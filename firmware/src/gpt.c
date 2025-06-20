/**************************************************************************************/
/** \file gpt.c
     
  Company:
    Hunting Titan
  
  File Name:
    gpt.c

  Summary:
    This file contains the state machine code for the GPT operation.

  Description:
    This file contains the state machine code for the GPT operation.  Once started, 
    the GPT operation decodes the Titan telemetry message from the GPT tool. Sync 
    pulses occur every 64mS to indicate the start of a new data string.  21 'channels' 
    of data can be sent along with a checksum and tool version number.  The tool
    uses Titan telemetry protocol.  Each bit uses a 200uS window. A data pulse received
    represents a 'one' and no data pulse represents a 'zero'. The states are configured 
    so that other system tasks can be maintained while these tasks are waiting for an 
    event to occur. 
*/
/**************************************************************************************/

/**************************************************************************************/
/**************************************************************************************/
/*  Section: Included Files                                                           */                                                      
/**************************************************************************************/
/**************************************************************************************/

#include "gpt.h"
#include "hvps.h"
#include "hvps_test.h"
#include "switches.h"
#include "high_side.h"
#include "wl_sps.h"
#include "timers.h"
#include "report.h"

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <xc.h>

#include "system_config.h"
#include"../system_definitions.h"



/**************************************************************************************/
/**************************************************************************************/
/* Section: Structure Data and Local Variables                                        */
/**************************************************************************************/


/**************************************************************************************/
/* GPT Data

  Summary:
    These structures hold the required states and variables to perform the GPT tasks.

  Description:
    These structures hold the required states and variables to perform the GPT tasks. 
    These are here to link these structures for use by the local functions.
 
  Remarks: 
    These are defined in adc.h
*/

GPT_DATA GPT;

static GPT_STATES G_STATES;
static GPT_RX_STATES GRX_STATES;
static GPT_PROCESS_STATES GTX_STATES;

/***************************************************************************************
 *	$GLOBAL VARIABLES
***************************************************************************************/
static	uint32_t gpt_timer_count[275];
static uint8_t fnp;
uint8_t count;

/**************************************************************************************/
/**************************************************************************************/
/*  Section: Application Callback Routines                                            */
/**************************************************************************************/
/**************************************************************************************/

void GPT_TimerCallback( uintptr_t context, uint32_t alarmCount )
{
    GPT.tmrIntTriggered = true;                                                         /* Set the 200uS timer complete flag to true.*/
    
    GPT.timer_count = DRV_TMR5_CounterValueGet();                                       /* For testing.*/
    DRV_TMR5_CounterClear();                                                            /* Reset the timer.*/
    DRV_TMR5_Stop();                                                                    /* Stop the 200uS timer.*/
    LED2Off(); 
    Nop();
//    if(GPT.int_count <= 12U)
//    {
//        DRV_TMR_AlarmEnable(GPT.tmrHandle, true);
//        DRV_TMR_Start(GPT.tmrHandle);
//        LED2On();
//    }  
 
    GPT.int_count = GPT.int_count + 1U;                                                 /* Increment the 200uS counter.  Used to track 13 events per channel.*/
}

/**************************************************************************************/
/**************************************************************************************/
/* Section: Local Functions                                                           */
/**************************************************************************************/
/**************************************************************************************/

/*!************************************************************************************* 
  Function:
    static void Alarm_GPT( void )

  Summary:
    Function to initialize GPT parameters.

  Remarks:
    Refer to the man.h interface header for function usage details.
 */

void Alarm_GPT( void )
{
    GPT.tmrHandle = DRV_TMR_Open(DRV_TMR_INDEX_5, 0);                                   /* Open Timer Instance 5.  It is using Timer 8. Register the 200uS alarm callback.*/
    DRV_TMR_AlarmRegister(GPT.tmrHandle, 19200, false, 0, GPT_TimerCallback);            
    DRV_TMR_AlarmEnable(GPT.tmrHandle, true);
    (void) memset( GPT.ch_bit_data, 0, 12);
    (void) memset( GPT.ch_rev_bit_data, 0, 12);
//    GPT.tmrIntTriggered = false;   
}
/*!************************************************************************************* 
  Function:
    static void Init_GPT( void )

  Summary:
    Function to initialize GPT parameters.

  Remarks:
    Refer to the man.h interface header for function usage details.
 */

