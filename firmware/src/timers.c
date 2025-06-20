/**************************************************************************************/  
/** \file timers.c

  Company:
    Hunting Titan

  File Name:
    timers.c

  Summary:
    To provide timer functions to various parts of the program.

  Description:
    This file contains the state machine code for the TIMERS operation.  It 
    implements the logic of the TIMERS state machine.  It provides timer functions 
    to various parts of the program.  This machine uses TIMER instance 1.  It has 
    been configured to provide a 100uS interrupt. This is then used to generate 
    clocks at 100uS, 1mS, 10mS, 100mS and 1000mS.  Various task ticks are 
    generated as needed.
*/ 
/**************************************************************************************/

/**************************************************************************************/ 
/**************************************************************************************/ 
/* Section: Included Files                                                            */ 
/**************************************************************************************/ 
/**************************************************************************************/ 

#include "timers.h"
#include "adc.h"
#include "hvps.h"
#include "man.h"
#include "fsk.h"
#include "switches.h"
#include "wl_sps.h"
#include "wl_cps.h"
#include "system_okay.h"
#include "USB.h"
#include "high_side.h"
#include "hvps_test.h"
#include "gpt.h"
#include "gamma.h"

#include "report.h"
#include "hid.h"
#include <stdbool.h>                                                                    /* Defines true.*/
#include "peripheral/ports/plib_ports.h"
#include "system/int/sys_int.h"
/*LDRA_HEADER_END : This resets the header comment count.*/

/**************************************************************************************/ 
/**************************************************************************************/ 
/* Section: Structure Data and Local Variables                                        */ 
/**************************************************************************************/ 
/**************************************************************************************/ 
/* Structure Data

  Summary:
    These structures hold required data.

  Description:
    These structures hold required data. These are here to link these 
    structures for use by the local functions.
  Remarks:
    
    
    These are defined in timers.h
*/

TIMER_DATA TIMER;
APP_DATA appData;

static TIMER_STATES T_STATES;

/**************************************************************************************/ 
/**************************************************************************************/ 
/* Section: State Machine Functions                                                   */ 
/**************************************************************************************/ 
/**************************************************************************************/ 

/*************************************************************************************** 
  Function:
    void TIMER_Tasks ( void )

  Summary:
   This routine is the TIMER_Tasks function.  It defines the (TIMER) state machine and
   core logic.

  Remarks:
    Refer to the timers.h interface header for function usage details.
 */

