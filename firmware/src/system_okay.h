/* ************************************************************************** */
/** Descriptive File Name

  Company:
 Hunting Titan

  File Name:
    system_okay.h

  Summary:
    This function performs system checks using Microchip Class B safety code to verify
    proper operation of the controller before the system is initialized.

  Description:
    This function performs system checks using Microchip Class B safety code to verify
    proper operation of the controller before the system is initialized.
 */
/**************************************************************************************/

#ifndef SYSTEM_OKAY_H                                                                   /* Guard against multiple inclusion */
#define SYSTEM_OKAY_H

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
#include <stdbool.h>

/**************************************************************************************/ 
/**************************************************************************************/ 
/* Section: Structure Data and Local Variables                                        */ 
/**************************************************************************************/ 
/**************************************************************************************/ 
/* SYSTEM_OKAY Data

  Summary:
    These structures hold required data.

  Description:
    This enumeration defines the valid SYSTEM_OKAY states.  These states
    determine the behavior of the SYSTEM_OKAY state machine at various times.
         
*/

typedef enum                                                                            /*!< Enumerate the valid states for the SYSTEM_OKAY_STATES machine.*/
{
	SYSTEM_OKAY_STATE_INIT=0,                                                           /*!< SYSTEM_OKAY state machine's initial state.*/            
    SYSTEM_OKAY_STATE_START,                                                            /*!< This state checks a flag to indicate when the SYSTEM_OKAY tick has completed a cycle.*/          
    SYSTEM_OKAY_STATE_TEST,                                                             /*!< Finalize the system status and set the LED accordingly.*/ 
    SYSTEM_OKAY_STATE_IDLE,                                                             /*!< Come here when other tasks are complete.*/
  
} SYSTEM_OKAY_STATES;

/**************************************************************************************/

typedef struct                                                                          /* This structure collects the variables and states required for these*/                                                                        
{                                                                                       /* functions to operate.*/
    
    SYSTEM_OKAY_STATES state;                                                           /*!< The SYSTEM_OKAY tasks current state.*/
    bool pass;
} SYSTEM_OKAY_DATA;

extern SYSTEM_OKAY_DATA SYSTEM_OKAY;

/**************************************************************************************/ 
/**************************************************************************************/ 
/* Section: State Machine Functions                                                   */ 
/**************************************************************************************/ 
/**************************************************************************************/

/*!*************************************************************************************
  Function:
    void SYSTEM_OKAY_Tasks(void)

  Summary:
    SYSTEM_OKAY tasks function

  Description:
    This routine is the SYSTEM_OKAY tasks function.  It defines the SYSTEM_OKAY's 
    state machine and core logic. This code should execute only if the fuse does not 
    blow when the SYSTEM_OKAY timer expires.  This code will turn off all power  
    supplies so the tool can be safely retrieved.

  Precondition:
    The system ("SYS_Initialize") and application ("APP_Initialize")initialization 
    should be called before calling this.

  Parameters:
    None.

  Returns:
    None.
  
  Remarks:
    This routine must be called from APP_Tasks() routine.

  Example:
    SYSTEM_OKAY_Tasks()
 */

void SYSTEM_OKAY_Tasks(void);

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_OKAY_H */

/***************************************************************************************
 End of File
 */