void Init_GPT( void )
{
	fnp = 0U;                                                                           /* Initialize index counter for storing incoming GPT message.*/
//    GPT_BIAS.dac_a_setting = 0x0300;                                                    /* Sets the SPI message to write to the DAC A output only.*/
//    GPT_BIAS.spi_bias_fsk = DRV_HANDLE_INVALID;                                         /* Set the MAN_BIAS SPI Port handle to invalid.*/
//    GPT.process_complete_flag = false;                                                  /* Flag to show if we have completed the GPT processing task.*/
//	GPT.trynumber = 0x02;                                                               /* Set this to the default value.*/
    
//    GPT.spi_write_complete_flag = false;                                                /* Set this flag to show we have not completed an SPI write to the MAN_BIAS DAC.*/                                                          
//    GPT.spi_sent_flag = false;                                                          /* Set this flag to show we have not sent an SPI message to the MAN_BIAS DAC.*/
    GPT.timer_count = 0U;                                                               /* Reset the 200uS timer count to 0.*/
//    GPT.timer_complete = 13;                                                            /* Set the max number of timer counts to reflect 130mS.*/ 
    GPT.sync_bit_count = 0U;    
    GPT.sync_received_flag = false;                                                     /* Initialize the variables.*/
    GPT.sync_timer_started_flag = false;                                                
    GPT.sync_timer_value = 0U;
    GPT.sync_data_timer_started_flag = false;                                    
    GPT.sync_data_timer_value = 0U;
    GPT.null_timer_value = 0U;
    GPT.data_sync_received_flag = false;
//    GPT.sync_data_start = 0U;
//    GPT.sync_data_stop = 0U;
    
    GPT.data_timer_value = 0U;
    GPT.data_count = 0U;
    GPT.data_bit_count = 0U;
    GPT.data_ch_count = 0U;
    GPT.data_sum = 0U;
    GPT.data_good_flag = false;
    
    GPT.first_sum = 0U;
    GPT.second_sum = 0U;
    GPT.first_sum_MSB = 0U;
    GPT.first_sum_LSB = 0U;
    GPT.tick = false;                                                                   
    GPT.crc = 0U;    
    
    GPT.null_timer_complete = false;
    GPT.timer_count = 0U;
    GPT.cnt_data = 0U;
    GPT.cnt_sync = 0U;
    GPT.int_count = 0U;
    GPT.inter_count = 0U;
    GPT.inter_timer_tick = false;    
    
     
//    GPT_BIAS.dac_b_setting = 0x2700;                                                    /* Sets the SPI message to write to the DAC B output only.*/

//    GPT.error = false;                                                                  /* Flag to show if a GPT error has occurred.*/
//    GPT.manual_bias_flag = false;                                                       /* Flag to indicate if the manual DAC bias setting is used.*/
//    GPT.tmrHandle = DRV_TMR_Open(DRV_TMR_INDEX_5, 0);                                   /* Open Timer Instance 5.  It is using Timer 8. Register the 200uS alarm callback.*/
//    DRV_TMR_AlarmRegister(GPT.tmrHandle, 19200, false, 0, GPT_TimerCallback);            
//    DRV_TMR_AlarmEnable(GPT.tmrHandle, true);
    GPT.tmrIntTriggered = false;                                                        /* Initialize 200uS timer complete flag.*/
    GPT.Rx_state = GPT_RX_STATE_IDLE;                                                   /* This GPT receive state machine is in the change notice ISR. Set it to idle.*/
    GPT.Process_state = GPT_PROCESS_STATE_IDLE;                                         /* Set the GPT process state machine to idle.*/

}

/**************************************************************************************/
/**************************************************************************************/
/* Section: State Machine Functions                                                   */
/**************************************************************************************/
/**************************************************************************************/

/*************************************************************************************** 
  Function:
    void GPT_RX_Tasks( void )

  Summary:
   This routine is the GPT_RX_Tasks function.  It defines the GPT_RX state machine and
   core logic.

  Remarks:
    Refer to the man.h interface header for function usage details.
 */

