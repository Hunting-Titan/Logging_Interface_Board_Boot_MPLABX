/**************************************************************************************/
/** \file fsk.c
  
  Company:
    Hunting Titan
  
  File Name:
    fsk.c

  Summary:
    These files control the FSK messaging to a PerfSwitch.

  Description:
    These files control the FSK messaging to a PerfSwitch. This machine prepares the 
    message and sends it to the PerfSwitch. Short messages have a preamble of 1, 
    a one bit null time,1,1,0 along with the message. A long message will have a 
    preamble, the message and a CRC. All messages are appended with a 1 to complete 
    the message. 
    
*/ 
/**************************************************************************************/

/**************************************************************************************/
/**************************************************************************************/
/* Section: Included Files                                                            */
/**************************************************************************************/
/**************************************************************************************/
#include "fsk.h"
#include "crc.h"
#include "man.h"
#include "wl_cps.h"

#include"../system_config.h"
#include"../system_definitions.h"
#include <stdint.h>
#include <stddef.h>
#include <math.h>
#include <xc.h>


/**************************************************************************************/
/**************************************************************************************/
/*  Section: Defines                                                                  */                                                      
/**************************************************************************************/
/**************************************************************************************/

#define  testbit(var, bit)   (((var) & (1U <<(bit))) != 0U)                             /*!< Short function to determine whether to send a 'Mark'(1) or a 'Space'(0).*/

/**************************************************************************************/
/**************************************************************************************/
/* Section: Structure Data                                                            */
/**************************************************************************************/
/**************************************************************************************/

/**************************************************************************************/
/* FSK Data

  Summary:
    These structures hold the required states and variables to perform the FSK tasks.

  Description:
    These structures hold the required states and variables to perform the FSK tasks. 
    These are here to link these structures for use by the local functions.
 * 
  Remarks: 
    These are defined in fsk.h
*/

DOWN_MSG DWNMSG;
TMultiValue MESSAGE;
FSK_DATA FSK;
MSG_DATA MSG;
PRE_DATA PRE_MSG;

/**************************************************************************************/
/**************************************************************************************/
/* Section: Local Variables                                                           */
/**************************************************************************************/
/**************************************************************************************/

static	uint8_t TimeMark[ 312 ];                                                        /*!< Table for DAC mark update spacings.*/                                                     
static	uint8_t TimeSpace[ 168 ];                                                       /*!< Table for DAC space update spacings.*/

static volatile float32_t	errorMark,                                                  /*!< The updated value to change the FSK 'mark' spacings.*/
                            errorSpace;                                                 /*!< The updated value to change the FSK 'space' spacings.*/

static double               Corr0,                                                      /*!< The fractional part of the updated 'mark' spacings.*/
                            Corr1,                                                      /*!< The fractional part of the updated 'space' spacings.*/
                            intpart0,                                                   /*!< The integer part of the updated 'mark' spacings.*/
                            intpart1,                                                   /*!< The integer part of the updated 'space' spacings.*/
                            Esum;                                                       /*!< The sum of the fractional parts as a DAC spacing table is generated.*/

 uint16_t i;                                                                            /*!< Counter for table generation.*/
/**************************************************************************************/
/**************************************************************************************/
/* Section: State Machine Functions                                                   */
/**************************************************************************************/
/**************************************************************************************/

/*************************************************************************************** 
  Function:
    void FSK_Tasks( ( void )

  Summary:
   This routine is the FSK tasks function.  It defines the (FSK) state machine and
   core logic.

  Remarks:
    Refer to the fsk.h interface header for function usage details.
 */

