/**************************************************************************************/
/** \file commmodule.h

  Company:
    Hunting Titan

  File Name:
    commmodule.h

  Summary:
    This header file provides prototypes and definitions for commmodule.c. These 
    functions are used to monitor and respond to commands from a host via a USB 
    or UART connection. 

  Description:
    This header file provides function prototypes and data type definitions for
    commmodule.c.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "COMM_STATES" definition).  
 */
/**************************************************************************************/

#ifndef COMMMODULE_H                                                                    /* Guard against multiple inclusion.*/
#define COMMMODULE_H
                
#ifdef __cplusplus                                                                      /* Provide C++ Compatibility */
extern "C" {
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
/* COMM states

  Summary:
    COMM states enumeration

  Description:
    This enumeration defines the valid COMM states.  These states
    determine the behavior of the COMM state machine at various times.
*/    

typedef enum                                                                            /*!< Enumerate the valid states for the COMM_STATE machine.*/
{
	COMM_STATE_INIT=0,                                                                  /*!< Application's state machine's initial state.*/           
    COMM_STATE_VALIDATE,                                                                /*!< Ensure the command received is valid.*/ 
    COMM_STATE_WAIT,                                                                    /*!< Process the data from the communication.*/
    COMM_STATE_IDLE                                                                     /*!< Only comes here after the communication has been completed.*/      
 
} COMM_STATES;

/**************************************************************************************/
/* COMM Data

  Summary:
    Holds COMM data used for the COMM tasks.

  Description:
    Holds COMM data used for the COMM tasks. The state machine and variables used 
    to control COMM message are stored here.

  Remarks:
    None
 */

typedef struct                                                                          /* This structure collects the variables and states required for these*/ 
{                                                                                       /* functions to operate.*/

    COMM_STATES state;                                                                  /*!< The COMM_STATES current state.*/

    DRV_HANDLE handleUSART0;                                                            /*!< The UART handle.*/
	uint8_t tx_count;                                                                   /*!< Counter for the Transmit Fifo.*/
	uint8_t rx_count;                                                                   /*!< Counter for the Receive Fifo.*/
    bool processing;                                                                    /*!< Flag to indicate that a message needs to be processed.*/

} COMM_DATA;

extern COMM_DATA COMM;

/**************************************************************************************/
/**************************************************************************************/
/* Section: Local Functions                                                           */
/**************************************************************************************/
/**************************************************************************************/

/*!************************************************************************************* 
  Function:
    static void ValidateComm(void) 

  Summary:
    This function reads the battery voltage, temperature and remaining capacity 
    based on the command given to the function

  Description:
   Description: This task handles reading messages from Receive Queue (RxQ Fifo) and
   processes them. It looks for a valid command & upon finding it puts the remainder 
   into the Command buffer for processing.
   
    
    
  Precondition:
    None.

  Parameters:
    None.

  Returns
    None.
 
  Remarks
    None.
   
   Example:
    void ValidateComm()   
 */
static void ValidateComm(void);

/**************************************************************************************/
/**************************************************************************************/
/*       State Machine Functions                                                      */
/**************************************************************************************/
/**************************************************************************************/

/*!*************************************************************************************
  Function:
    void COMM_Tasks(void)

  Summary:
    COMM tasks function

  Description:
    This routine is the COMM tasks function.  It defines the COMM's state machine and 
    core logic. This task controls the communications between a host UART or host USB.

  Precondition:
    The system ("SYS_Initialize") and application ("APP_Initialize")initialization 
    should be called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Example:
    COMM_Tasks()
  
  Remarks:
    This routine must be called from COMM_Tasks() routine.
 */
void COMM_Tasks(void);

#ifdef __cplusplus                                                                      /* Provide C++ Compatibility.*/
}
#endif

#endif                                                                                  /* COMMMODULE_H */

/***************************************************************************************
 End of File
 */