void  GPT_RX_Tasks(void)
{
	switch( GPT.Rx_state )
	{
		case GPT_RX_STATE_IDLE:
        {
            count = 0U;                                                                 /* Reset counter after every message.*/
            GPT.Rx_state = GPT_RX_STATE_TRY;
        }
		break;
        
        case GPT_RX_STATE_TRY:
        {
            if(GPT.tmrIntTriggered == true)
            {
                GPT.tmrIntTriggered = false;
                GPT.Rx_state = GPT_RX_STATE_DONE;
            }
            else
            {
                GPT.Rx_state = GPT_RX_STATE_DONE;
            }    
        }
        break;
        
        case GPT_RX_STATE_DONE:
        {
            
//            GPT.timer_count = 0U;
//            DRV_TMR_AlarmEnable(GPT.tmrHandle, true);
//            DRV_TMR_Start(GPT.tmrHandle);             
            GPT.Rx_state = GPT_RX_STATE_TRY;
        }
        break;
        
        case GPT_RX_STATE_INIT:
        {
            Init_GPT();                                                                 /* Initialize the variables.*/
//            if(RLY_GPT_StateGet()==true)
//            {
//                GPT.Rx_state = GPT_RX_STATE_SYNC;
//            }
        }
        break;
            
		case GPT_RX_STATE_SYNC:                                                         /* Looking for sync bit for the start of a GPT transmission.*/
        {
//            gpt_timer_count[count] = GPT.sync_timer_value;                              /* Debug only. Store timer values.*/
            
			if((GPT.sync_timer_value >= GptSyncLower) && 
                                           (GPT.sync_timer_value <= GptSyncUpper))      /* Verify that the sync bit received is within period window.*/
			{
                count = 1U;                                                             /* Flag is set when proper bit is received.*/
				GPT.sync[ GPT.cnt_sync ] = (uint16_t)GPT.sync_timer_value;              /* Store the timer_value for testing.*/
				GPT.cnt_sync++;                                                         /* Increment index counter for testing.*/
			}
            else                                                                        /* If the sync time count is not within the window,*/
            {
                GPT.sync_timer_started_flag = false;                                    /* Reset flag for interrupt routine.*/
                GPT.sync_timer_value = 0U;                                              /* Reset the variables.*/
                GPT.int_count = 0U;

                GPT.Rx_state = GPT_RX_STATE_IDLE;                                       /* Move to idle and wait for another sync bit.*/
            }
            if(count == 1U)                                                             /* If a proper sync bit was received,*/
            {
//                LED2On();
                GPT.sync_timer_started_flag = false;                                    /* Reset variables.*/                     
                GPT.sync_timer_value = 0U;                                              
                GPT.sync_received_flag = true;
                count = 0U;
                GPT.null_timer_value = 0U;
                GPT.sync_data_timer_started_flag = false; 
                GPT.Rx_state = GPT_RX_STATE_NULL;                                       /* Move on to wait for the null time.*/
            }
			if( GPT.cnt_sync >= 274U )                                                  /* If we have received 274 values,*/
			{
				GPT.cnt_sync = 0U;                                                      /* reset the counter. For testing.*/
			}            
        }
		break;
        
        case GPT_RX_STATE_NULL:
        {
            GPT.null_timer_value = DRV_TMR2_CounterValueGet();                          /* Record the timer count to test if the null time has past.*/
            if((GPT.null_timer_value >= GptNullLower) && 
                                    (GPT.null_timer_value <= GptNullUpper))             /* If the null timer count is within the window,*/
            {
//                LED2Off();
                LED2On();
                DRV_TMR_AlarmEnable(GPT.tmrHandle, true);                               /* Start the 200uS timer counter for the data bits.*/
                DRV_TMR_Start(GPT.tmrHandle);
                GPT.null_timer_complete = true;                                         /* Reset the variables.*/
                GPT.null_timer_value = 0U;
                
                DRV_TMR2_Stop();
                DRV_TMR2_CounterClear();                                                /* Reset the Timer 2 count.*/
                (void)DRV_TMR2_Start();                                                 /* Start the timer again.*/
                Nop();
                GPT.Rx_state = GPT_RX_STATE_SYNC_DATA;                                  /* move on to look for a sync data bit.*/
            }
        }
        break;
        
        case GPT_RX_STATE_SYNC_DATA:                                                    /* Looking for sync data bit for the start of a channel GPT transmission.*/
        {
            gpt_timer_count[count] = GPT.sync_data_timer_value;                         /* Debug only. Store timer values.*/
            
			if((GPT.sync_data_timer_value >= GptDataLower) &&                           /* If the sync data bit is within the period window,*/
                                        (GPT.sync_data_timer_value <= GptDataUpper))    
			{
                count = 1U;
				GPT.data_sync[ GPT.cnt_sync ] = (uint16_t)GPT.sync_data_timer_value;    /* Store the timer_value for testing.*/
				GPT.cnt_sync++;                                                         /* Increment index counter.*/
                GPT.data_sync_received_flag = true;
			}
            else if(GPT.sync_data_timer_value > GptDataUpper)                           /* If the sync data bit is greater than the period window,*/
            {
                GPT.tmrIntTriggered = false;                                            /* Reset the variables.*/
                GPT.data_sync_received_flag = false;
                GPT.data_timer_started_flag = false;
                GPT.null_timer_complete = false;
                GPT.sync_data_timer_value = 0U;
                GPT.sync_timer_started_flag = false;
                GPT.sync_bit_count = 0U; 
                GPT.data_count = 0U;
                GPT.data_ch_count = 0U;
                GPT.int_count = 0U;
                GPT.data_bit_count = 0U;
                Set_Status( 7 );                                                        /* Set bit to show that the data was bad.*/
                (void) memset( GPT.ch_bit_data, 0, 12);
                (void) memset( GPT.ch_rev_bit_data, 0, 12);
                (void)memset(REPORT.data, 0, 50);
                DRV_TMR2_CounterClear();                                                /* Reset the timer.*/
                DRV_TMR2_Stop();                                                        /* Stop the timer again.*/
                GPT.Rx_state = GPT_RX_STATE_INIT;                                       /* Move on to wait for another sync bit.*/
            }
            else
            {
                /**/
            }
//            if((GPT.inter_timer_tick == true) && (GPT.tmrIntTriggered == false))
//            {              
//                GPT.inter_count = GPT.inter_count + 1U;
//            }
//            if((GPT.inter_count > 2U == true))
//            {
//                GPT.Rx_state = GPT_RX_STATE_INIT;
//                GPT.inter_count = 0U;
//            }
            if(GPT.tmrIntTriggered == true)                                             /* testing only.*/
            {
                GPT.inter_count = 0U;
            }
            if((count == 1U) && (GPT.tmrIntTriggered == true))                          /* If we received a valid data sync bit and the 200uS timer has expired,*/
            {
                if(GPT.sync_bit_count ==2U)                                             /* Testing.*/
                {
                    Nop();
                }
                GPT.data_bit_count = 0U;                                                /* Reset the variables.*/
                GPT.tmrIntTriggered = false;
                GPT.data_timer_started_flag = false;
                GPT.sync_data_timer_value = 0U;
//                GPT.data_received_flag = true;
                GPT.Rx_state = GPT_RX_STATE_DATA;                                       /* Move to get the data bits for a channel.*/
                count = 0U;                
//                DRV_TMR2_CounterClear();                                                /* Reset the timer.*/
                DRV_TMR2_Stop();                                                        /* Stop the timer again.*/
                DRV_TMR_AlarmEnable(GPT.tmrHandle, true);                               /* Restart the 200uS timer.*/
                DRV_TMR_Start(GPT.tmrHandle);
                LED2On();
                Nop();
            }
			if( GPT.cnt_sync >= 274U )                                                  /* If we have received 274 values,*/
			{
				GPT.cnt_sync = 0U;                                                      /* reset the counter.*/
			}            
        }
		break;
        
        case GPT_RX_STATE_DATA:
        {
            count = 1U;
            gpt_timer_count[count] = GPT.data_timer_value;                              /* Debug only. Store timer values.*/
            
			if((GPT.data_timer_value >= GptDataLower) &&                                /* If the data bit is within the period window,*/         
                                        (GPT.data_timer_value <= GptDataUpper))
			{
                count = 1U;
				GPT.data[ GPT.cnt_data ] = (uint16_t)GPT.data_timer_value;              /* Store the timer_value for testing.*/
				GPT.cnt_data++;                                                         /* Increment index counter.*/
                GPT.data_received_flag = true;
			}
            else if(GPT.data_timer_value > GptDataUpper)                                /* If the data bit is greater than the period window,*/            
            {
                GPT.tmrIntTriggered = false;                                            /* Reset the variables.*/
                GPT.data_received_flag = false;
                GPT.data_timer_started_flag = false;
                GPT.null_timer_complete = false;
                GPT.sync_data_timer_value = 0U;
                GPT.sync_timer_started_flag = false;
                GPT.sync_bit_count = 0U; 
                GPT.data_count = 0U;
                GPT.data_ch_count = 0U; 
                GPT.int_count = 0U;
                GPT.data_bit_count = 0U;
                Set_Status( 7 );                                                        /* Set bit to show that the data was bad.*/
                (void) memset( GPT.ch_bit_data, 0, 12);                                 /* Clear the channel data bit arrays.*/
                (void) memset( GPT.ch_rev_bit_data, 0, 12);
                (void)memset(REPORT.data, 0, 50);
                DRV_TMR2_CounterClear();                                                /* Reset the timer.*/
                DRV_TMR2_Stop();                                                        /* Start the timer again.*/
                GPT.Rx_state = GPT_RX_STATE_INIT;                                       /* Move to wait for another sync bit.*/
            }
            else
            {
                /**/
            }
            if((GPT.tmrIntTriggered == true) && (count > 0U) &&                         /* If the 200uS timer has expired and we did not receive a 'one' bit,*/
                                            (GPT.data_received_flag == false))
//            if((GPT.tmrIntTriggered == true) && (count > 0U))
			{
//                LED2Off();
                GPT.tmrIntTriggered =  false;                                           /* Reset the variables.*/
                GPT.data_timer_value = 0U;
                GPT.data_timer_started_flag = false;
                if(GPT.int_count <= 12U)                                                /* If we have not received all twelve data bits for a channel,*/
                {
                    DRV_TMR_AlarmEnable(GPT.tmrHandle, true);                           /* reset and restart the 200uS timer.*/
                    DRV_TMR_Start(GPT.tmrHandle);
                    LED2On();
                } 
                DRV_TMR2_Stop();                                                        /* Stop the data bit width timer.*/
                GPT.data_bit = 0;                                                       /* Set the variable to show that this data bit is a '0'.*/
                
//                DRV_TMR_AlarmEnable(GPT.tmrHandle, true);
//                DRV_TMR_Start(GPT.tmrHandle);
//                LED2On();
                
                Nop();
                GPT.ch_bit_data[ GPT.data_bit_count ] = GPT.data_bit;                   /* Store the data bit in the Channel data bit array.*/
                GPT.data_bit_count = GPT.data_bit_count + 1U;                           /* Increment the array counter.*/
            }
            else if ((GPT.tmrIntTriggered == true) && (count > 0U) &&                   /* If the 200uS timer has expired and we did receive a 'one' bit,*/
                                            (GPT.data_received_flag == true))
            {
//                LED2Off();
                GPT.tmrIntTriggered =  false;                                           /* Reset the variables.*/
                GPT.data_timer_value = 0U;
                GPT.data_received_flag = false;
                GPT.data_timer_started_flag = false;
                if(GPT.int_count <= 12U)                                                /* If we have not received all twelve data bits for a channel,*/
                {
                    DRV_TMR_AlarmEnable(GPT.tmrHandle, true);                           /* reset and restart the 200uS timer.*/
                    DRV_TMR_Start(GPT.tmrHandle);
                    LED2On();
                }  
                DRV_TMR2_Stop();                                                        /* Stop the data bit width timer.*/
                GPT.data_bit = 1;                                                       /* Set the variable to show that this data bit is a '1'.*/
                
                
                GPT.ch_bit_data[ GPT.data_bit_count ] = GPT.data_bit;                   /* Store the data bit in the Channel data bit array.*/
                GPT.data_bit_count = GPT.data_bit_count + 1U;                           /* Increment the array counter.*/
                Nop();
                Nop();
               
            }

            if(GPT.int_count == 13U)                                                    /* If we have counted all data bit windows for a channel,*/
            { 
                GPT.inter_count = 0U;                                                   /* Testing only.*/
                if(GPT.data_count >= 6U)                                                /* Testing only.*/
                {
                    Nop();
                }
//               
                GPT.data_bit_count = 11U;                                               /* Set this to properly reverse the data bits for a channel.*/
//                GPT.reverse_count = 0U;
                for(GPT.reverse_count = 0U; GPT.reverse_count < 12U; GPT.reverse_count ++)
                {
                    GPT.ch_rev_bit_data[GPT.reverse_count] =                            /* Reverse the channel data bits to MSB first.*/
                                            GPT.ch_bit_data[ GPT.data_bit_count ];
                    GPT.ch_rev_bit_data[GPT.reverse_count] =                            /* Move the reversed channel data bits to the correct location channel data location.*/
                        GPT.ch_rev_bit_data[GPT.reverse_count] << GPT.data_bit_count;
                    GPT.ch_data[ GPT.data_ch_count ] = GPT.ch_data[ GPT.data_ch_count ] /* Apply the reversed data bits to the correct channel data, MSB first.*/
                                            | GPT.ch_rev_bit_data[GPT.reverse_count];
                    if(GPT.data_bit_count > 0U)
                    {
                        GPT.data_bit_count = GPT.data_bit_count - 1U;
                    }
                    
                }
                REPORT.data[GPT.data_ch_count + 12U] = GPT.ch_data[ GPT.data_ch_count ] && 0xFF00;
                REPORT.data[GPT.data_ch_count + 13U] = GPT.ch_data[ GPT.data_ch_count ] && 0x00FF;
                Clear_Status( 7 );                                                      /* Show that we received good data.*/
                if(GPT.data_ch_count == 19U)                                            /* testing only.*/
                {
                    Nop();
                }
                if(GPT.data_ch_count <= 20U)                                            /* Add up the channel data bits for the checksum.*/
                {
                    GPT.first_sum = GPT.first_sum + GPT.ch_data[ GPT.data_ch_count ];
                }

                GPT.int_count = 0U;
                if(GPT.data_ch_count > 20U)                                             /* If we have received all of the data for a transmission,*/
                {
                    GPT.tmrIntTriggered =  false;                                       /* Reset the variables.*/
                    GPT.data_ch_count = 0U;
                    GPT.data_sync_received_flag = false;
                    (void) memset( GPT.ch_bit_data, 0, 12);                             /* Clear the channel data bit arrays.*/
                    (void) memset( GPT.ch_rev_bit_data, 0, 12);
                    
                    DRV_TMR2_CounterClear();                                            /* Reset the Timer 2 count.*/
                    GPT.Rx_state = GPT_RX_STATE_CRC;
                    count = 0U;
                }
                else                                                                    /* If we have not received all of the data for a transmission,*/
                {
                    GPT.tmrIntTriggered =  false;                                       /* reset the 200uS timer flag.*/
                    GPT.data_ch_count = GPT.data_ch_count + 1U;                         /* Increment the channel data counter.*/
                    GPT.data_sync_received_flag = false;
//                    GPT.Rx_state = GPT_RX_STATE_SYNC_DATA;
                    
                    (void) memset( GPT.ch_bit_data, 0, 12);                             /* Clear the channel data bit arrays.*/
                    (void) memset( GPT.ch_rev_bit_data, 0, 12);
                    DRV_TMR2_CounterClear();                                            /* Reset the Timer 2 count.*/
//                    (void)DRV_TMR2_Start();                                             /* Start the timer again.*/
                    count = 0U;
                    GPT.Rx_state = GPT_RX_STATE_IDLE;                                   /* Move on to wait for another sync data bit.*/
//                    DRV_TMR_AlarmEnable(GPT.tmrHandle, true);
//                    DRV_TMR_Start(GPT.tmrHandle);
                }
            }
//            DRV_TMR_AlarmEnable(GPT.tmrHandle, true);
//            DRV_TMR_Start(GPT.tmrHandle); 
//            GPT.tmrIntTriggered =  false;
        }
        break;
        
        case GPT_RX_STATE_SYNC_CRC:
        {
          
        }
        break;
        
        case GPT_RX_STATE_CRC:
        {
            GPT.version = (GPT.ch_data[ 21 ] & 0x000C)>>2;
            GPT.CRC = (GPT.ch_data[ 21 ] & 0x0FF0)>> 4;
            GPT.first_sum_LSB = GPT.first_sum & 0x00FF;
            GPT.first_sum_MSB = (GPT.first_sum & 0xFF00)>>8;
            GPT.second_sum = GPT.first_sum_LSB + GPT.first_sum_MSB;
            count = 1U;
            gpt_timer_count[count] = GPT.data_timer_value;                              /* Debug only. Store timer values.*/
            Nop();
            GPT.sync_timer_started_flag = false;                                        /* Reset variables.*/
            GPT.sync_timer_value = 0U;  
            GPT.int_count = 0U;
            GPT.data_sync_received_flag = false;
            GPT.data_timer_started_flag = false;
            GPT.null_timer_complete = false;
            GPT.sync_data_timer_value = 0U;
            GPT.sync_timer_started_flag = false;
            GPT.sync_bit_count = 0U; 
            GPT.data_count = 0U;
            GPT.data_ch_count = 0U;
            GPT.int_count = 0U;
            GPT.data_bit_count = 0U;
            GPT.Rx_state = GPT_RX_STATE_IDLE;                                           /* Move on to wait for another sync bit.*/
//            Init_GPT( );
            

        }
        break;
        
		default:
        {
            /*Comment.*/
        }
		break;
	} 
}