void FSK_Tasks( void )
{
    switch( FSK.state)
    {
        case FSK_STATE_INIT:
        {
            Init_FSK( );                                                                /* Initialize the FSK parameters and start Timer 2.*/
            FSK.state = FSK_STATE_CHECK_MESSAGE_READY;                                  /* Move on to see if a message to a PerfSwitch is ready to be sent.*/
            PRE_MSG.state = PREAMBLE_STATE_IDLE;                                        /* Put the FSK preamble state machine in idle.*/
            MSG.state = MSG_STATE_IDLE;                                                 /* Put the Send_Message_task state machine in idle.*/
        }
        break;
        
        case FSK_STATE_CHECK_MESSAGE_READY:
        {
            if( DWNMSG.xmit_ready_flag != 0x00U )                                       /* If we are ready to transmit a message to a PerfSwitch.*/
            {                                                                           /* This flag is set in the Protocol B commands.*/
                FSK.state = FSK_STATE_PREP_MESSAGE;                                     /* Move on to prep the message.*/
            }
        }
        break;
        
        case FSK_STATE_PREP_MESSAGE:
        {
            switch( DWNMSG.msg_length )                                                 /* Determine the message length.*/
            {
                case 0x04U:
                {  
                    MSG.command = DWNMSG.identifier;                                    /* Configure the message command.*/
                    MSG.length = DWNMSG.msg_length - 1U;                                /* Configure the message length.*/
                    FSK.state = FSK_STATE_SEND_MESSAGE;                                 /* Move on to send the message.*/
                    MSG.state = MSG_STATE_CAL_MAN_BIAS_1;                               /* Initialize the first task in the SEND_MESSAGE_Tasks machine.*/
                }
                break;

                case 0x14U:
                {
                    Reset_CRC_Value( );                                                 /* Reset the CRC value.*/
                    Calc_CRC( 3, DWNMSG.identifier );                                   /* CRC is not calculated for the Long/Short Bit	*/
                    Calc_CRC( 8, DWNMSG.command );                                      /* Update the CRC result with the command byte.*/
                    FSK.crc	= Get_CRC_Value( );
                    
                    MESSAGE.byte[ 2 ]= DWNMSG.identifier;                               /* Prepare the message.*/
                    MESSAGE.byte[ 1 ]= DWNMSG.command;
                    MESSAGE.byte[ 0 ]= FSK.crc;                    
 
                    MSG.command = MESSAGE.dword;                                        /* Configure the message command.*/
                    MSG.length = DWNMSG.msg_length - 1U;                                /* Configure the message length.*/
                    FSK.state = FSK_STATE_SEND_MESSAGE;                                 /* Move on to send the message.*/
                    MSG.state = MSG_STATE_CAL_MAN_BIAS_1;                               /* Initialize the first task in the SEND_MESSAGE_Tasks machine.*/
                    
                }
                break; 
                
                default:
                {
                    /*Comment.*/
                }
                break;
            } 
        }
        break;
        
        case FSK_STATE_SEND_MESSAGE:
        {            
            Send_Message_Tasks();                                                       /* Send the FSK message to the PerfSwitch.*/
            if(FSK.send_message_complete_flag == true)                                  /* If we have completed sending the message,*/
            {
                FSK.state = FSK_STATE_WAIT;                                             /* Move on to wait for the Manchester response.*/
                MAN.state = MAN_STATE_RECEIVE_START;                                    /* Initiate the Manchester Receive tasks.*/
            }
        }
        break;
        
        case FSK_STATE_WAIT:                                                            /* Wait here for the Manchester response.*/
        {
            
        }
        break;
        
        case FSK_STATE_COMPLETE_MESSAGE:                                                /* Machines moves here after Manchester response is received.*/
        {
            if(MAN.trynumber <= 0x02U)                                                  /* If we do not have to retry to send an FSK message,*/
            {
                DWNMSG.xmit_ready_flag = 0x00U;                                         /* Reset the transmit ready flag.*/                                               
                MESSAGE.dword = 0U;                                                     /* Reset the message.*/
                FSK.state = FSK_STATE_CHECK_MESSAGE_READY;                              /* Move on to see if another message needs to be transmitted.*/            
                FSK.send_message_complete_flag = false;
            }
            else                                                                        /* Otherwise,*/
            {
                FSK.state = FSK_STATE_CHECK_MESSAGE_READY;                              /* Move on to retransmit the message.*/            
                FSK.send_message_complete_flag = false;
            }
        }
        break;
        
        default:
        {
            /*Comment.*/
        }
        break;
    }
}

