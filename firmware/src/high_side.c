/**************************************************************************************/
/** \file high_side.c
     
  Company:
    Hunting Titan
  
  File Name:
    side.c

  Summary:
    This file contains the state machine code for the HIGH_SIDE operation.

  Description:
    This file contains the state machine code for the HIGH_SIDE operation.  It 
    implements the logic of the HIGH_SIDE's state machine. These functions monitor the  
    HST communication when the front panel knob is in the HIGH SIDE position. A UART is 
    configured to receive the data. This machine reads data from the UART at 20 KBaud 
    and puts it to the RxFifo for later use.  The first 30 transmissions from the HSI
    tool are the 'Sign On' data that includes The Tool ID and firmware version. All
    transmissions afterwards are the tool data values.  The states are configured so 
    that other system tasks can be maintained while these tasks are waiting for an 
    event to occur. It may call API routines of other MPLAB Harmony modules in the 
    system, such as drivers, system services, and middleware.  
*/
/**************************************************************************************/

/**************************************************************************************/
/**************************************************************************************/
/* Section: Included Files                                                            */
/**************************************************************************************/
/**************************************************************************************/

#include "high_side.h"
#include "adc.h"
#include "switches.h"
#include "gpt.h"
#include "fifo.h"
#include "commmodule.h"
#include "commands.h"
#include "report.h"
#include "statusst.h"

#include <stdbool.h>
#include <xc.h>
#include <math.h>


/**************************************************************************************/
/**************************************************************************************/
/* Section: Structure Data                                                            */
/**************************************************************************************/
/**************************************************************************************/

/**************************************************************************************/
/* HIGH_SIDE Data

  Summary:
    These structures hold the required states and variables to perform the HIGH_SIDE 
    tasks.
 
  Description:
    These structures hold the required states and variables to perform the HIGH_SIDE  
    tasks. These are here to link these structures for use by the local functions.
 
  Remarks: 
    These are defined in high_side.h
*/

HIGH_SIDE_DATA HIGH_SIDE;

/**************************************************************************************/
/**************************************************************************************/
/* Section: State Machine Functions                                                   */
/**************************************************************************************/
/**************************************************************************************/

/*************************************************************************************** 
  Function:
    void HIGH_SIDE_Tasks ( void )

  Summary:
    This routine is the HIGH_SIDE_Tasks function.  It defines the (HIGH_SIDE) state  
    machine and core logic. This task monitors the wire-line voltage and current when 
    the panel knob is in the HIGH SIDE position.

  Remarks:
    Refer to the high_side.h interface header for function usage details.
 */

