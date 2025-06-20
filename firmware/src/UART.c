/**************************************************************************************/
/** \file UART.c
     
  Company:
    Hunting Titan
  
  File Name:
    UART.c

  Summary:
    This file contains the state machine code for the UART operation.

  Description:
    This file contains the state machine code for the UART operation.  It implements
    the logic of the UART's state machine and it may call API routines of other
    MPLAB Harmony modules in the system, such as drivers, system services, and
    middleware. This machine reads data from the UART and puts it to the RxFifo
    for later use.  It also gets data from the TxFifo and writes it to the UART.
    The states are configured so that other system tasks can be maintained while 
    these tasks are waiting for an event to occur.     

***************************************************************************************/

/**************************************************************************************/
/**************************************************************************************/
/* Section: Included Files                                                            */
/**************************************************************************************/
/**************************************************************************************/


#include "UART.h"
#include "fifo.h"
#include "commmodule.h"
#include "commands.h"

/**************************************************************************************/
/* UART Data

  Summary:
    These structures hold the required states and variables to perform the UART tasks.

  Description:
    These structures hold the required states and variables to perform the UART tasks. 
    These are here to link these structures for use by the local functions.
 
  Remarks: 
    These are defined in UART.h
*/

UART_DATA UART;

static UART_STATES U_STATES;

/**************************************************************************************/
/**************************************************************************************/
/* Section: State Machine Functions                                                   */
/**************************************************************************************/
/**************************************************************************************/

/*************************************************************************************** 
  Function:
    void UART_Tasks ( void )

  Summary:
   This routine is the UART_Tasks function.  It defines the (UART) state machine and
   core logic.

  Remarks:
    Refer to the UART.h interface header for function usage details.
 */

void UART_Tasks(void)
{
    switch ( UART.state )                                                               /* Check the machines current state.*/                                                                        
    {
        case UART_STATE_INIT:
        {
            UART.write_complete = false;                                                /* Set this flag to show we have not completed a write to the host.*/
            UART.usage = false;                                                         /* Flag to show we are not communicating through the UART.*/
//            UART.handleUSART0 = DRV_HANDLE_INVALID;                                     /* Set the UART handle to invalid.*/
            UART.state = UART_STATE_OPEN;                                               /* Move on to open the UART port.*/
            UART.bytes_received = 0U;
        }
        break;
        
        case UART_STATE_OPEN:
        {
//            if (UART.handleUSART0 == DRV_HANDLE_INVALID)                                /* Open the UART. This port is used for debugging only.*/
//            {
//                /*LDRA_INSPECTED 123 S*/
//                /*LDRA_INSPECTED 120 S*/                                                /* MPLAB Harmony created function.*/
//                UART.handleUSART0 = DRV_USART_Open(0, 
//                    DRV_IO_INTENT_READWRITE|DRV_IO_INTENT_NONBLOCKING);
//            }
//            if(UART.handleUSART0 != DRV_HANDLE_INVALID)                                 /* Once the UART port is open,*/
//            {
//                UART.state = UART_STATE_READ;                                           /* move on to check for data received via the UART port.*/
//            }
        }
        break;
        
        case UART_STATE_READ:                                                           /* Stay here until data is received.*/
        {
/*            ReadUART()*/                                                                 /* Check for and read a byte from the host.*/
            if( UART.bytes_received  == CMD.cmd_size )                                  /* If we have received enough bytes for a command,*/
            {
                UART.bytes_received = 0U;                                               /* Reset the counter.*/
                UART.state = UART_STATE_WAIT;                                           /* move on to wait for the command to be processed.*/
                COMM.state = COMM_STATE_VALIDATE;                                       /* Check to see if we have received a valid command.*/
            }
        }
        break;
        
        case UART_STATE_WAIT:                                                           /* Wait here to process a command before sending response.*/
        {                                                                               /* State will move to WRITE from commmodule.c.*/
            
        }
        break;   
     
        case UART_STATE_WRITE:                                                          /* Send the command response to the host.*/
        {
            WriteUART();                                                                /* Send the command response.*/
            if(UART.write_complete == true)                                             /* If we have completed sending the response,*/
            {
                UART.write_complete = false;                                            /* reset the flag.*/
                UART.state = UART_STATE_READ;                                           /* Move to look for the next data from the host.*/
                UART.usage = false;                                                     /* Flag to show we are not communicating through the UART.*/
            }            
        }
        break;
        
        default:
        {
            /* Comment.*/            
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
    static void ReadUART(void)

  Summary:
    This function reads a byte of data from the UART and transfers it to the RxFifo.

  Remarks:
    Refer to the UART.h interface header for function usage details.
 */

static void ReadUART(void)
{
    static uint8_t uart_bytes=0U;                                                       /*!< Temporary placeholder for byte data from the host.*/   
    
    /*LDRA_INSPECTED 433 S*/                                                            /* MPLAB Harmony function returns a boolean result.*/
    if(DRV_USART_ReceiverBufferIsEmpty(COMM.handleUSART0) == false)                     /* If the UART receive buffer has data in it,*/
    { 
        /*LDRA_INSPECTED 434 S*/                                                    /*MPLAB Harmony function.*/
        uart_bytes = DRV_USART_ReadByte(COMM.handleUSART0);                              /* Read a received byte and */
        (void)Fifo_Put( &RX_FIFO, uart_bytes );                                         /* put the byte into the RxFifo.*/
        UART.usage =  true;                                                             /* Shows that we received data via the UART and not the USB.*/
        UART.bytes_received++;                                                          /* Increment counter for number of bytes received via the UART.*/
    }
    else
    {
        /*Comment.*/
    }
}

/*************************************************************************************** 
  Function:
    static void WriteUART(void)

  Summary:
    This function gets a byte of data from the TxFifo and writes it to the UART.

  Remarks:
    Refer to the UART.h interface header for function usage details.
 */

static void WriteUART( void )
{
    if( COMM.tx_count < CMD.cmd_size )                                                  /* If we have not transmitted enough bytes*/
    {
        if(PLIB_USART_TransmitterIsEmpty(USART_ID_1)==1)                                /* and if the transmitter buffer is empty,*/
        {
            /*LDRA_INSPECTED 434 S*/                                                    /*MPLAB Harmony function.*/
            PLIB_USART_TransmitterByteSend(USART_ID_1,Fifo_Get( &TX_FIFO ));            /* Send character.*/
            COMM.tx_count++;                                                            /* Increment counter.*/
        }
    }    
    else if( COMM.tx_count == CMD.cmd_size )                                            /* If we have tranmitted enough bytes,*/
    {
        COMM.tx_count = 0U;                                                             /* reset the counter.*/
        UART.write_complete = true;                                                     /* Set flag to show we have completed writing the response.*/
    }
    else
    {
        /*Comment.*/
    }
}

/***************************************************************************************
 End of File
 */
