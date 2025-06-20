/**************************************************************************************/
/** \file commands.c
  
  Company:
    Hunting Titan
  
  File Name:
   commands.c

  Summary:
    This file contains the source code for responding to commands sent from the host.

  Description:
    This file contains the source code for responding to commands sent from the host. 
    All commands are processed here.  Protocol A commands are for controlling the PIB
    itself.  Protocol B commands are for communicating with a PerfSwitch.  The states 
    are configured so that other system tasks can be maintained while these tasks 
    are waiting for an event to occur.
 
 **************************************************************************************/

/**************************************************************************************/
/**************************************************************************************/
/* Section: Included Files                                                            */
/**************************************************************************************/
/**************************************************************************************/

#include "commands.h"
#include "crc.h"

#include "statusst.h"
#include "commmodule.h"
#include "app.h"

#include "switches.h"
#include "gamma.h"
#include "high_side.h"

#include "gpt.h"
#include "system_okay.h"
#include "hid.h"
#include "report.h"

#include <string.h>
#include <stdbool.h>

/**************************************************************************************/
/**************************************************************************************/
/* Section: Defines                                                                   */
/**************************************************************************************/
/**************************************************************************************/
                                                                                        /* These defines are the various protocol commands.*/

                                                                                        /* Protocol A Commands Start.*/

                  
#define     Get_FP_Switch_Settings              0x5DU                                   /*!< Get front panel switch settings.*/
#define     PA_COM_18                           0x60U                                   /*!< Available Protocol A command (PA_COM).*/
#define     PA_COM_19                           0x61U                                   /*!< Available Protocol A command (PA_COM).*/
#define     CPS_Fault_Ack                       0x64U                                   /*!< Acknowledge for CPS fault.*/
#define     Initialize                          0x65U                                   /*!< Reset PIB.*/
#define     Gamma_Enable                        0x66U                                   /*!< Enable Gamma Operation.*/
#define     Gamma_Disable                       0x67U                                   /*!< Disable Gamma Operation.*/
#define     Gamma_Power_On                      0x68U                                   /*!< Turn on wireline supply for gamma operation.*/
#define     Gamma_Power_Off                     0x69U                                   /*!< Turn off wireline supply for gamma operation.*/
#define     Log_Panel_Bypass                    0x6AU                                   /*!< Set logging panel to bypass.*/
#define     Log_Panel_GPT                       0x6BU                                   /*!< Set logging panel to GPT mode.*/
#define     Log_Panel_Gamma                     0x6CU                                   /*!< Set logging panel to Gamma/CCL mode.*/
#define     Log_Panel_HSI                       0x6DU                                   /*!< Set logging panel to High Side mode.*/
#define     Transimit_Data                      0x6EU                                   /*!< Transmit tool data to PC host.*/
#define     PA_COM_29                           0x6FU
#define     PA_COM_30                           0x70U
                                                                                        /* Protocol A Commands end.*/




#define		NoOfCommands		  22

/**************************************************************************************/
/**************************************************************************************/
/* Section: Type Definition                                                           */
/**************************************************************************************/
/**************************************************************************************/
        



/**************************************************************************************/
/**************************************************************************************/
/* Section: Structure Data and Local Variables                                        */
/**************************************************************************************/
/**************************************************************************************/
/* COMMAND Data

  Summary:
    These structures hold required data.

  Description:
    These structures hold required data. These are here to link these 
    structures for use by the local functions.
  Remarks:
 * 
    These are defined in command.h
*/
COMMAND_DATA CMD;
APP_DATA appData;

static COMMAND_STATES CMD_STATES;

/***************************************************************************************
*	$GLOBAL VARIABLES
***************************************************************************************/

bool DepthStatus = true;


/**************************************************************************************/
/**************************************************************************************/
/* Section: State Machine Functions                                                   */
/**************************************************************************************/
/**************************************************************************************/

/*************************************************************************************** 
  Function:
    void COMMAND_Tasks ( void )

  Summary:
   This routine is the COMMAND_Tasks function.  It defines the (COMMAND) state 
   machine and core logic.

  Remarks:
    Refer to the commands.h interface header for function usage details.
 */