/*************************************************************************************** 
  Function:
    static void GPT_PROCESS_Tasks( void )
 
  Summary:
    This routine is the GPT_PROCESS_Tasks function.  It defines the (GPT_PROCESS) 
    state machine and core logic.

  Remarks:
    Refer to the man.h interface header for function usage details.
 */

static void GPT_PROCESS_Tasks( void )
{
	switch( GPT.Process_state )
	{
		case GPT_PROCESS_STATE_IDLE:                                                    /* Wait to process another message.*/
        {
            
        }
		break;

		case GPT_PROCESS_STATE_PARSE:                                                   /* Started in GPT timer expires.*/
        {
            Decode_GPT();                                                               /* Decode received GPT array.*/
            Package_GPT();                                                              /* Convert to a 4 Byte Array.*/
            GPT.Process_state = GPT_PROCESS_STATE_TEST;                                 /* Move on to see if it is a valid message.*/
        }
        break;
        
        case GPT_PROCESS_STATE_TEST:
        {
//            Test_GPT();                                                                 /* Test if we received a good GPT response.*/            
            Flush_Buffer_GPT();                                                         /* Flush the GPT buffers for another message.*/
            fnp = 0U;                                                                   /* Reset index counter for storing incoming GPT message.*/
            count = 0U;
            GPT.process_complete_flag = true;                                           /* Set flag to show GPT processing is complete.*/
            GPT.Process_state = GPT_PROCESS_STATE_IDLE;                                 /* Set this machine to idle.*/
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
    static	void Check_GPT( void )

  Summary:
    GPT data is validated by a checksum.  The checksum is calculated as follows:
    1.	Each channel value is added into a 16-bit register, any overflow is ignored.
    2.	The high and low bytes of this 16-bit register are summed into an 8-bit 
        register with any overflow ignored.
    3.	The resulting 8-bit value is the checksum. If each channel register is full 
        (all 1?s) the checksum value is 0x3A (decimal 58).


  Remarks:
    Refer to the gpt.h interface header for function usage details.
 */

static void Check_GPT( void )
{
	uint8_t  cnt2;                                                                      /* Counter for the GPT answer array.*/

	for( cnt2 = 0U; cnt2 < 21U; cnt2++ )                                                /* Package GPT bits.*/
	{
        GPT.data_sum = GPT.data_sum + GPT.ch_data[cnt2];
    }
    GPT.data_sum_high = ((GPT.data_sum & 0xFF00)>> 8);
    GPT.data_sum_low = GPT.data_sum & 0x00FF;
    GPT.checksum = GPT.data_sum_high + GPT.data_sum_low;
    
    if(GPT.checksum == GPT.crc_data[0])
    {
        GPT.data_good_flag = true;
    }   
    
//		GPT.msg[ 0 ] = GPT.msg[ 0 ] | GPT.ans[ cnt2 + 1U ];                             /* First byte of message array takes answer array elements 1 through 8.*/
//		GPT.msg[ 1 ] = GPT.msg[ 1 ] | GPT.ans[ cnt2 + 9U ];                             /* Second byte of message array takes answer array elements 9 through 16.*/
//		GPT.msg[ 2 ] = GPT.msg[ 2 ] | GPT.ans[ cnt2 + 17U ];                            /* Third byte of message array takes answer array elements 17 through 24.*/
//		GPT.msg[ 3 ] = GPT.msg[ 3 ] | GPT.ans[ cnt2 + 25U ];                            /* Fourth byte of message array takes answer array elements 25 through 32.*/
//		if( cnt2 < 11U )
//		{
//			GPT.msg[ 0 ] = GPT.msg[ 0 ]<<1;                                             /* Left-shift message elements to make room for next array answer element.*/
//			GPT.msg[ 1 ] = GPT.msg[ 1 ]<<1;
//			GPT.msg[ 2 ] = GPT.msg[ 2 ]<<1;
//			GPT.msg[ 3 ] = GPT.msg[ 3 ]<<1;
//		}
//	}                                                                                   /* Package Manchester bits Ends.*/
}

/*************************************************************************************** 
  Function:
    void GPT_Tasks ( void )

  Summary:
   This routine is the GPT_tasks function.  It defines the (GPT) state machine 
   and core logic.

  Remarks:
    Refer to the gpt.h interface header for function usage details.
 */
void GPT_Tasks ( void )                                                             /* GPT state machine.*/
{ 
    switch ( GPT.state )                                                            /* Check the machines current state.*/                                                                        
    {
        case GPT_STATE_INIT:                                                        /* This machines initial state.*/
        {
//            (void)memset(GPT.wl_current,0,200);                                     /* Initialize the array values to zero.*/
//            (void)memset(GPT.wl_voltage,0,200);
//            (void)memset(GPT.wl_resistance,0,200);
//            GPT.new_current_values_flag = false;                                    /* Initialize the flag to false.*/
//            GPT.array_count = 0U;                                                   /* Initialize the array counter to zero.*/
//            GPT.curr_count = 0U;                                                    /* Initialize the current array position for threshold check.*/
//            GPT.prev_count = 0U;                                                    /* Initialize the previous array position for threshold check.*/           
//            GPT.state = GPT_STATE_WAIT;                                         /* Move on to wait for an auto start command.*/
//            GPT.spike_found = false;                                                /* Initialize flag when current spike is found.*/
//            GPT.cur_threshold = 99;                                                 /* Difference in mA between current and previous array values.*/
//            GPT.current = 0U;
//            Set_Status(2);                                                              /* Set this bit to show a detonation has not been detected.*/
//            GPT.status_2_flag = true;
//            GPT.wl_res_threshold = 100.0F;
//            GPT.res_curr_count = 0U;
//            GPT.res_prev_count = 0U;            
//            GPT.ignore_shot_flag = false;
            
        }
        break;
        
        case GPT_STATE_WAIT:
        {
//            if ((HV_PS.ramp_start == true) && (HV_T_PS.state == HVPS_TEST_STATE_IDLE)   /* If we have started an auto ramp for the HVPS, no test is running,*/
//               &&(HV_PS.pot_switch == false) &&(GPT.ignore_shot_flag == false))     /* and the HVPS control pot is off and we are not ignoring shot detection,*/  
//            {
//                if((WL_SPS.voltage > 20U))                    /* If the wireline current is greater than 300mA and the wireline */                                                                                      
//                                                                                        /* voltage is greater than 20V */
//                {
//                    GPT.state = GPT_STATE_CHECK;                                /* start checking for a current spike.*/
//                }
//            }
        }
        break;
        
        case GPT_STATE_CHECK:
        {
//            if((HV_PS.run_time_count <=  HV_PS.run_time -1U) && 
//                ((SW_COM.S1_state == RLY_FIRE) || (SW_COM.S3_state == RLY_ARM_CF_AUTO)))
//            {    
//                if(GPT.new_current_values_flag == true)                             /* If a new current reading is available,*/
//                {
//                    GPT.new_current_values_flag = false;                            /* Reset the flag.*/
//                    
//                    GPT.voltage = WL_SPS.voltage;
//                    GPT.wl_current[GPT.array_count] = GPT.current;          /* Put the reading into the array.*/
//                    GPT.wl_voltage[GPT.array_count] = GPT.voltage;          /* Put the reading into the array.*/    
//                    GPT.wl_resistance[GPT.array_count] =
//                            (GPT.wl_voltage[GPT.array_count]
//                            /(GPT.wl_current[GPT.array_count]/1000));
//
//                    GPT.array_count = GPT.array_count +1U;                      /* Increment array counter.*/
//                    if(GPT.array_count > 49U)                                       /* If the array counter has exceeded the limit,*/
//                    {                    
//                        GPT.array_count = 0U;                                       /* reset the counter.*/                  
//                    }
//                    if(GPT.curr_count > 49U)                                        /* If the current array position has exceeded the limit,*/
//                    {
//                        GPT.curr_count = 0U;                                        /* reset the current array position.*/
//                    }
//                    if(GPT.prev_count > 49U)                                        /* If the previous array position has exceeded the limit,*/
//                    {
//                        GPT.prev_count = 0U;                                        /* reset the previous array position.*/
//                    }   
//                    if(GPT.res_curr_count > 49U)                                    /* If the current array position has exceeded the limit,*/
//                    {
//                        GPT.res_curr_count = 0U;                                    /* reset the current array position.*/
//                    }
//                    if(GPT.res_prev_count > 49U)                                    /* If the previous array position has exceeded the limit,*/
//                    {
//                        GPT.res_prev_count = 0U;                                    /* reset the previous array position.*/
//                    }   
//                    if((GPT.wl_resistance[GPT.res_curr_count] 
//                            - GPT.wl_resistance[GPT.res_prev_count]) 
//                            < GPT.wl_res_threshold)
//                    {
//                        GPT.res_prev_count = GPT.res_curr_count;                /* set the previous array position to the current array position and*/
//                        GPT.res_curr_count = GPT.res_curr_count + 1U;           /* increment the current array position.*/
//                    }
//                    else
//                    {
//                        Clear_Status(2);                                                /* Clear the status bit to show we found a detonation.*/
//                        GPT.status_2_flag = false;                                  /* Set to false to follow status bit.*/
//                        GPT.spike_found = true;                                     /* Set the flag that the current spike has been found and*/
//                        GPT.res_curr_count = 0U;                                    /* reset the array position counters for the next spike.*/
//                        GPT.res_prev_count = 0U;
//                        GPT.curr_count = 0U;                                        /* reset the array position counters for the next spike.*/
//                        GPT.prev_count = 0U;
//                        (void) memset(GPT.wl_current,0,200);                        /* Clear the wire-line current values.*/
//                        GPT.current = 0U;                                           /* Clear the latest current value.*/
//                        GPT.voltage = 0U;                                           /* Clear the latest voltage value.*/                    
//                        GPT.array_count = 0U;                                       /* Reset the counter.*/ 
//                        GPT.state = GPT_STATE_IDLE;
//                        (void) memset(GPT.wl_voltage,0,200);
//                        (void) memset(GPT.wl_resistance,0,200);               
//                    }
//                    if((GPT.wl_current[GPT.curr_count] <                        /* If the current wire line current is less than the previous wire line current,*/
//                                            GPT.wl_current[GPT.prev_count]))
//                    {
//                        if(((GPT.wl_current[GPT.prev_count] -                   /* and if the difference between them is greater than the threshold,*/
//                            GPT.wl_current[GPT.curr_count]) >= 
//                                                              GPT.cur_threshold)
//                            && (HV_PS.run_complete_flag == false))
//                        {
//                            Clear_Status(2);                                            /* Clear the status bit to show we found a detonation.*/
//                            GPT.status_2_flag = false;
//                            GPT.spike_found = true;                                 /* Set the flag that the current spike has been found and*/
//                            GPT.curr_count = 0U;                                    /* reset the array position counters for the next spike.*/
//                            GPT.prev_count = 0U;
//                            GPT.res_curr_count = 0U;                                /* reset the array position counters for the next spike.*/
//                            GPT.res_prev_count = 0U;
//                            (void) memset(GPT.wl_current,0,200);                    /* Clear the wire-line current values.*/
//                            GPT.current = 0U;                                       /* Clear the latest current value.*/
//                            GPT.array_count = 0U;                                   /* Reset the counter.*/ 
//                            GPT.state = GPT_STATE_IDLE;
//                            (void) memset(GPT.wl_voltage,0,200);
//                            (void) memset(GPT.wl_resistance,0,200);                          
//                        }
//                        else                                                            /* Otherwise,*/
//                        {
//                            GPT.prev_count = GPT.curr_count;                    /* set the previous array position to the current array position and*/
//                            GPT.curr_count = GPT.curr_count + 1U;               /* just increment the current array position counter.*/                        
//                        }
//                    }
//                    else if (GPT.spike_found == false) 
//                    {
//                        GPT.prev_count = GPT.curr_count;                        /* set the previous array position to the current array position and*/
//                        GPT.curr_count = GPT.curr_count + 1U;                   /* just increment the current array position counter.*/
//
//                        /*Comment.*/
//                    }                    
//                }   
//            }
//            else
//            {
//                GPT.curr_count = 0U;                                                /* reset the array position counters for the next spike.*/
//                GPT.prev_count = 0U;
//                GPT.res_curr_count = 0U;                                            /* reset the array position counters for the next spike.*/
//                GPT.res_prev_count = 0U;
//                (void) memset(GPT.wl_current,0,200);                                /* Clear the wire-line current values.*/
//                GPT.current = 0U;                                                   /* Clear the latest current value.*/
//                GPT.array_count = 0U;                                               /* Reset the counter.*/ 
//                GPT.state = GPT_STATE_IDLE;
//                (void) memset(GPT.wl_voltage,0,200);
//                (void) memset(GPT.wl_resistance,0,200);            
//            }
//            if(                      /* This added to shut things down if current limit reached.*/
//                    (SW_COM.S3_state == RLY_ARM_CF_AUTO))
//            {                                                                           /* Actions emulate a spike being found.*/
//                Clear_Status(2);                                                        /* Clear the status bit to show we reached current limit.*/
//                GPT.status_2_flag = false;
//                GPT.spike_found = true;                                             /* Set the flag that the current spike has been found and*/
//                GPT.curr_count = 0U;                                                /* reset the array position counters for the next spike.*/
//                GPT.prev_count = 0U;
//                GPT.res_curr_count = 0U;                                            /* reset the array position counters for the next spike.*/
//                GPT.res_prev_count = 0U;
//                (void) memset(GPT.wl_current,0,200);                                /* Clear the wire-line current values.*/
//                GPT.current = 0U;                                                   /* Clear the latest current value.*/
//                GPT.array_count = 0U;                                               /* Reset the counter.*/ 
//                GPT.state = GPT_STATE_IDLE;
//                (void) memset(GPT.wl_voltage,0,200);
//                (void) memset(GPT.wl_resistance,0,200);                
//            }
        }
        break; 
        
        case GPT_STATE_IDLE:
        {
//            if(HV_PS.ramp_start == false)                                               /* If the command has been completed in hvps.c,*/
//            {
//                GPT.state = GPT_STATE_WAIT;                                     /* Move on to wait for an auto start command.*/
//            }
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
    static	void Flush_Buffer_GPT( void )

  Summary:
    Function to reset GPT.level[], GPT.TIME[], GPT.msg[] and GPT.PREAMBLE[] buffers. 

  Remarks:
    Refer to the man.h interface header for function usage details.
 */

static	void Flush_Buffer_GPT( void )
{	
//	(void) memset( GPT.time, 0, 96);
//	(void) memset( GPT.level, 0, 96);
//    (void) memset( GPT.msg, 0, 4);
//    (void) memset( GPT.preamble,0, 5);
}

/*!************************************************************************************* 
  Function:
    static	void Package_GPT( void )

  Summary:
    GPT is decoded, the 1 X 32 answer array is packed into 
    a 4 X 8 bit message array.

  Remarks:
    Refer to the gpt.h interface header for function usage details.
 */

static void Package_GPT( void )
{
	uint8_t  cnt2;                                                                      /* Counter for the GPT answer array.*/

	for( cnt2 = 0U; cnt2 < 8U; cnt2++ )                                                 /* Package GPT bits.*/
	{
		GPT.msg[ 0 ] = GPT.msg[ 0 ] | GPT.ans[ cnt2 + 1U ];                             /* First byte of message array takes answer array elements 1 through 8.*/
		GPT.msg[ 1 ] = GPT.msg[ 1 ] | GPT.ans[ cnt2 + 9U ];                             /* Second byte of message array takes answer array elements 9 through 16.*/
		GPT.msg[ 2 ] = GPT.msg[ 2 ] | GPT.ans[ cnt2 + 17U ];                            /* Third byte of message array takes answer array elements 17 through 24.*/
		GPT.msg[ 3 ] = GPT.msg[ 3 ] | GPT.ans[ cnt2 + 25U ];                            /* Fourth byte of message array takes answer array elements 25 through 32.*/
		if( cnt2 < 7U )
		{
			GPT.msg[ 0 ] = GPT.msg[ 0 ]<<1;                                             /* Left-shift message elements to make room for next array answer element.*/
			GPT.msg[ 1 ] = GPT.msg[ 1 ]<<1;
			GPT.msg[ 2 ] = GPT.msg[ 2 ]<<1;
			GPT.msg[ 3 ] = GPT.msg[ 3 ]<<1;
		}
	}                                                                                   /* Package GPT bits Ends.*/
}

/*!************************************************************************************* 
  Function:
    static	void Decode_GPT( void )

  Summary:
    Function to decode the GPT response from a GPT tool.

  Remarks:
    Refer to the gpt.h interface header for function usage details.
 */

static	void Decode_GPT( void )
{
	uint8_t  cnt;
	uint8_t  cnt2;
	cnt  = 0U;                                                                          /* Counter for incoming buffer.*/
	cnt2 = 0U;                                                                          /* Counter for GPT answer.*/

//	while( cnt2 < ( NoGptBits + 2U ) )                                                  /* While No of GPT Bits + 2*/
//	{                                                                                   /* 2 extra transitions to accommodate the 1st (tickle) bit*/
//                                                                                        /* of the pre-amble.*/
//		if( GPT.level[ cnt ] == 0x01U )                                                 /* If the present level is a 1 then it must be a One Bit.*/                                                                                      
//		{
//			GPT.ans[ cnt2 ] = 0x01U;                                                    /* Set the answer to a one.*/
//		}
//		else                                                                            /* Otherwise,*/
//		{
//			GPT.ans[ cnt2 ] = 0x00U;                                                    /* Set the answer to a zero.*/                                
//		}
//		if( GPT.time[ cnt + 1U ] == HalfBit )                                           /* If the time of next array element i.e.*/                                                                                        
//		{                                                                               /* the other part of the waveform is a Half bit then*/                                                                               
//			cnt++;                                                                      /* increment the incoming buffer counter twice.*/
//			cnt++;
//		}
//		else                                                                            /* Else increment only once.*/
//		{
//			cnt++;
//		}
//		cnt2++;                                                                         /* Answer counter to be incremented by only one.*/                                                                                        
//	}
}

/***************************************************************************************
 End of File
 */