void HIGH_SIDE_Tasks ( void )
{ 
    switch(HIGH_SIDE.state)
    {
        case HIGH_SIDE_STATE_INIT:
        {  
            if(SWITCH.command_setting == 0U)                                            /* If we received a command to read the High Side data,*/
            {
                HIGH_SIDE.write_complete = false;                                       /* Set this flag to show we have not completed a write to the host.*/
                HIGH_SIDE.usage = false;                                                /* Flag to show we are not communicating through the UART.*/
                HIGH_SIDE.handleUSART1 = DRV_HANDLE_INVALID;                            /* Set the UART handle to invalid.*/
                HIGH_SIDE.state = HIGH_SIDE_STATE_OPEN;                                 /* Move on to open the UART port.*/
                HIGH_SIDE.bytes_received = 0U;   
                HIGH_SIDE.checksum = 0U;
                HIGH_SIDE.byte_count = 0U;
                HIGH_SIDE.timeout_count = 0U;
            }
            else
            {
                Clear_Status( 6 );                                                      /* Clear the status bit to show we received good data.*/
            }
        }
        break;
       
        case HIGH_SIDE_STATE_OPEN:
        {
            if (HIGH_SIDE.handleUSART1 == DRV_HANDLE_INVALID)                           /* Open the UART. This port is used for debugging only.*/
            {
                /*LDRA_INSPECTED 123 S*/
                /*LDRA_INSPECTED 120 S*/                                                /* MPLAB Harmony created function.*/
                HIGH_SIDE.handleUSART1 = DRV_USART_Open(1, 
                    DRV_IO_INTENT_READWRITE|DRV_IO_INTENT_NONBLOCKING);
            }
            if(HIGH_SIDE.handleUSART1 != DRV_HANDLE_INVALID)                            /* Once the UART port is open,*/
            {
                HIGH_SIDE.state = HIGH_SIDE_STATE_READ;                                 /* move on to check for data received via the UART port.*/
            }
        }
        break;
        
        case HIGH_SIDE_STATE_READ:
        {
            if(SWITCH.command_setting == 0U)                                            /* If we received a command to read the High Side data,*/
            {
                ReadHSUART();                                                           /* Check for and read a byte from the HST.*/
                if((HIGH_SIDE.bytes_received == HIGH_SIDE.data[2U]) &&                  /* If the bytes received are the 'Sign On' data,*/
                        (HIGH_SIDE.data[1U] == 2U))   
                {
                    Nop();
                    DRV_USART_Close(HIGH_SIDE.handleUSART1); 
                    HIGH_SIDE.state = HIGH_SIDE_STATE_CHECKSUM;
                    HIGH_SIDE.timeout_count = 0U;
                }
                else if ((HIGH_SIDE.bytes_received == HIGH_SIDE.data[2U]) &&            /* Otherwise if the bytes received are 'Tool Data',*/
                        (HIGH_SIDE.data[1U] == 3U))   
                {
                    Nop();
                    DRV_USART_Close(HIGH_SIDE.handleUSART1); 
                    HIGH_SIDE.state = HIGH_SIDE_STATE_CHECKSUM;
                    HIGH_SIDE.timeout_count = 0U;
                }
                else
                {
                    /**/
                }
                if((HIGH_SIDE.bytes_received == 0U) && (HIGH_SIDE.tick == true))        /* If data is not being received,*/
                {               
                    HIGH_SIDE.tick = false;                                             /* Reset the timer tick.*/
                    HIGH_SIDE.timeout_count = HIGH_SIDE.timeout_count + 1U;             /* Increment the timer count.*/
                    if(HIGH_SIDE.timeout_count == 21U)                                  /* If 210mS have gone by,*/
                    {
                        Set_Status( 6 );                                                /* Set the status bit to show the data is bad.*/
                        HIGH_SIDE.timeout_count = 0U;                                   /* Reset the time out count.*/
                        for(HIGH_SIDE.byte_count = 0U; HIGH_SIDE.byte_count < 35; 
                            HIGH_SIDE.byte_count ++)
                        {
                            REPORT.data[HIGH_SIDE.byte_count + 11U] = 0U;               /* Clear the report data.*/                       
                        }
                    }
                }
            }
            else
            {
                HIGH_SIDE.state = HIGH_SIDE_STATE_INIT;                                 /* move on to check for data received via the UART port.*/
            }
        }
        break;
        
        case HIGH_SIDE_STATE_WAIT:                                                      /* Wait here to process a command before sending response.*/
        {                                                                               /* State will move to WRITE from commmodule.c.*/
            
        }
        break;
        
        case HIGH_SIDE_STATE_CHECKSUM:
        {
            for(HIGH_SIDE.byte_count=0;                                                 /* Calculate the checksum as a modulo 256.*/
                    HIGH_SIDE.byte_count < HIGH_SIDE.bytes_received - 1U; 
                    HIGH_SIDE.byte_count++)
            {                                                                           /* Add all of the data values except the checksum*/
                HIGH_SIDE.checksum = HIGH_SIDE.checksum +                               /* and use the LSB for comparison.*/
                        HIGH_SIDE.data[HIGH_SIDE.byte_count];
            }
            if(HIGH_SIDE.checksum == HIGH_SIDE.data[HIGH_SIDE.bytes_received - 1U])     /* If the checksum is valid,*/
            {
                Clear_Status( 6 );                                                      /* Clear the status bit to show we received good data.*/
                for(HIGH_SIDE.byte_count = 0U; 
                        HIGH_SIDE.byte_count < HIGH_SIDE.bytes_received; 
                        HIGH_SIDE.byte_count ++)
                {
                    REPORT.data[HIGH_SIDE.byte_count + 11U] =                           /* Save the data to the report array for transmission.*/
                                            HIGH_SIDE.data[HIGH_SIDE.byte_count];
                }
                (void) memset( HIGH_SIDE.data, 0, HIGH_SIDE.bytes_received);            /* Clear the data array.*/
                HIGH_SIDE.good_data_flag = true;                                        /* Set the flag and*/                  
                HIGH_SIDE.bytes_received = 0U;                                          /* reset the number of bytes received.*/                
            }
            else                                                                        /* Otherwise, good data was not received.*/
            {
                HIGH_SIDE.good_data_flag = false;                                       /* Reset the flag.*/  
                Set_Status( 6 );                                                        /* Set the status bit to show we did not receive good data.*/
                (void) memset( HIGH_SIDE.data, 0, 53U);                                 /* Clear the data array.*/
                for(HIGH_SIDE.byte_count = 0U; 
                        HIGH_SIDE.byte_count < HIGH_SIDE.bytes_received; 
                        HIGH_SIDE.byte_count ++)
                {                   
                   REPORT.data[HIGH_SIDE.byte_count + 11U] = 0U;                        /* Clear the report data.*/
                }
                HIGH_SIDE.bytes_received = 0U;
            }
            HIGH_SIDE.state = HIGH_SIDE_STATE_INIT;                                     /* move on to check for data received via the UART port.*/
        }
        break;
        
        case HIGH_SIDE_STATE_WRITE:                                                     /* Send the command response to the host.*/
        {
            WriteHSUART();                                                              /* Send the command response.*/
            if(HIGH_SIDE.write_complete == true)                                        /* If we have completed sending the response,*/
            {
                HIGH_SIDE.write_complete = false;                                       /* reset the flag.*/
                HIGH_SIDE.state = HIGH_SIDE_STATE_READ;                                 /* Move to look for the next data from the host.*/
                HIGH_SIDE.usage = false;                                                /* Flag to show we are not communicating through the UART.*/
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
/* Section: Local Functions                                                           */
/**************************************************************************************/
/**************************************************************************************/

/*!************************************************************************************* 
  Function:
    static void ReadHSUART(void)

  Summary:
    This function reads a byte of data from the UART and transfers it to the RxFifo.

  Remarks:
    Refer to the UART.h interface header for function usage details.
 */

static void ReadHSUART(void)
{
    static i = 0U;
    static uint8_t uart_bytes=0U;                                                       /*!< Temporary placeholder for byte data from the host.*/   
    
    /*LDRA_INSPECTED 433 S*/                                                            /* MPLAB Harmony function returns a boolean result.*/
    if(DRV_USART_ReceiverBufferIsEmpty(HIGH_SIDE.handleUSART1) == false)                /* If the UART receive buffer has data in it,*/
    { 
        /*LDRA_INSPECTED 434 S*/                                                        /*MPLAB Harmony function.*/
        
        uart_bytes = DRV_USART_ReadByte(HIGH_SIDE.handleUSART1);                        /* Read a received byte and */        
        if((HIGH_SIDE.bytes_received == 0U) && (uart_bytes == 0xAC))                    /* If the first byte received is the sync byte,*/
        {
            HIGH_SIDE.data[HIGH_SIDE.bytes_received] = uart_bytes;                      /* Put the byte into the data array.*/
            HIGH_SIDE.usage =  true;                                                    /* Shows that we received data via the UART and not the USB.*/
            HIGH_SIDE.bytes_received = HIGH_SIDE.bytes_received + 1U;                   /* Increment counter for number of bytes received via the UART.*/
        }
        else if((HIGH_SIDE.bytes_received > 0U))                                        /* If we have already received the sync byte,*/
        {
            HIGH_SIDE.data[HIGH_SIDE.bytes_received] = uart_bytes;                      /* Put the byte into the data array.*/
            HIGH_SIDE.usage =  true;                                                    /* Shows that we received data via the UART and not the USB.*/
            HIGH_SIDE.bytes_received = HIGH_SIDE.bytes_received + 1U;                   /* Increment counter for number of bytes received via the UART.*/
        }
        if(HIGH_SIDE.bytes_received >= 15U)
        {
            (void) memset( HIGH_SIDE.data, 0, HIGH_SIDE.bytes_received);                /* Clear the data array.*/
            (void) memset( REPORT.data + 11U, 0, 64);                                   /* Clear the data array.*/
            HIGH_SIDE.bytes_received = 0U;
            
            Nop();
        }
    }
}

/*************************************************************************************** 
  Function:
    static void WriteHSUART(void)

  Summary:
    This function gets a byte of data from the TxFifo and writes it to the UART.

  Remarks:
    Refer to the UART.h interface header for function usage details.
 */

static void WriteHSUART( void )
{
//    if( COMM.tx_count < CMD.cmd_size )                                                  /* If we have not transmitted enough bytes*/
//    {
//        if(PLIB_USART_TransmitterIsEmpty(USART_ID_1)==1)                                /* and if the transmitter buffer is empty,*/
//        {
//            /*LDRA_INSPECTED 434 S*/                                                    /*MPLAB Harmony function.*/
//            PLIB_USART_TransmitterByteSend(USART_ID_1,Fifo_Get( &TX_FIFO ));            /* Send character.*/
//            COMM.tx_count++;                                                            /* Increment counter.*/
//        }
//    }    
//    else if( COMM.tx_count == CMD.cmd_size )                                            /* If we have tranmitted enough bytes,*/
//    {
//        COMM.tx_count = 0U;                                                             /* reset the counter.*/
//        UART.write_complete = true;                                                     /* Set flag to show we have completed writing the response.*/
//    }
//    else
//    {
//        /*Comment.*/
//    }
}

/***************************************************************************************
 End of File
 */
