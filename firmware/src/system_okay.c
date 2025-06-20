/**************************************************************************************/
/** \file system_okay.c
  
  Company:
   Hunting Titan

  File Name:
    system_okay.c

  Summary:
    This file contains the state machine code for the SYSTEM_OKAY operation.   

  Description:
    This file contains the state machine code for the SYSTEM_OKAY operation.  It 
    implements the logic of the SYSTEM_OKAY's state machine. Once started, the 
    SYSTEM_OKAY waits for a tick from timers.c If the main controller check fails, 
    the task turns on an LED to indicate an issue and warns the user that an issue has 
    occurred. After the check is completed, the machine is set to idle and is no 
    longer used. The states are configured so that other system tasks can be 
    maintained while these tasks are waiting for an event to occur.
 */
/**************************************************************************************/

/**************************************************************************************/
/**************************************************************************************/
/* Section: Included Files                                                            */
/**************************************************************************************/
/**************************************************************************************/

/* This section lists the other files that are included in this file.                 */

#include "system_okay.h"
#include <stddef.h>
#include <stdlib.h>
#include"../system_config.h"
#include"../system_definitions.h"
#include "test.h"
#include "hvps_test.h"
#include "switches.h"
/*LDRA_HEADER_END : This resets the header comment count.*/

/**************************************************************************************/
/**************************************************************************************/
/* Section: Structure Data and Local Variables                                        */
/**************************************************************************************/
/**************************************************************************************/

/* SYSTEM_OKAY Data

  Summary:
    This structure holds the required states and variables to perform the 
    SYSTEM_OKAY tasks.

  Description:
    These structures hold required data. These are here to link these 
    structures for use by the local functions.
 
  Remarks:
    This structures are defined in system_okay.h.   
    
*/

SYSTEM_OKAY_DATA SYSTEM_OKAY;

/**************************************************************************************/
/**************************************************************************************/
/* Section: State Machine Functions                                                   */
/**************************************************************************************/
/**************************************************************************************/

/*************************************************************************************** 
  Function:
    void SYSTEM_OKAY_Tasks (void)

  Summary:
   This routine is the SYSTEM_OKAY tasks function.  It defines the (SYSTEM_OKAY) 
   state machine and core logic.  Once the code has completed, it is set to IDLE and no
   longer used.

  Remarks:
    Refer to the system_okay.h interface header for function usage details.
 */

void SYSTEM_OKAY_Tasks(void)
{
    switch ( SYSTEM_OKAY.state )
    {
        case SYSTEM_OKAY_STATE_INIT:                                                    /* Initializes the SYSTEM_OKAY machine.*/  
        {
            SYSTEM_OKAY.pass == false;
//            SYSTEM_OKAY.state=SYSTEM_OKAY_STATE_START;                                  /* Change state to complete test function.*/ 
            SYSTEM_OKAY.state=SYSTEM_OKAY_STATE_TEST;                                  /* Change state to complete test function.*/ 
        }
        break;

        case SYSTEM_OKAY_STATE_START:                                                   /* This state checks a flag to indicate when the SYSTEM_OKAY tick has completed a cycle.*/                                                      
        {                                                                                        
//            if((HV_T_PS.test_in_progress == false) && (SAFE_SWStateGet() == 1U))        /* If the HV_PS self test has completed and the key switch is not in the safe position,*/                                                       
//            {                                                                           /* this indicates we are in the main part of the program.*/
//                SYSTEM_OKAY.state = SYSTEM_OKAY_STATE_TEST;                             /* Move on to complete the system test.*/
//            }           
        }
        break;
        
        case SYSTEM_OKAY_STATE_TEST:                                                    /* Finalize the system status and set the LED accordingly.*/
        {                                                                               
//            if( (HV_T_PS.test_pass == false) || 
//                    (TEST_FLAG.returnCode != CLASSB_TEST_PASS))                         /* If the HVPS test did not pass or*/                                                                   /* If the HVPS returned a bad result or*/
//                                                                                        /* the main controller returned a bad result from test.c,*/   
            if( (TEST_FLAG.returnCode != CLASSB_TEST_PASS))                             /* If the main controller returned a bad result from test.c,*/  
            {
                STATUS_LED_On();                                                        /* Set STATUS_LED on to indicate a system failure.*/
//                DMP_FIRE_LEDOn();                                                       /* Set DMP_FIRE_LED on to indicate a system failure.*/ 
                Set_Status(1);                                                          /* Set status bit zero to indicate a system failure.*/
//                HV_T_PS.test_pass = true;                                               /* Reset the flag.*/
                
            }
            else                                                                        /* Otherwise,*/
            {
                SYSTEM_OKAY.pass = true;
                STATUS_LED_Off();                                                       /* turn STATUS_LED off to indicate system pass.*/
//                DMP_FIRE_LEDOff();                                                      /* turn DMP_FIRE_LED off to indicate system pass.*/
                Clear_Status(1);                                                        /* Clear status bit zero to indicate the system test passed.*/
            }
            SYSTEM_OKAY.state = SYSTEM_OKAY_STATE_IDLE;                                 /* System checks are complete.*/
        }
        break;
        
        case SYSTEM_OKAY_STATE_IDLE:
        {
            /*Comment*/
        }
        break;
        
        default:
        {
            break;
        }
    }
}

/***************************************************************************************
 End of File
 */
