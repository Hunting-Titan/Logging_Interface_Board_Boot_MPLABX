/**************************************************************************************/
/** \file UART.h

  Company:
    Hunting Titan

  File Name:
    UART.h

  Summary:
    This header file provides prototypes and definitions for UART.c.

  Description:
    This header file provides function prototypes and data type definitions for
    UART.c.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "UART_TASKS" definition).  
 */
/**************************************************************************************/

#ifndef UART_H                                                                          /* Guard against multiple inclusion */
#define UART_H

#ifdef __cplusplus                                                                      /* Provide C++ Compatibility */
extern "C"
{
#endif

/**************************************************************************************/
/**************************************************************************************/
/* Section: Included Files                                                            */
/**************************************************************************************/
/**************************************************************************************/

#include"../system_definitions.h"

/**************************************************************************************/
/**************************************************************************************/
/* Section: Data Types                                                                */
/**************************************************************************************/
/**************************************************************************************/    

/**************************************************************************************/
/* UART states

  Summary:
    UART states enumeration

  Description:
    This enumeration defines the valid UART states.  These states
    determine the behavior of the UART state machine at various times.
*/    

typedef enum                                                                            /*!< Enumerate the valid states for the UART_STATE machine.*/
{
	UART_STATE_INIT=0,                                                                  /*!< UART's state machine's initial state.*/            
    UART_STATE_OPEN,                                                                    /*!< Open the UART channel.*/
    UART_STATE_READ,                                                                    /*!< Read the UART data and transfer to a RxFifo.*/            
    UART_STATE_WAIT,                                                                    /*!< Wait for the command to be processed.*/            
    UART_STATE_WRITE,                                                                   /*!< Transfer the response data from the TxFifo to the UART.*/    
 
} UART_STATES;

/**************************************************************************************/
/* UART Data

  Summary:
    Holds UART data used for the UART tasks.

  Description:
    Holds UART data used for the UART tasks. The state machine and variables used 
    to control UART message are stored here.

  Remarks:
    None
 */

typedef struct                                                                          /* This structure collects the variables and states required for these*/ 
{                                                                                       /* functions to operate.*/

    UART_STATES state;                                                                  /*!< The COMM_STATES current state.*/
    DRV_HANDLE handleUSART0;                                                            /*!< The UART handle.*/
    bool write_complete;                                                                /*!< Flag to indicate that the UART has completed writing a response.*/
    bool usage;                                                                         /*!< Flag to show if we are communicating through the UART.  Used to choose
                                                                                          or USB to respond to a command.*/
    uint8_t bytes_received;                                                             /*!< Counter for number of bytes received via the UART.*/
    
} UART_DATA;

extern UART_DATA UART;


/**************************************************************************************/
/**************************************************************************************/
/* Section: Local Functions                                                           */
/**************************************************************************************/
/**************************************************************************************/

/*!************************************************************************************* 
  Function:
    static void ReadUART(void) 

  Summary:
    This function reads a byte from the UART when data is received from the host.

  Description:
    This function reads a byte from the UART when data is received from the host. It
    puts the received byte into the RxFifo for later use.
 
  Precondition:
    None.

  Parameters:
    None.

  Returns
    None.
 
  Remarks
    None.
   
   Example:
    ReadUART()   
 */
static void ReadUART(void);

/*!************************************************************************************* 
  Function:
    static void WriteUART(void) 

  Summary:
    This function transfers a byte to the host. 

  Description:
    This function transfers a byte to the host.  A byte is transferred from the 
    TxFifo to the UART for transmission to the host.  The baud rate is 115200,N-8-1.
    Once the required number of bytes are transferred, a flag is set to notify the 
    UART_Tasks machine to look for a another transmission from the host.
    
  Precondition:
    None.

  Parameters:
    None.

  Returns
    None.
 
  Remarks
    None.
   
   Example:
    WriteUART()   
 */
static void WriteUART(void);

/**************************************************************************************/
/**************************************************************************************/
/*       State Machine Functions                                                      */
/**************************************************************************************/
/**************************************************************************************/

/*!*************************************************************************************
  Function:
 * 
    void UART_Tasks(void)

  Summary:
    UART_Tasks function

  Description:
    This routine is the UART_Tasks function.  It defines the UART_Tasks state 
    machine and core logic. This machine is used to send and receive data from the 
    host.  

  Precondition:
    The system ("SYS_Initialize") and application ("APP_Initialize")initialization 
    should be called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Remarks:
    This routine must be called from the APP_Tasks() routine.

  Example:
    UART_Tasks()   
 */

void UART_Tasks(void);

    
#ifdef __cplusplus                                                                      /* Provide C++ Compatibility */
}
#endif

#endif /* UART_H */

/***************************************************************************************
 End of File
 */