/**************************************************************************************/
/**************************************************************************************/
/* Section: Interface Functions                                                       */
/**************************************************************************************/
/**************************************************************************************/

/*!************************************************************************************* 
  Function:
    void Prepare_Dwn_Msg( uint8_t Identifier, uint8_t Command, uint8_t msgLength )

  Summary:
    Receives information from the command parser and stores it into the structure
    for FSK.	

  Remarks:
    Refer to the fsk.h interface header for function usage details.
 */

void Prepare_Dwn_Msg( uint8_t Identifier, uint8_t Cmd, uint8_t Msg_Length )
{
	DWNMSG.identifier	 = Identifier;                                                  /* The state ID to be transmitted.*/
	DWNMSG.command		 = Cmd;                                                         /* The command to be transmitted.*/
	DWNMSG.msg_length	 = Msg_Length;                                                  /* The length of the message in bits.*/
}

/*!************************************************************************************* 
  Function:
    void Generate_Sine_Wave_Data( float NoOfTicks )

  Summary:
    This function stores sine wave inter step time values into two arrays at 
    initialization and if the FSK frequency needs to be adjusted.

  Remarks:
    Refer to the fsk.h interface header for function usage details.
 */

void Generate_Sine_Wave_Data( float32_t NoOfTicks )
{
	uint8_t mark;                                                                       /*!< The rounded integer result of errorMark.*/
	uint8_t	space;                                                                      /*!< The rounded integer result of errorSpace.*/	
    
    if(NoOfTicks == 1.0F)
    {
        FSK.mark_count = FSK.init_mark_count;                                           /* Store the original values.*/
        FSK.space_count = FSK.init_space_count;
    }
    errorMark = FSK.mark_count *(NoOfTicks);                                            /* Calculate the new FSK 'MARK' count.*/  
    errorSpace = FSK.space_count * NoOfTicks;                                           /* Calculate the new FSK 'SPACE' count.*/ 
    FSK.mark_count = errorMark;
    FSK.space_count = errorSpace;  
    
    Corr0 = modf(errorMark, &intpart0);                                                 /* Find the fractional and integer portions of the*/
    Corr1 = modf(errorSpace,&intpart1);                                                 /* update mark and space values.*/
    
    mark = (uint8_t)(intpart0);                                                         /* Keep the integer portion of the updated values.*/
    space = (uint8_t)(intpart1);    
    
    Esum = 0.0;                                                                         /* Create the new space table.*/
    for (i = 0; i < 168;i++)                                                            /* 168 is 24 steps/wave time 7 waves.*/
    {
        TimeSpace[i] = intpart1;                                                        /* Store the integer portion.*/
        Esum = Esum + Corr1;                                                            /* Sum the fractional portion.*/
        while (Esum >= 1.0)                                                             /* When the fractional sum is greater than 1.0,*/
        {
			TimeSpace[i]++;			                                                    /* Add one to the table value and*/
			Esum -= 1.0;		                                                        /* reduce the fractional sum by one.*/
		}
    }
    
    Esum = 0.0;                                                                         /* Create the new mark table.*/
    for (i = 0; i < 312; i++)                                                           /* 312 is 24 steps per wave times 13 waves.*/
    {	
		TimeMark[i] = intpart0;	                                                        /* Store the integer portion.*/
		Esum = Esum + Corr0;			                                                /* Sum the fractional portion.*/
		while (Esum >= 1.0) 
        {
			TimeMark[i]++;			                                                    /* Add one to the table value and*/
			Esum -= 1.0;		                                                        /* reduce the fractional sum by one.*/
		}
	}
    Nop();
    
    /*LDRA_INSPECTED 124 D*/                                                            /* No need to check return from rounding function.*/
//    mark = (uint8_t)rint(errorMark);                                                    /* Round the errorMark result to the nearest integer.*/
//    /*LDRA_INSPECTED 124 D*/
//    space = (uint8_t)rint(errorSpace);                                                  /* Round the errorSpace result to the nearest integer.*/ 
//    /*LDRA_INSPECTED 489 S*/                                                            /* Proper use of memset function.*/
//    (void)memset( TimeMark, mark, sizeof( TimeMark ) );                                 /* Update the TimeMark array with the new mark value.*/
//    /*LDRA_INSPECTED 489 S*/                                                            /* Proper use of memset function.*/
//    (void)memset( TimeSpace, space, sizeof( TimeSpace ) );                              /* Update the TimeSpace array with the new space value.*/ 
}

