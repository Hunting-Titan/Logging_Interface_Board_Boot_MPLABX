/**************************************************************************************/
/** \file test.h

  Company:
    Hunting Titan

  File Name:
    test.h

  Summary:
    This header file provides prototypes and definitions for test.c.

  Description:
    This header file provides function prototypes and data type definitions for
    test.c.  The majority of this code is taken from the CLASS B demo code. 
 
***************************************************************************************/

/*DOM-IGNORE-BEGIN*/
/***************************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
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
***************************************************************************************/
/*DOM-IGNORE-END*/

#ifndef TEST_H                                                                          /* Guard against multiple inclusion.*/
#define TEST_H

#ifdef __cplusplus                                                                      /* Provide C++ Compatibility*/
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
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"
#include "classb/classb.h"

/**************************************************************************************/
/**************************************************************************************/
/* Section: Data Types                                                                */
/**************************************************************************************/
/**************************************************************************************/

/**************************************************************************************/
/* TEST_FLAG Data

  Summary:
    Holds TEST_FLAG_DATA used for the TEST tasks.

  Description:
    Holds TEST_FLAG_DATA used for the TEST tasks. The and variables used to record 
    TEST functions are stored here.

  Remarks:
    None.
 */
typedef struct 
{
    CLASSBRESULT  cpuRegister_TestResult;
    CLASSBRESULT  programCounter_TestResult;
    CLASSBRESULT  checkerboardRam_TestResult;
    CLASSBRESULT  marchCRam_TestResult;
    CLASSBRESULT  marchCMinusRam_TestResult;
    CLASSBRESULT  marchCRamStack_TestResult;
    CLASSBRESULT  marchBRam_TestResult;
    CLASSBRESULT  flash_TestResult;
    CLASSBRESULT  clock_TestResult;
    CLASSBRESULT  clockLine_TestResult;
    CLASSBRESULT  returnCode;
    
}ClassB_Test_Flags ;

extern ClassB_Test_Flags TEST_FLAG;
	
/**************************************************************************************/
/**************************************************************************************/
/* Section: Interface Functions                                                     */
/**************************************************************************************/
/**************************************************************************************/


/***************************************************************************************
  Function:
    void TEST_Tasks (void)

  Summary:
    Class B controller test function.

  Description:
    Class B controller test function. It implements several self tests to ensure the 
    PIB controller is operating correctly prior to the start of any system 
    initialization. Any error here is flagged and the result is used in 
    SYSTEM_OKAY_Tasks to set the DMPLED if there is an error.

  Precondition:
    This is called prior to any system and application initialization. 
 
  Parameters:
    None.

  Returns:
    None.

  Example:    
    TEST_Tasks()    

  Remarks:
    This function must be called from the main() routine.
 */

void TEST_Tasks(void);



#ifdef __cplusplus                                                                      /* Provide C++ Compatibility.*/
}
#endif

#endif                                                                                  /* TEST_H */

/***************************************************************************************
 End of File
 */