void TIMER_Tasks ( void )                                                               /* Timer state machine.*/
{ 
    switch ( TIMER.state )                                                              /* Check the TIMERS current state.*/
    {        
        case TIMER_STATE_INIT:                                                          /* TIMERS initial state.*/
        {            
            TIMER.tmrDrvHandle = DRV_HANDLE_INVALID;                                    /* Don't use until TIMER instance 1 is opened.*/
            TIMER.state = TIMER_STATE_TIMER_START;                                      /* Move on to start the timer and initialize counts.*/
        }
        break;
        
        case TIMER_STATE_TIMER_START:
        {
            if(TIMER.tmrDrvHandle == DRV_HANDLE_INVALID)                                /* If Timer instance 1 has not been opened,*/
            {
                TIMER.tmrDrvHandle = DRV_TMR_Open ( DRV_TMR_INDEX_1,
                                                DRV_IO_INTENT_EXCLUSIVE );              /* Open Timer instance 1.  It is using Timer 7. Set for 100uS.*/
            }
            
            if ( TIMER.tmrDrvHandle != DRV_HANDLE_INVALID  )                            /* If Timer instance 1 is open,*/
            {
                (void)DRV_TMR_Start(TIMER.tmrDrvHandle);                                /* Start the timer.*/
            
                TIMER.timer1_100uS_tick = false;                                        /* Initialize timer1 100uS Timer Tick to false.*/
                TIMER.timer1_1mS_tick = false;                                          /* Initialize timer1 1mS Timer Tick to false.*/                                         
                TIMER.timer1_10mS_tick = false;                                         /* Initialize timer1 10mS Timer Tick to false.*/                                         
                TIMER.timer1_100mS_tick = false;                                        /* Initialize timer1 100mS Timer Tick to false.*/ 
                TIMER.timer1_1000mS_tick = false;                                       /* Initialize timer1 1000mS Timer Tick to false.*/ 
                
                TIMER.timer1_100uS_count = 0U;                                          /* Initialize timer1 100uS count to 0.*/
                TIMER.timer1_1mS_count = 0U;                                            /* Initialize timer1 1mS count to 0.*/
                TIMER.timer1_10mS_count = 0U;                                           /* Initialize timer1 10mS count to 0.*/
                TIMER.timer1_100mS_count = 0U;                                          /* Initialize timer1 100mS count to 0.*/
                TIMER.timer1_1000mS_count = 0U;                                         /* Initialize timer11 1000mS count to 0.*/

                TIMER.state = TIMER_STATE_SERVICE_TASKS;                                /* Move on to perform the Timer tasks.*/
            }
        }  
        break;
         
        case TIMER_STATE_SERVICE_TASKS:
        { 
            if (TIMER.timer1_100uS_tick == true)                                        /* Check if interrupt changed Timer1_100uS_Tick flag.*/ 
            {                                                                                        
                TIMER.timer1_100uS_tick = false;                                        /* Reset the Timer1_100uS_Tick flag.*/
//                HV_PS.tick = true;                                                      /* Flag to allow the HV_PS control voltage to be adjusted.*/
//                HV_T_PS.tick = true;                                                    /* Set the Timer 1 tick.*/
//                FSK.tick = true;
                GPT.tick = true;
                TIMER.timer1_100uS_count++;
                if(TIMER.timer1_100uS_count > 9U )                                      /* If we have exceeded nine counts,*/
                {
                    TIMER.timer1_100uS_count = 0U;                                      /* reset the counter and*/
                    TIMER.timer1_1mS_tick = true;                                       /* set the 1mS tick to true to indicate 1mS has elapsed.*/
                }
            }
            
            if (TIMER.timer1_1mS_tick == true )                                         /* If the Timer1_1mS_Tick flag is set,*/
            {                                           
                TIMER.timer1_1mS_tick = false;                                          /* reset the Timer1_1mS_Tick flag.*/
//                ADC.tick=true;                                                          /* Flag to allow ADC to retrieve any new ADC values.*/
//                WL_SPS.tick = true; 
//                GAM.tick = true;
                TIMER.timer1_1mS_count++;                                               /* Increment the 1mS counter.*/
                if(TIMER.timer1_1mS_count > 9U )                                        /* If we have exceeded nine counts,*/
                {
                    TIMER.timer1_1mS_count = 0U;                                        /* reset the counter and*/
                    TIMER.timer1_10mS_tick = true;                                      /* set the 10mS tick to true to indicate 10mS has elapsed.*/
                }
            }
            
            if (TIMER.timer1_10mS_tick == true )                                        /* If the Timer1_10mS_Tick flag is set,*/
            {                                            
                TIMER.timer1_10mS_tick = false;                                         /* reset the Timer1_10mS_Tick flag.*/ 
//                MAN.tick = true;                                                        /* Set to true so the Manchester timer can be incremented.*/
//                AUTO_CF.new_current_values_flag = true;
//                appData.hidDataReceived = true;                                         /* Set this to true to initiate a data transfer.*/
//                appData.receiveDataBuffer[0] = 0x6E;                                    /* Set this value to ensure proper operation.*/
//                appData.state = HID_STATE_TRANSMIT;
                HIGH_SIDE.tick = true;
                appData.timer_tick = true;
                TIMER.count = TIMER.count + 1U;                                         /* Fill report array with data transmission counts.*/
                REPORT.data[4] = ((TIMER.count & 0xFF000000U)>> 24);
                REPORT.data[5] = ((TIMER.count & 0x00FF0000U)>> 16);
                REPORT.data[6] = ((TIMER.count & 0x0000FF00U)>> 8);
                REPORT.data[7] = TIMER.count & 0x000000FFU;
                TIMER.timer1_10mS_count++;                                              /* Increment the 10mS counter.*/
                if(TIMER.timer1_10mS_count > 9U )                                       /* If we have exceeded nine counts,*/
                {
                    TIMER.timer1_10mS_count = 0U;                                       /* reset the counter and*/
                    TIMER.timer1_100mS_tick = true;                                     /* set the 100mS tick to true to indicate 100mS has elapsed.*/
                }
            }
            
            if (TIMER.timer1_100mS_tick == true )                                       /* If the Timer1_100mS_Tick flag is set,*/
            { 
                SWITCH.STATUS_SW_debounce_tick = true;
//                HV_PS.spike_delay_tick = true;
//                SWITCH.ARM_CF_debounce_tick = true;
//                SWITCH.ENABLE_debounce_tick = true;
                TIMER.timer1_100mS_tick = false;                                        /* reset the Timer1_100mS_Tick flag.*/                
                TIMER.timer1_100mS_count++;                                             /* Increment the 100mS counter.*/
                if(TIMER.timer1_100mS_count > 9U )                                      /* If we have exceeded nine counts,*/
                {
                    TIMER.timer1_100mS_count = 0U;                                      /* reset the counter and*/
                    TIMER.timer1_1000mS_tick = true;                                    /* set the 100mS tick to true to indicate 1000mS has elapsed.*/
                }
            }
            if (TIMER.timer1_1000mS_tick == true )                                      /* If the Timer1_1000mS_Tick flag is set,*/
            {
                GAM.count_flag = true;                                                  /* Flag to allow gamma counts to be reported.*/
                GAM.count_reset_tick = true;
                GPT.inter_timer_tick = true;
//                SWITCH.DUMP_fire_debounce_tick = true; 
//                WL_CPS.tick = true;
//                HV_PS.run_time_tick = true;
//                HV_T_PS.test_timer_tick = true;
//                HV_PS.sensor_offset_tick = true;
//                WL_SPS.sensor_offset_tick = true;
//                CF.sensor_offset_tick = true;
//                USB.tick = true;
//                SW_COM.DUMP_fire_led_tick = true;                                       /* Set to true so the DUMP_fire_LED can toggle.*/
//                HV_PS.fault_timeout_tick = true;
                TIMER.timer1_1000mS_tick = false;                                       /* reset the Timer1_1000mS_Tick flag.*/ 
                TIMER.timer1_1000mS_count++;                                            /* Increment the 1000mS counter.*/
                if(TIMER.timer1_1000mS_count > 9U )                                     /* If we have exceeded nine counts,*/
                {
                    TIMER.timer1_1000mS_count = 0U;                                     /* reset the counter.*/
                }
            }
        }
        break;
        
        default:
        {
           /*Comment.*/
        }
        break;
    }
}

/***************************************************************************************
 End of File
 */


