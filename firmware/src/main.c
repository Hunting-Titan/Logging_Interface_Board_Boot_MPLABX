/**************************************************************************************/
/** \file main.c
  
  Company:
   Hunting Titan
  
  File Name:
    main.c

  Summary:
    This file contains the "main" function for the shooting power supply panel.

  Description:
    This file contains the "main" function for the shooting power supply panel.  The
    "main" function calls the "SYS_Initialize" function to initialize the state 
    machines of all MPLAB Harmony modules in the system and it calls the 
    "SYS_Tasks" function from within a system-wide "super" loop to maintain 
    their correct operation. These two functions are implemented in 
    configuration-specific files (usually "system_init.c" and "system_tasks.c")
    in a configuration-specific folder under the "src/system_config" folder 
    within this project's top-level folder.  The APP_Initialize and APP_Tasks functions 
    are implemented in app.c and contain the application specific files. 
*/ 
/**************************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

//Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


/**************************************************************************************/
/**************************************************************************************/
/* Section: Included Files                                                            */
/**************************************************************************************/
/**************************************************************************************/

#include <stddef.h>                                                                     /* Defines NULL.*/
#include <stdbool.h>                                                                    /* Defines true, false.*/
#include <stdlib.h>                                                                     /* Defines EXIT_FAILURE.*/
#include "system/common/sys_module.h"                                                   /* SYS function prototypes.*/
#include "app.h"
#include "test.h"

/**************************************************************************************/
/**************************************************************************************/
/* Section: Main Entry Point                                                          */
/**************************************************************************************/
/**************************************************************************************/

int main ( void )
{   
    TEST_Tasks();                                                                       /* Class B Tests to ensure controller operation.*/
    SYS_Initialize ( NULL );                                                            /* Initialize all MPLAB Harmony modules.*/    
    APP_Initialize();                                                                   /* Initialize the Application.*/

    while ( true )
    {        
        SYS_Tasks();                                                                    /* Maintain state machines of all polled MPLAB Harmony modules.*/         
        APP_Tasks();                                                                    /* Maintain the application's state machines.*/                                                
    }
                                                                                        /* Execution should not come here during normal operation */
    return ( EXIT_FAILURE );
}

/***************************************************************************************
 End of File
 */