/**************************************************************************************/
/**************************************************************************************/
/* Section: Local Functions                                                           */
/**************************************************************************************/
/**************************************************************************************/

/*!************************************************************************************* 
  Function:
    static void Init_FSK( void )

  Summary:
    Function to initialize FSK parameters.

  Remarks:
    Refer to the fsk.h interface header for function usage details.
 */

static void Init_FSK( void )
{
//    FSK.init_mark_count = 47.0F;                                                        /* Single 3.0. Box. The initial number of time counts between DAC updates.*/
//    FSK.init_space_count = 87.0F;                                                       /* Single 1.8. Single 3.0. Box. The initial number of time counts between DAC updates.*/
 
//    FSK.init_mark_count = 48.0F;                                                        /* Single 3.0. Box. The initial number of time counts between DAC updates.*/
//    FSK.init_space_count = 88.0F;                                                       /* Single 1.8. Single 3.0. Box. The initial number of time counts between DAC updates.*/
//    
//    FSK.mark_count = FSK.init_mark_count;
//    FSK.space_count = FSK.init_space_count;
//
//    MESSAGE.dword = 0U;                                                                 /* Initialize the FSK message to send to 0.*/
//    DWNMSG.xmit_ready_flag = 0x00U;                                                     /* Reset flag to indicate that we are not ready to send a message.*/           
//    FSK.send_message_complete_flag = false;                                             /* Flag to show we have completed sending an FSK message.*/                                    
//    FSK.null_count = 0U;                                                                /* Initialize null count to 0.  Used to determine 2.5mS null time in preamble.*/
//    FSK.tick = false;                                                                   /* Initialize the FSK timer tick.*/           
////    FSK.baud = 405.0F;                                                                  /* Initial FSK baud rate in Hertz. Based on temperature testing.*/
//    FSK.baud = 400.0F;                                                                  /* Initial FSK baud rate in Hertz. Based on temperature testing.*/
//    FSK.fsk_timer_freq = 6250000.0F;                                                    /* 10nS clock w/ 16 pre-scalar gives 160nS period.*/
//
//    Generate_Sine_Wave_Data( 1.0 );                                                     /* Generate the table with no correction.*/
//    (void)DRV_TMR2_Start();                                                             /* Start the timer 2 instance using (Timer 6). Set for 160nS.*/
            
}
/*!************************************************************************************* 
  Function:
    static void Send_Message_Tasks(void )

  Summary:
    Function to send FSK message.

  Remarks:
    Refer to the fsk.h interface header for function usage details.
 */

