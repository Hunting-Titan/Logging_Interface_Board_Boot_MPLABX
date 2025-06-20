/**************************************************************************************/
/** \file commmodule.c
     
  Company:
    Hunting Titan
  
  File Name:
    commmodule.c

  Summary:
    This file contains the state machine code for the COMM operation.

  Description:
    This file contains the state machine code for the COMM operation.  It implements
    the logic of the COMM's state machine. This machine handles the communications 
    between the host and the PIB. The communications are received via a USB or UART 
    connection. If a valid command is received, it allows the command processing to 
    proceed.  The states are configured so that other system tasks can be 
    maintained while these tasks are waiting for an event to occur.     
*/
/**************************************************************************************/

/**************************************************************************************/
/**************************************************************************************/
/*  Section: Included Files                                                           */                                                      
/**************************************************************************************/
/**************************************************************************************/

#include "commmodule.h"
#include "fifo.h"
#include "statusst.h"
#include "commands.h"
#include "UART.h"
#include "USB.h"
#include "high_side.h"
#include "hid.h"
#include "report.h"

#include <stdbool.h>                                                                    /* Defines true, false.*/

/**************************************************************************************/
/**************************************************************************************/
/* Section: Structure Data and Local Variables                                        */
/**************************************************************************************/
/**************************************************************************************/

/**************************************************************************************/
/* COMM Data

  Summary:
    These structures hold the required states and variables to perform the COMM tasks.

  Description:
    These structures hold the required states and variables to perform the COMM tasks. 
    These are here to link these structures for use by the local functions.
 
  Remarks: 
    These are defined in commmodule.h
*/

COMM_DATA COMM;
APP_DATA appData;

static COMM_STATES C_STATES;

/**************************************************************************************/
/**************************************************************************************/
/* Section: Type Definition                                                           */
/**************************************************************************************/
/**************************************************************************************/
        
		

/**************************************************************************************/
/**************************************************************************************/
/* Section: State Machine Functions                                                   */
/**************************************************************************************/
/**************************************************************************************/

/*************************************************************************************** 
  Function:
    void COMM_Tasks ( void )

  Summary:
   This routine is the COMM_Tasks function.  It defines the (COMM) state machine and
   core logic.

  Remarks:
    Refer to the commmodule.h interface header for function usage details.
 */

void COMM_Tasks(void)
{
    switch ( COMM.state )                                                               /* Check the machines current state.*/                                                                        
    {
        case COMM_STATE_INIT:
        {
            COMM.processing = false;                                                    /* Initialize flag to show no message needs processing.*/
    
            COMM.rx_count = 0U;                                                         /* Set the receive counter to 0.*/
            COMM.tx_count = 0U;                                                         /* Set the transmit counter to 0.*/
            COMM.state = COMM_STATE_IDLE;                                               /* Move on to wait for a host communication.*/
        }
        break;
     
        case COMM_STATE_VALIDATE:                                                       /* Comes here when we receive a byte from the UART.*/
        {            
            if( COMM.processing == false )                                              /* If no command is currently being processed, */
            {
                ValidateComm();                                                         /* see if we received a valid command.*/
            }
            if( COMM.processing == true )                                               /* If we received a valid command,*/
            {
                COMM.state = COMM_STATE_WAIT;                                           /* Move on to wait for command to be executed.*/
                CMD.process_complete_flag = false;                                      /* Flag to show a command needs to be executed.*/               
            }                                                                           /* This starts the Command_Tasks machine.*/
            else
            {
                COMM.state = COMM_STATE_IDLE;                                           /* Move on to wait for a host communication.*/
            }
        }
        break;
        
        case COMM_STATE_WAIT:                                                           /* Wait here for the command to be processed.*/
        {
            if(CMD.process_complete_flag == true)                                       /* If we have finished processing the command,*/
            {                                                                           /*(Set true in commands.c)*/
                COMM.state = COMM_STATE_IDLE;                                           /* Move on wait for the next transmission from the host.*/
                COMM.processing = false;                                                /* Reset flag to show we are not processing a command.*/
//                if(UART.usage ==  true)                                                 /* If we have communicated to the host via the UART,*/
//                {
//                    UART.state = UART_STATE_WRITE;                                      /* Write the command response to the UART.*/
//                }
//                else                                                                    /* Otherwise,*/
//                {
////                    USB.state = USB_STATE_WRITE;                                        /* write the command response to the USB.*/
//                }               
            }
        }
        break;  
        
        case COMM_STATE_IDLE:                                                           /*Wait here until we have received data.*/
        {
            
        }
        break;
        
        default:
        {
            /* If not enough characters to process a message, then leave.*/            
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
    static void ValidateComm( void )

  Summary: This function checks if a valid command byte was received.

  Remarks:
    Refer to the commmodule.h interface header for function usage details.
 **************************************************************************************/

static void ValidateComm( void )
{
	uchar8_t temp;                                                                      /*!< Temporary placeholder for first byte of a command message.*/

	temp = Fifo_Get( &RX_FIFO );                                                        /* Get the first byte and check to see if it is a valid data word.*/

	if( Valid_Command( temp ) == false )                                                /* If the command is not valid, set the status byte and clear the RxFifo.*/
	{
		Set_Status( 15 );                                                               /* Set the Status byte to show an invalid command was received.*/
		Prepare_Return_A( 0x5C, 0, 0 );                                                 /* Prepare the return with a Status query 0x5C message.*/        
        while(COMM.rx_count < CMD.cmd_size)                                             /* While the the receive byte counter is less than the command size,*/
        {
            ( void ) Fifo_Get( &RX_FIFO );                                              /* Clear the FIFO Out & start over.*/                         
            COMM.rx_count = COMM.rx_count + 1U;                                         /* Increment the counter.*/
        } 
	}
    else
    {
        Clear_Status( 15 );                                                             /* Clear the status byte, a valid command was received.*/													  
        CMD.command[ 0 ] = temp;                                                        /* Put the valid command byte into the first position of the Command[] array.*/ 
        COMM.rx_count = 1U;                                                             /* Set the receive byte counter to 1.*/
        while(COMM.rx_count < CMD.cmd_size)                                             /* While the the receive byte counter is less than the command size,*/
        {
            CMD.command[ COMM.rx_count ] = Fifo_Get( &RX_FIFO );                        /* transfer a byte from the RX_FIFO to the COMMAND array.*/                          
            COMM.rx_count = COMM.rx_count + 1U;                                         /* Increment the counter.*/
        }                
        COMM.processing = true;                                                         /* We have a message that needs processing.*/
    } 
}

/***************************************************************************************
 End of File
 */

