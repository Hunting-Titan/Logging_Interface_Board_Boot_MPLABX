/**************************************************************************************/
/** \file high_side.h

  Company:
    Hunting Titan

  File Name:
    high_side.h

  Summary:
    This header file provides prototypes and definitions for high_side.c.

  Description:
    This header file provides function prototypes and data type definitions for
    high_side.  Some of these are required by the system (such as the system_interrupt) 
    and some of them are only used internally by the application 
    (such as the "HIGH_SIDE_STATES" definition). 
 */
/**************************************************************************************/

#ifndef HIGH_SIDE_H                                                                     /* Guard against multiple inclusion.*/
#define HIGH_SIDE_H
                                                                                       
#ifdef __cplusplus                                                                      /* Provide C++ Compatibility */
extern "C"
{
#endif

/**************************************************************************************/
/**************************************************************************************/
/* Section: Included Files                                                            */
/**************************************************************************************/
/**************************************************************************************/

#include "wl_sps.h"
#include"../system_config.h"
#include"../system_definitions.h"
    
#include <stdbool.h>    
    
/**************************************************************************************/
/**************************************************************************************/
/* Section: Defines                                                                   */
/**************************************************************************************/
/**************************************************************************************/

    
typedef float float32_t;
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
	HS_UART_STATE_INIT=0,                                                                  /*!< UART's state machine's initial state.*/            
    HS_UART_STATE_OPEN,                                                                    /*!< Open the UART channel.*/
    HS_UART_STATE_READ,                                                                    /*!< Read the UART data and transfer to a RxFifo.*/            
    HS_UART_STATE_WAIT,                                                                    /*!< Wait for the command to be processed.*/            
    HS_UART_STATE_WRITE,                                                                   /*!< Transfer the response data from the TxFifo to the UART.*/    
 
} HS_UART_STATES;

/**************************************************************************************/
/* HIGH_SIDE_STATES 

  Summary:
    HIGH_SIDE_STATES enumeration

  Description:
    This enumeration defines the valid HIGH_SIDE states.  These states
    determine the behavior of the HIGH_SIDE state machine at various times.
*/        
 
typedef enum                                                                            /*!< Enumerate the valid states for the HIGH_SIDE_STATE machine.*/
{
	HIGH_SIDE_STATE_INIT=0,                                                             /*!< HIGH_SIDE state machine's initial state.*/             
    HIGH_SIDE_STATE_OPEN,                                                               /*!< Open the UART channel.*/
    HIGH_SIDE_STATE_READ,                                                               /*!< Read the UART data and transfer to a RxFifo.*/            
    HIGH_SIDE_STATE_WAIT,                                                               /*!< Wait for the command to be processed.*/ 
    HIGH_SIDE_STATE_CHECKSUM,        
    HIGH_SIDE_STATE_WRITE,                                                              /*!< Transfer the response data from the TxFifo to the UART.*/            
            
} HIGH_SIDE_STATES;

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

    HS_UART_STATES state;                                                               /*!< The COMM_STATES current state.*/
    DRV_HANDLE handleUSART1;                                                            /*!< The UART handle.*/
    bool write_complete;                                                                /*!< Flag to indicate that the UART has completed writing a response.*/
    bool usage;                                                                         /*!< Flag to show if we are communicating through the UART.  Used to choose
                                                                                          or USB to respond to a command.*/
    uint8_t bytes_received;                                                             /*!< Counter for number of bytes received via the UART.*/
    
    
} HS_UART_DATA;

extern HS_UART_DATA HS_UART;

/**************************************************************************************/
/* HIGH_SIDE_DATA

  Summary:
    Holds HIGH_SIDES_DATA used for the HIGH_SIDE tasks.

  Description:
    Holds HIGH_SIDE_DATA used for the HIGH_SIDE tasks. The state machine and variables
    used to control HIGH_SIDE functions are stored here.

  Remarks:
    None
 */

typedef struct
{    
    HIGH_SIDE_STATES state;                                                             /*!< The application's current state */

    bool tick;                                                                          /*!< Timer tick used to decide when to retrieve a voltage reading. (1mS)*/
    HS_UART_STATES HSUstate;                                                            /*!< The HIGH SIDE UART COMM_STATES current state.*/
    DRV_HANDLE handleUSART1;                                                            /*!< The UART handle.*/
    bool write_complete;                                                                /*!< Flag to indicate that the UART has completed writing a response.*/
    bool usage;                                                                         /*!< Flag to show if we are communicating through the UART.  Used to choose
                                                                                          or USB to respond to a command.*/
    uint8_t bytes_received;                                                             /*!< Counter for number of bytes received via the UART.*/
    uint16_t cmd_size;
    uint8_t data[15];                                                                   /*!< Array to hold contents from HSI tool.*/
    uint8_t byte_count;                                                                 /*!< Counter for the number of bytes received in a transmission.*/
    uint8_t checksum;                                                                   /*!< The checksum result to validate a good transmission.*/
    bool good_data_flag;                                                                /*!< Flag to indicate good data has been received.*/
    uint8_t data_clear;                                                                 /*!< Placeholder to clear FIFO data isf it is bad.*/
    uint8_t timeout_count;                                                              /*!< Count to track if data is not received from high side tool.*/

} HIGH_SIDE_DATA;

extern HIGH_SIDE_DATA HIGH_SIDE;

/**************************************************************************************/
/**************************************************************************************/
/*       State Machine Functions                                                      */
/**************************************************************************************/
/**************************************************************************************/

/*!*************************************************************************************
  Function:
 * 
    void HIGH_SIDE_Tasks(void)

  Summary:
    HIGH_SIDE_Tasks function

  Description:
    This routine is the HIGH_SIDE_Tasks function.  It defines the HIGH_SIDE_Tasks state 
    machine and core logic. This machine is used to monitor the wire-line when the 
    High Side tool is selected.  It will receive communications from the tool and send 
    them to the host.     

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
   HIGH_SIDE_Tasks()   
 */

void HIGH_SIDE_Tasks ( void );

/**************************************************************************************/
/**************************************************************************************/
/* Section: Local Functions                                                           */
/**************************************************************************************/
/**************************************************************************************/

/*!************************************************************************************* 
  Function:
    static void ReadHSUART(void) 

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
    ReadHSUART()   
 */
static void ReadHSUART(void);

/*!************************************************************************************* 
  Function:
    static void WriteHSUART(void) 

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
static void WriteHSUART(void);
    
#ifdef __cplusplus                                                                      /* Provide C++ Compatibility */
}
#endif

#endif                                                                                  /* HIGH_SIDE_H */

/***************************************************************************************
 End of File
 */