static void Send_Message_Tasks(void )
{
    switch(MSG.state)
    {
        case MSG_STATE_IDLE:                                                            /* The initial state to wait for a FSK message to send.*/
        {
                                                                                        /* No action occurs here.*/
        }
        break;
        
        case MSG_STATE_CAL_MAN_BIAS_1:                                                  /* Perform the first Manchester bias adjustment.*/
        {                                                                               /* Accessed from the FSK state machine.*/
            if(MAN.manual_bias_flag == false)                                           /* If we have not set the MAN bias manually,*/
            { 
//                if((MAN.spi_sent_flag == false) &&                                      /* If we have not sent the command and the MAN_BIAS SPI port is open,*/
//                    (MAN_BIAS.spi_bias_fsk != DRV_HANDLE_INVALID))
                {
                    Calc_Auto_Bias();                                                   /* Calculate the correct bias and send data to the MAN_BIAS SPI port.*/
                    MAN.spi_sent_flag = true;                                           /* Set this flag to show we sent data to the MAN_BIAS SPI port.*/
                }    

                if(MAN.spi_write_complete_flag == true)                                 /* If the SPI port is through sending data,*/
                {
                    MAN.spi_write_complete_flag = false;                                /* reset the flag.*/
                    MSG.state = MSG_STATE_SEND_PREAMBLE;                                /* Move on send the message preamble.*/
                    PRE_MSG.state = PREAMBLE_STATE_SEND_TICKLE;                         /* Set the PRE_MSG state machine to its initial state.*/
                    MAN.spi_sent_flag = false;                                          /* Reset the flag so we can send data.*/
                }
            }
        }
        break;
        
        case MSG_STATE_SEND_PREAMBLE:                                                   /* This state contains the PRE_MSG state machine.*/
        {
            switch(PRE_MSG.state)                                                       /* This machine controls the sending of the preamble bits.*/
            {
                case PREAMBLE_STATE_IDLE:                                               /* Wait here until the next message needs to be sent.*/
                {
                                                                                        /* No action occurs here.*/
                }
                break;
                
                case PREAMBLE_STATE_SEND_TICKLE:                                        /* Send the first MARK 'tickle' bit.*/
                {
                    Send_Mark();
                    PRE_MSG.state = PREAMBLE_STATE_NULL;                                /* Move on to wait for the null period.*/                    
                }
                break;
                
                case PREAMBLE_STATE_NULL:                                               /* Null time between tickle bit and remaining preamble.*/
                {
                    if(FSK.tick == true)                                                /* If 100uS FSK tick is true,*/
                    {
                        FSK.tick = false;                                               /* reset the tick.*/
                        if(FSK.null_count == 25U)                                       /* If 2.5mS has passed,*/
                        {
                            FSK.null_count = 0U;                                        /* reset the count.*/
                            PRE_MSG.state = PREAMBLE_STATE_SEND_MARK_1;                 /* Move on to send the first MARK bit.*/
                        }
                        else                                                            /* Otherwise,*/
                        {
                            FSK.null_count = FSK.null_count + 1U;                       /* increment the null timer count.*/
                        }
                    }
                }
                break;
                
                case PREAMBLE_STATE_SEND_MARK_1:                                        /* Send the first MARK bit of the preamble.*/
                {
                    Send_Mark();
                    PRE_MSG.state = PREAMBLE_STATE_SEND_MARK_2;                         /* Move on to send the second MARK bit.*/
                }
                break;
                
                case PREAMBLE_STATE_SEND_MARK_2:                                        /* Send the second MARK bit of the preamble.*/
                {
                    Send_Mark();
                    PRE_MSG.state = PREAMBLE_STATE_SEND_SPACE;                          /* Move on to send the first SPACE bit.*/
                }
                break;
                
                case PREAMBLE_STATE_SEND_SPACE:                                         /* Send the SPACE bit of the preamble.*/
                {
                    Send_Space();
                    PRE_MSG.state = PREAMBLE_STATE_IDLE;
                    MSG.state = MSG_STATE_SEND_MESSAGE;
                }
                break;
                
                default:
                {
                    /*Comment.*/
                }
                break;
            }
        }
        break;
        
        case MSG_STATE_SEND_MESSAGE:
        { 
            int8_t bit_position;

            for(bit_position = (int8_t)MSG.length; bit_position >= 0;bit_position--)    /* For loop required to maintain proper FSK timing to PerfSwitch.*/    
            {                                                                           /* This cannot be set up like the preamble. This is sent MSB first.*/
                /*LDRA_INSPECTED 403 S*/                                                /* bit_position will not be a negative number.*/
                if( testbit( MSG.command, bit_position ) == 0x01U )                     /* If the bit in the message is a one,*/    
                {
                    Send_Mark( );                                                       /* send an FSK one.*/
                }
                else                                                                    /* Otherwise,*/
                {
                    Send_Space( );                                                      /* send an FSK zero.*/
                }               
            }
            
            Send_Mark( );                                                               /* Send an extra Mark (Stop bit)or else PerfSwitch won't respond.*/
            MSG.state = MSG_STATE_NULL;                                                 /* Move on to wait for a null time.*/
        }
        break;
        
        case MSG_STATE_NULL:                                                            /* Null time after last bit.*/
        {
            if(FSK.tick == true)                                                        /* If 100uS FSK tick is true,*/
            {
                FSK.tick = false;                                                       /* reset the tick.*/
                if(FSK.null_count == 25U)                                               /* If 2.5mS has passed,*/
                {
                    FSK.null_count = 0U;                                                /* reset the count.*/
                    MSG.state = MSG_STATE_IDLE;                                         /* Move on to wait for another message to send.*/
                    FSK.send_message_complete_flag = true;                              /* Flag to indicate that we have completed sending the FSK message.*/
                }
                else                                                                    /* Otherwise,*/
                {
                    FSK.null_count = FSK.null_count + 1U;                               /* increment the null timer count.*/
                }
            }
        }
        break;  
        
        default:
        {
            /*Comment.*/
        }
        break;
    }
       
}

