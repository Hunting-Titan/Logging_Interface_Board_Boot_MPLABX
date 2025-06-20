/**************************************************************************************/
/** \file timers.h

  Company:
    Hunting Titan

  File Name:
    timers.h

  Summary:
    This header file provides prototypes and definitions for timers.c.

  Description:
    This header file provides function prototypes and data type definitions for
    timers.c.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "TIMER_Tasks" definition).  Both
    are defined here for convenience.
 */
/**************************************************************************************/

#ifndef TIMERS_H                                                                        /* Guard against multiple inclusion.*/
#define TIMERS_H

#ifdef __cplusplus                                                                      /* Provide C++ Compatibility */
extern "C"
{
#endif

/**************************************************************************************/
/**************************************************************************************/
/* Section: Included Files                                                            */
/**************************************************************************************/
/**************************************************************************************/

#include <stdint.h>
#include <stdbool.h>                                                                    /* Defines true.*/
#include"../system_config.h"
#include"../system_definitions.h"

/**************************************************************************************/
/**************************************************************************************/
/* Section: Data Types                                                                */
/**************************************************************************************/
/**************************************************************************************/

/**************************************************************************************/
/* TIMER states

  Summary:
    TIMER states enumeration

  Description:
    This enumeration defines the valid TIMER states.  These states
    determine the behavior of the TIMER state machine at various times.
*/    

typedef enum
{	
	TIMER_STATE_INIT=0,                                                                 /*!< TIMER state machine's initial state. */            
    TIMER_STATE_TIMER_START,                                                            /*!< Open the timer and set count flags and values.*/            
	TIMER_STATE_SERVICE_TASKS                                                           /*!< State where the main timer tasks occur.*/
           
} TIMER_STATES; 

/**************************************************************************************/
/* TIMER_DATA

  Summary:
    Holds TIMER_DATA used for the TIMER tasks.

  Description:
    Holds TIMER_DATA used for the TIMER tasks. The state machine and variables
    used to control TIMER functions are stored here.

  Remarks:
    None
 */
    
typedef struct                                                                          /* This structure collects the variables and states required for these*/ 
{                                                                                       /* functions to operate.*/ 
    
    TIMER_STATES state;                                                                 /*!< The application's current state.*/ 
    
    DRV_HANDLE  tmrDrvHandle;                                                           /* Pointer to Timer Driver returned by DRV_TMR_Open().*/
    
    bool        timer1_100uS_tick;                                                      /*!< Flag to show timer1 100uS Timer Tick has completed.*/
    bool        timer1_1mS_tick;                                                        /*!< Flag to show timer1 1mS Timer Tick has completed.*/
    bool        timer1_10mS_tick;                                                       /*!< Flag to show timer1 10mS Timer Tick has completed.*/
    bool        timer1_100mS_tick;                                                      /*!< Flag to show timer1 100mS Timer Tick has completed.*/
    bool        timer1_1000mS_tick;                                                     /*!< Flag to show timer1 1000mS Timer Tick has completed.*/
    
    uint8_t     timer1_100uS_count;                                                     /*!< Counter to track 0 to 900uS in 100uS increments.*/
    uint8_t     timer1_1mS_count;                                                       /*!< Counter to track 0 to 9 mS in 1mS increments.*/
    uint8_t     timer1_10mS_count;                                                      /*!< Counter to track 10 to 90mS in 10mS increments.*/
    uint8_t     timer1_100mS_count;                                                     /*!< Counter to track 100 to 900mS in 100mS increments.*/
    uint8_t     timer1_1000mS_count;                                                    /*!< Counter to track 1000 to 9000 mS in 1000mS increments.*/ 
    uint32_t    count;
    
} TIMER_DATA;

extern TIMER_DATA TIMER;

/**************************************************************************************/
/**************************************************************************************/
/*       State Machine Functions                                                      */
/**************************************************************************************/
/**************************************************************************************/

/*!*************************************************************************************
  Function:
    void TIMER_Tasks(void)

  Summary:
    TIMER_Tasks function.

  Description:
    This routine is the TIMER_Tasks function.  It defines the TIMER state machine and 
    core logic.

  Precondition:
    The system ("SYS_Initialize") and application ("APP_Initialize")initialization 
    should be called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Example:    
    TIMER_Tasks() 

  Remarks:
    This routine must be called from APP_Tasks() routine.
 */

void TIMER_Tasks(void);
 
#ifdef __cplusplus                                                                      /* Provide C++ Compatibility.*/
}
#endif

#endif                                                                                  /* TIMERS_H */

/***************************************************************************************
 End of File
 */
