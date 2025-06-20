/**************************************************************************************/ 
/*LDRA_INSPECTED 110 S */
/** \file app.h

  Company:
    Hunting Titan

  File Name:
    app.h

  Summary:
    This header file provides prototypes and definitions for the shooting panel main 
    controller.

  Description:
    This header file provides function prototypes and data type definitions for
    the shooting panel main controller.  Some of these are required by the system 
    (such as the "APP_Initialize" and "APP_Tasks" prototypes) and some of them are 
    only used internally by the application (such as the "APP_STATES" definition).  
    Both are defined here for convenience.
 */ 
/**************************************************************************************/

#ifndef APP_H                                                                           /* Guard against multiple inclusion.*/
#define APP_H

#ifdef __cplusplus                                                                      /* Provide C++ Compatibility */
extern "C" {
#endif

/**************************************************************************************/
/* ************************************************************************************/
/* Section: Included Files                                                            */
/**************************************************************************************/
/**************************************************************************************/

#include <stdint.h>

/**************************************************************************************/
/**************************************************************************************/
/* Section: Data Types                                                                */
/**************************************************************************************/
/**************************************************************************************/

/**************************************************************************************/
/* APP_DATA

  Summary:
    Holds APP_DATA used for the APP tasks.

  Description:
    Holds APP_DATA used for the APP tasks. The variables
    used are stored here.

  Remarks:
    None
 */

typedef struct
{  
    uint16_t RevNumber; 
    
} APP_DATA1;

extern APP_DATA1 APP;
/**************************************************************************************/
/**************************************************************************************/
/* Section: Application Initialization and State Machine Functions                    */
/**************************************************************************************/
/**************************************************************************************/
	
/*!*************************************************************************************
  Function:
    void APP_Initialize(void)

  Summary:
     Panel Interface application initialization routine.

  Description:
    This function initializes the application.  It places the 
    application in its initial state and prepares it to run so that its 
    APP_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    APP_Initialize()

  Remarks:
    This routine must be called from the main function.
*/

void APP_Initialize ( void );


/*!*************************************************************************************
  Function:
    void APP_Tasks(void)

  Summary:
    Application tasks function

  Description:
    This function is the main application's tasks function.  It contains the various
    tasks that are maintained during the operation of the shooting panel.

  Precondition:
    The system ("SYS_Initialize") and application ("APP_Initialize") initialization 
    should be called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Example:
    APP_Tasks()

  Remarks:
    This routine must be called from the main() routine.
 */

void APP_Tasks( void );


#ifdef __cplusplus                                                                      /* Provide C++ Compatibility.*/
}
#endif

#endif                                                                                  /* APP_H */

/***************************************************************************************
 End of File
 */

