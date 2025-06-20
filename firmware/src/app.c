/**************************************************************************************/
/** \file app.c
  
  Company:
    Hunting Titan
  
  File Name:
    app.c

  Summary:
    This file controls the application functions for the shooting panel main 
    controller.

  Description:
    This file controls the application functions for the shooting panel main 
    controller. It implements the logic of the application's state machines and it may 
    call API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.   
*/ 
/**************************************************************************************/

/**************************************************************************************/
/**************************************************************************************/
/* Section: Included Files                                                            */
/**************************************************************************************/
/**************************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include"../system_config.h"
#include"../system_definitions.h"

#include "app.h"
#include "switches.h"
#include "adc.h"
#include "commmodule.h"
//#include "hvps.h"
//#include "wl_sps.h"
//#include "wl_cps.h"
//#include "fsk.h"
//#include "man.h"
#include "fifo.h"
#include "commands.h"
#include "timers.h"
//#include "USB.h"
#include "hid.h"
#include "UART.h"
#include "high_side.h"
#include "system_okay.h"
//#include "hvps_test.h"
#include "gpt.h"
#include "gamma.h"
//#include "wl_sps_v.h"
#include "nvm_fs.h"
#include "report.h"

/**************************************************************************************/
/**************************************************************************************/
/* Section: Structure Data and Local Variables                                        */
/**************************************************************************************/
/**************************************************************************************/

/**************************************************************************************/
/*  appData Data

  Summary:
    This structure holds the required variables to perform the APP tasks.

  Description:
    This structures holds the required variables to perform the APP tasks. 
    These are here to link these structures for use by the local functions.
 
  Remarks: 
    These are defined in app.h
*/

//APP_DATA APP;
NVM_FS_DATA nvmfsData;


/**************************************************************************************/
/**************************************************************************************/
/* Section: Application Initialization and State Machine Functions                    */
/**************************************************************************************/
/**************************************************************************************/

/***************************************************************************************
  Function:
    void APP_Initialize ( void )
  
  Summary:
   Shooting panel application initialization routine.

  Remarks:
    See prototype in app.h.
*/

void APP_Initialize ( void )
{    
//    ADC.state = ADC_STATE_INIT;                                                         /* Initialize the ADC task machine.*/
    SWITCH.state = SWITCH_STATE_INIT;                                                   /* Initialize the SWITCH task machine.*/
    COMM.state = COMM_STATE_INIT;                                                       /* Initialize the COMM task machine.*/
    CMD.state = COMMAND_STATE_INIT;                                                     /* Initialize the CMD task machine.*/
    TIMER.state = TIMER_STATE_INIT;                                                     /* Initialize the TIMER state machine.*/
//    USB.state =  USB_STATE_INIT;                                                        /* Initialize the USB state machine.*/
    HID_Initialize();                                                                   /* Initialize the HID communication.*/
//    UART.state = UART_STATE_INIT;                                                       /* Initialize the UART state machine.*/
    Init_Fifo();                                                                        /* Initialize the FIFO.  There is no state machine.*/
    SYSTEM_OKAY.state = SYSTEM_OKAY_STATE_INIT;                                         /* Initialize the SYSTEM_OKAY state machine.*/
    GPT.state = GPT_RX_STATE_INIT;
    HIGH_SIDE.state = HIGH_SIDE_STATE_INIT;
    NVM_FS_Initialize();
    Alarm_GPT();                                                                      /* Initialize the 200uS callback alarm for the GPT tool.*/
//    APP.RevNumber = 2123;                                                               /* The firmware revision number.  Divide by 1000 on host side.*/
                                                                                        /* The most significant digit represents the controller memory.*/
                                                                                        /* 1 equals 512, 2 equals 1024, 3 equals 2048. The remaining*/
                                                                                        /* digits represent the code revision level.*/
 }


/*************************************************************************************** 
  Function:
    void APP_Tasks(void)

  Summary:
   This routine is the APP_Tasks function.  This is where the application
   manipulates the various state machines.

  Remarks:
    Refer to the app.h interface header for function usage details.
 */

void APP_Tasks ( void )
{   
//    ADC_Tasks();                                                                        /* ADC tasks.*/
    SWITCH_Tasks();                                                                     /* Front panel switch and relay control tasks.*/
    COMM_Tasks();                                                                       /* Host communication tasks.*/
    COMMAND_Tasks();                                                                    /* Command tasks.*/
    TIMER_Tasks();                                                                      /* Timer Tasks to control various functions.*/
//    USB_Tasks();                                                                        /* USB Tasks to control USB communications.*/
    HID_Tasks();                                                                        /* HID Tasks to control USB communications.*/
//    UART_Tasks();                                                                       /* UART Tasks to control UART communications.*/
    SYSTEM_OKAY_Tasks();                                                                /* Tasks to verify health of the controller.*/
                                                                                        /* value for more accurate results.*/
    GPT_RX_Tasks();
    GAMMA_Tasks();
    GAMMA_Counts();
    HIGH_SIDE_Tasks();
    NVM_FS_Tasks();                                                                     /* Store gamma gain changes as needed.*/
    DACQ_ReportCreate();                                                                /* Create the report for transmission to the host.*/
}

/***************************************************************************************
 End of File
 */