void COMMAND_Tasks( void )                                                              /* COMMAND state machine.*/
{    
    switch (CMD.state)                                                                  /* Check the machines current state.*/
    {
        case COMMAND_STATE_INIT:                                                        /* This machines initial state.*/
        {
            CMD.process_complete_flag = true;                                           /* Flag to show the command execution has been completed.*/
            CMD.state = COMMAND_STATE_WAIT;                                             /* Move on to wait for a host command.*/
            CMD.cmd_size = 1U;                                                          /* The number of bytes in a valid command.*/
            (void)memset(CMD.command, 0, CMD.cmd_size);                                 /* Initialize the command bytes to 0 value.*/ 
            CMD.b_command_complete_flag = false;                                        /* Flag to show if a Protocol B command is complete.*/
//            CMD.sw_status_bit_check = true;                                             /* Flag to use status bits from PerfSwitch.*/
        }
        break;
        
        case COMMAND_STATE_WAIT:                                                        /* Wait here for a command to be sent from the host.*/
        {
            if(CMD.process_complete_flag == false)                                      /* If we have a command that needs processing,*/
            {                                                                           /* (set false in commmodule.c)*/
//                CMD.state = COMMAND_STATE_CRC_CHECK;                                    /* Move on to check the command array CRC.*/
                CMD.state = COMMAND_STATE_EXECUTE_CMD;                                    /* Move on to check the command array CRC.*/
            }
        }
        break;
        
        case COMMAND_STATE_CRC_CHECK:                                                   /* Calculate the CRC of the sent command array.*/
        {
//            CMD.crc = Calc_CRC_Array( 6, CMD.command );                                 /* Calculate the command array CRC.*/
//            if( CMD.command[ 6 ] == CMD.crc )                                           /* If the answer agrees with the fifth array element,*/
//            {
//                Clear_Status(16);                                                       /* Clear the CRC Error status bit and*/
//                CMD.state = COMMAND_STATE_EXECUTE_CMD;                                  /* move on to execute the command.*/
//            }
//            else                                                                        /* Otherwise,*/
//            {
//                Set_Status(16);                                                         /* set the CRC Error Bit and*/
//                Prepare_Return_A(CMD.command[ 0 ], 0, 0);                               /* prepare the message to be sent back to the host.*/
//                CMD.state = COMMAND_STATE_WAIT;                                         /* Wait for another command to process.*/                
//                CMD.process_complete_flag = true;                                       /* Set this flag to show we have completed processing the command.*/ 
//            }
        }
        break;
        
        case COMMAND_STATE_EXECUTE_CMD:                                                 /* Execute the command.*/
        {
//            if((CMD.command[ 0 ] >= 0x30U) && (CMD.command[ 0 ] <= 0x45U))              /* If the command is within the Protocol A Auto Command range,*/
//            {
//                Execute_Auto_Protocol_A();                                              /* execute the command here.*/
//                CMD.state = COMMAND_STATE_WAIT;                                         /* Wait for another command to process.*/
//            }
            if((CMD.command[ 0 ] >= 0x50U) && (CMD.command[ 0 ] <= 0x70U))              /* If the command is within the Protocol A Command range,*/
            {
                Execute_Protocol_A();                                                   /* execute the command here.*/
                CMD.state = COMMAND_STATE_WAIT;                                         /* Wait for another command to process.*/
            }
//            else if((CMD.command[ 0 ] >= 0x80U) && (CMD.command[ 0 ] <= 0xB0U))         /* If the command is within the Protocol B Command range,*/
//            {
//                if(CMD.b_command_complete_flag == true)                                 /* If we have completed processing a protocol B command,*/
//                {
//                    CMD.b_command_complete_flag = false;                                /* Reset the flag.*/
//                    CMD.state = COMMAND_STATE_WAIT;                                     /* Wait for another command to process.*/            
//                    CMD.process_complete_flag = true;                                   /* Set this flag to show we have completed processing the command.*/ 
//                    CMD.command[ 0 ] = 0x00U;                                           /* Reset the command.*/
//                }
//                
//                if(FSK.send_message_complete_flag == false)                             /* If we have not sent the command yet,*/              
//                {
//                    Execute_Protocol_B();                                               /* execute the command here.*/
//                }
//            }
            else                                                                        
            {
                /*Comment.*/
            }      
        }
        break;
        
        default:
        {
            
        }
        break;
    }
}