/*!************************************************************************************* 
  Function:
    static void Send_Space( void )

  Summary:
    This function sends a FSK 0 or 'SPACE'. It is called from the Send_Message_Task 
    function.

  Remarks:
    Refer to the fsk.h interface header for function usage details.
 */
static void Send_Space( void )
{
	uint16_t  cnt1;
    
//    for( cnt1 = 0U; cnt1 < sizeof( TimeSpace ); cnt1++ )
//	{
//        FSK_DAC_CSOff();                                                                /* Bring the chip select line low.*/
//        DRV_PMP0_Write(Xmit00[ cnt1 ]);                                                 /* Update the DAC value for generating the FSK "Space" sine wave.*/
//		FSK_DAC_CSOn();                                                                 /* Bring the chip select line high.*/
//        DRV_TMR2_CounterClear();                                                        /* Reset the timer.*/
//        (void)DRV_TMR2_Start();                                                         /* Start the timer again.*/
//        /*LDRA_INSPECTED 28 D*/                                                         /* No infinite loop.*/
//		while( DRV_TMR2_CounterValueGet() < (uint32_t)TimeSpace[ cnt1 ] )               /* Wait until the timer is greater than the TimeSpace value.*/
//		{
//            /*Comment.*/
//		}
//	}
}

/*!************************************************************************************* 
  Function:
    static void Send_Mark( void )

  Summary:
    This function sends a FSK 1 or 'MARK'. It is called from the Send_Message_Task 
    function.

  Remarks:
    Refer to the fsk.h interface header for function usage details.
 */
static void Send_Mark( void )
{
//	uint16_t  cnt1;
//  
//    for( cnt1 = 0U; cnt1 < sizeof( TimeMark ); cnt1++ )
//	{
//        FSK_DAC_CSOff();                                                                /* Bring the chip select line low.*/
//        DRV_PMP0_Write(Xmit11[ cnt1 ]);                                                 /* Update the DAC value for generating the FSK "Mark" sine wave.*/
//		FSK_DAC_CSOn();                                                                 /* Bring the chip select line high.*/
//        DRV_TMR2_CounterClear();                                                        /* Reset the Timer 2 count.*/
//        (void)DRV_TMR2_Start();                                                         /* Start the timer again.*/
//        /*LDRA_INSPECTED 28 D*/                                                         /* No infinite loop.*/
//		while( DRV_TMR2_CounterValueGet() < (uint32_t)TimeMark[ cnt1 ] )                /* Wait until Timer 2 reaches the TimeMark value.*/
//		{
//            /*Comment.*/
//		}
//	}    
}

/***************************************************************************************
 End of File
 */