/**************************************************************************************/
/**************************************************************************************/
/* Section: Local Functions                                                           */
/**************************************************************************************/
/**************************************************************************************/

/*!************************************************************************************* 
  Function:
    static void Execute_Auto_Protocol_A (void)

  Summary:
   Function to execute a auto protocol A command.

  Remarks:
    Refer to the commands.h interface header for function usage details.
 */

static void Execute_Auto_Protocol_A (void)
{
    switch( CMD.command[ 0 ] )
    {

        
        default:
        {
            CMD.process_complete_flag = true;                                           /* Set this flag to show we have completed processing the command.*/
            Prepare_Return_A(CMD.command[ 0 ], 0, 0);                                   /* Prepare the protocol A response.*/			
            CMD.command[ 0 ] = 0x00U;                                                   /* Reset the Command received byte.*/
        }
        break;
    }    
}
/*!************************************************************************************* 
  Function:
    static void Execute_Protocol_A (void)

  Summary:
   Function to execute a protocol A command.

  Remarks:
    Refer to the commands.h interface header for function usage details.
 */

static void Execute_Protocol_A (void)
{
	switch( CMD.command[ 0 ] )
    {
//        case Get_PIB_Revision:                                                          /* 5Bh*/
//        {
//            CMD.process_complete_flag = true;                                           /* Set this flag to show we have completed processing the command.*/
////            Prepare_Return_A(CMD.command[ 0 ], 0, APP.RevNumber);                       /* Prepare the protocol A response.*/		
//            CMD.command[ 0 ] = 0x00U;                                                   /* Reset the Command received byte.*/
//        }
//        break;
//
//        case Get_PIB_Status:                                                            /* 5Ch*/
//        {
//            CMD.process_complete_flag = true;                                           /* Set this flag to show we have completed processing the command.*/
//            Prepare_Return_A(CMD.command[ 0 ], 0, 0);                                   /* Prepare the protocol A response.*/			
//            CMD.command[ 0 ] = 0x00U;                                                   /* Reset the Command received byte.*/
//        }
//        break;
        
        case Get_FP_Switch_Settings:                                                    /* 5Dh*/
        {
            CMD.process_complete_flag = true;                                           /* Set this flag to show we have completed processing the command.*/
            Prepare_Return_A(CMD.command[ 0 ], SWITCH.store_buffer[ 1 ],
                    SWITCH.store_buffer[ 0 ]);                                          /* Prepare the protocol A response.*/			
            CMD.command[ 0 ] = 0x00U;                                                   /* Reset the Command received byte.*/
        }
        break;

//        case Close_COMM_Relay:                                                          /* 5Eh*/ 
//        {
////            RLY_COMMOn();                                                               /* Close this relay before communications with a PerfSwitch begins.*/
//            Set_Status(11);                                                             /* Set status bit 10 to show OR relay is closed.*/
//            CMD.process_complete_flag = true;                                           /* Set this flag to show we have completed processing the command.*/
//            Prepare_Return_A(CMD.command[ 0 ], 0, 0);                                   /* Prepare the protocol A response.*/		
//            CMD.command[ 0 ] = 0x00U;                                                   /* Reset the Command received byte.*/
//        }
//        break;
//
//        case Open_COMM_Relay:                                                           /* 5Fh*/
//        {
////            RLY_COMMOff();                                                              /* Open this relay when communications with PerfSwitch are complete.*/            
//            Clear_Status(11);                                                           /* Clear status bit 10 to show OR relay is open.*/
//            CMD.process_complete_flag = true;                                           /* Set this flag to show we have completed processing the command.*/
//            Prepare_Return_A(CMD.command[ 0 ], 0, 0);                                   /* Prepare the protocol A response.*/		
//            CMD.command[ 0 ] = 0x00U;                                                   /* Reset the Command received byte.*/
//        }
//        break;

        case PA_COM_18:                                                                  /* 60h*/
        {                                                                                                                 
            CMD.process_complete_flag = true;                                           /* Set this flag to show we have completed processing the command.*/
            Prepare_Return_A(CMD.command[ 0 ], 0, 0);                                   /* Prepare the protocol A response.*/		
            CMD.command[ 0 ] = 0x00U;                                                   /* Reset the Command received byte.*/ 
        }
        break;
        
        case PA_COM_19:                                                                 /* 61h*/
        {                                                                               
            CMD.process_complete_flag = true;                                           /* Set this flag to show we have completed processing the command.*/
            Prepare_Return_A(CMD.command[ 0 ], 0, 0);                                   /* Prepare the protocol A response.*/		
            CMD.command[ 0 ] = 0x00U;                                                   /* Reset the Command received byte.*/
        }
        break;

        case CPS_Fault_Ack:                                                             /* 64h*/
        {
            Clear_Status(4);                                                            /* Clear status bit 3 to clear the overvoltage bit.*/
            Clear_Status(13);                                                           /* Clear status bit 13 to clear the overcurrent bit.*/
            CMD.process_complete_flag = true;                                           /* Set this flag to show we have completed processing the command.*/
            Prepare_Return_A(CMD.command[ 0 ], 0, 0);                                   /* Prepare the protocol A response.*/		
            CMD.command[ 0 ] = 0x00U;                                                   /* Reset the Command received byte.*/
        }
        break;

        case Initialize:                                                                /* 65h*/
        {
            CMD.process_complete_flag = true;                                           /* Set this flag to show we have completed processing the command.*/
            Prepare_Return_A(CMD.command[ 0 ], 0, 0);                                   /* Prepare the protocol A response.*/		
            CMD.command[ 0 ] = 0x00U;                                                   /* Reset the Command received byte.*/
        }
        break;
        
        case Gamma_Enable:                                                              /* 66h*/
        {
            GAM.gamma_enable_flag = true;                                               /* Set this flag to enable the panel for gamma counts.*/
            CMD.process_complete_flag = true;                                           /* Set this flag to show we have completed processing the command.*/
            Prepare_Return_A(CMD.command[ 0 ], 0, 0);                                   /* Prepare the protocol A response.*/		
            CMD.command[ 0 ] = 0x00U;                                                   /* Reset the Command received byte.*/
        }
        break;
        
        case Gamma_Disable:                                                             /* 67h*/
        {
            GAM.gamma_enable_flag = false;                                              /* Set this flag to disable the panel for gamma counts.*/ 
            CMD.process_complete_flag = true;                                           /* Set this flag to show we have completed processing the command.*/
            Prepare_Return_A(CMD.command[ 0 ], 0, 0);                                   /* Prepare the protocol A response.*/		
            CMD.command[ 0 ] = 0x00U;                                                   /* Reset the Command received byte.*/
        }
        break;
        
        case Gamma_Power_On:                                                            /* 68h*/
        {
            GAM.wireline_enable_flag = true;
            CMD.process_complete_flag = true;                                           /* Set this flag to show we have completed processing the command.*/
            Prepare_Return_A(CMD.command[ 0 ], 0, 0);                                   /* Prepare the protocol A response.*/		
            CMD.command[ 0 ] = 0x00U;                                                   /* Reset the Command received byte.*/
        }
        break;
        
        case Gamma_Power_Off:                                                           /* 69h*/
        {
            GAM.wireline_enable_flag = false;
            CMD.process_complete_flag = true;                                           /* Set this flag to show we have completed processing the command.*/
            Prepare_Return_A(CMD.command[ 0 ], 0, 0);                                   /* Prepare the protocol A response.*/		
            CMD.command[ 0 ] = 0x00U;                                                   /* Reset the Command received byte.*/
        }
        break;
        
        case Log_Panel_Bypass:                                                          /* 6Ah*/
        {
            (void)memset(REPORT.data, 0, 64);
            SWITCH.command_flag = true;
            SWITCH.command_setting = 3U;
            CMD.process_complete_flag = true;                                           /* Set this flag to show we have completed processing the command.*/
            Prepare_Return_A(CMD.command[ 0 ], 0, 0);                                   /* Prepare the protocol A response.*/		
            CMD.command[ 0 ] = 0x00U;                                                   /* Reset the Command received byte.*/
        }
        break;
        
        case Log_Panel_GPT:                                                             /* 6Bh*/
        {
            (void)memset(REPORT.data, 0, 64);
            SWITCH.command_flag = true;
            SWITCH.command_setting = 1U;
            CMD.process_complete_flag = true;                                           /* Set this flag to show we have completed processing the command.*/
            Prepare_Return_A(CMD.command[ 0 ], 0, 0);                                   /* Prepare the protocol A response.*/		
            CMD.command[ 0 ] = 0x00U;                                                   /* Reset the Command received byte.*/
        }
        break;
        
        case Log_Panel_Gamma:                                                           /* 6Ch*/
        {
            (void)memset(REPORT.data, 0, 64);
            SWITCH.command_flag = true;
            SWITCH.command_setting = 2U;
            CMD.process_complete_flag = true;                                           /* Set this flag to show we have completed processing the command.*/
            Prepare_Return_A(CMD.command[ 0 ], 0, 0);                                   /* Prepare the protocol A response.*/		
            CMD.command[ 0 ] = 0x00U;                                                   /* Reset the Command received byte.*/
        }
        break;
        
        case Log_Panel_HSI:                                                             /* 6Dh*/
        {
            (void)memset(REPORT.data, 0, 64);
            SWITCH.command_flag = true;
            SWITCH.command_setting = 0U;
            CMD.process_complete_flag = true;                                           /* Set this flag to show we have completed processing the command.*/
            Prepare_Return_A(CMD.command[ 0 ], 0, 0);                                   /* Prepare the protocol A response.*/		
            CMD.command[ 0 ] = 0x00U;                                                   /* Reset the Command received byte.*/
        }
        break;
        
        case Transimit_Data:                                                             /* 6Eh*/
        {            
            appData.state = HID_STATE_TRANSMIT;
//            appData.hidDataReceived = true;
//            SWITCH.command_flag = true;
//            SWITCH.command_setting = 1U;
            CMD.process_complete_flag = true;                                           /* Set this flag to show we have completed processing the command.*/
            Prepare_Return_A(CMD.command[ 0 ], 0, 0);                                   /* Prepare the protocol A response.*/		
            CMD.command[ 0 ] = 0x00U;                                                   /* Reset the Command received byte.*/
        }
        break;
        
        default:
        {
            CMD.process_complete_flag = true;                                           /* Set this flag to show we have completed processing the command.*/
            Prepare_Return_A(CMD.command[ 0 ], 0, 0);                                   /* Prepare the protocol A response.*/			
            CMD.command[ 0 ] = 0x00U;                                                   /* Reset the Command received byte.*/
        }
        break;
    }
}

/*!************************************************************************************* 
  Function:
    bool Valid_Command( uchar8_t msg )

  Summary:
    Function receives a command for validation and returns a true if it is 
    a valid command.

  Remarks:
    Refer to the commands.h interface header for function usage details.
 */

bool Valid_Command( uchar8_t msg )
{
	bool ans;                                                                           /* Returned value from check.*/

    const uchar8_t CommandBitMap[NoOfCommands] ={0x65U,0x66U,0x67U,0x68U,0x69U,0x6AU,
          0x6BU,0x6CU,0x6DU,0x6EU,0x6FU,0x70U};
  
	ans = false;                                                                        /* Set response to false.*/
	if ((strchr( ( char * ) CommandBitMap, msg ) != NULL ) && ( msg != 0U ))            /* Perform a compare to look for the command in the list.*/
	{
		ans = true;                                                                     /* If we found a match, set to true.*/
	}
	else                                                                                /* Otherwise,*/
	{
  		ans = false;                                                                    /* set to false.*/
	}
	return ans;
}

/***************************************************************************************
 End of File
 */
