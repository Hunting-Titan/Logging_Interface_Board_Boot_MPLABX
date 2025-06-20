/*******************************************************************************
 System Interrupts File

  File Name:
    system_interrupt.c

  Summary:
    Raw ISR definitions.

  Description:
    This file contains a definitions of the raw ISRs required to support the
    interrupt sub-system.

  Summary:
    This file contains source code for the interrupt vector functions in the
    system.

  Description:
    This file contains source code for the interrupt vector functions in the
    system.  It implements the system and part specific vector "stub" functions
    from which the individual "Tasks" functions are called for any modules
    executing interrupt-driven in the MPLAB Harmony system.

  Remarks:
    This file requires access to the systemObjects global data structure that
    contains the object handles to all MPLAB Harmony module objects executing
    interrupt-driven in the system.  These handles are passed into the individual
    module "Tasks" functions to identify the instance of the module to maintain.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2014 released Microchip Technology Inc.  All rights reserved.

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
 *******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "system/common/sys_common.h"
#include "app.h"
#include "system_definitions.h"
#include "adc.h"
#include "timers.h"
#include "wl_sps.h"
#include "hvps.h"
#include "wl_cps.h"
#include "fifo.h"
#include "uart.h"
#include "commmodule.h"
#include "man.h"
#include "high_side.h"
#include "wl_sps_v.h"
#include "gpt.h"
#include "gamma.h"
#include "switches.h"


GPT_DATA GPT;
// *****************************************************************************
// *****************************************************************************
// Section: System Interrupt Vector Functions
// *****************************************************************************
// *****************************************************************************
void __ISR(_CHANGE_NOTICE_C_VECTOR, ipl1AUTO) _IntHandlerChangeNotification_PortC(void) 
{
    uint32_t __attribute__ ((unused)) temp;
    
    temp = PLIB_PORTS_Read(PORTS_ID_0, GAMMA_PULSE_CN_PORT_CHANNEL);                    /* Read port to clear mismatch on change notice pin.*/
    GAM.f_count = GAM.f_count + 0.5F;                                                   /* Increment the count value. 0.5 accounts for two interrupts per gamma pulse.*/
    if(GAM.count_flag == true)
    {
        GAM.count_flag = false;                                                         /* Reset the one second flag.*/
        GAM.count = (int32_t)((GAM.f_count));                                           /* Convert to integer for data transmission.*/
        GAM.f_count = 0.0;                                                              /* Reset the count total for the next second.*/
        GAM.count_reset_flag = false;                                                   /* Reset to show we have received gamma pulses.*/
    }                  
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_CHANGE_NOTICE_C);
}
void __ISR(_CHANGE_NOTICE_D_VECTOR, ipl1AUTO) _IntHandlerChangeNotification_PortD(void) /* This port reads the data sync and data bits.*/
{
    uint32_t __attribute__ ((unused)) temp;
    
    temp = PLIB_PORTS_Read(PORTS_ID_0, GPT_DATA_CN_PORT_CHANNEL);                       /* Read port to clear mismatch on change notice pin.*/
    if(SWITCH.command_setting == 1U)
    {
        if((GPT.data_timer_started_flag == false) && (GPT.null_timer_complete == true)) /* If we have not received the start of a data sync or data pulse */
        {                                                                               /* and the null timer has completed,*/ 
            if(GPT.data_sync_received_flag == false)                                    /* If we have not received a data sync pulse for a channels data,*/
            {
                DRV_TMR_AlarmEnable(GPT.tmrHandle, true);                               /* Start the 200uS data period timer.*/
                DRV_TMR_Start(GPT.tmrHandle);
                LED2On();
                GPT.int_count = 0U;                                                     /* Reset the variables.*/
                GPT.data_timer_value = 0U;
                GPT.sync_data_timer_value = 0U;
            }
            LED1On();

            GPT.data_timer_started_flag = true;                                         /* Set the flag to show that the data timer has started.*/
            DRV_TMR2_CounterClear();                                                    /* Reset the data bit width timer.*/
            (void)DRV_TMR2_Start();                                                     /* Start the data bit width timer again.*/   
        }
        else if((GPT.data_timer_value == 0U)&&(GPT.data_timer_started_flag == true))    /* If we have not read a timer value and we have received a positive pulse,*/
        {
            if(GPT.data_sync_received_flag == false)                                    /* and if we have not received a data sync pulse,*/
            {
                LED1Off();
                GPT.sync_data_timer_value = DRV_TMR2_CounterValueGet();                 /* Record the timer count when the a change was detected on the port pin.*/
                DRV_TMR2_Stop();
                GPT.Rx_state = GPT_RX_STATE_SYNC_DATA;                                  /* move on to check if the data sync pulse is valid.*/
                GPT.sync_bit_count ++;
                if(GPT.sync_bit_count ==2U)                                             /* Testing.*/
                {
                    Nop();
                }
                GPT_RX_Tasks();                                                         /* Go to check for valid data sync pulse.*/
            }
            else                                                                        /* otherwise, we are receiving a data bit.*/
            {
                LED1Off();
                GPT.data_timer_value = DRV_TMR2_CounterValueGet();                      /* Record the timer count when the a change was detected on the port pin.*/
                DRV_TMR2_Stop();                                                        /* Stop the data bit width timer.*/
                GPT.Rx_state = GPT_RX_STATE_DATA;                                       /* Move on to check if the data pulse is valid.*/
                GPT.data_count++;                                                       /* Testing.*/
                GPT_RX_Tasks();                                                         /* Go to check for valid data pulse.*/
            }
        }  
    }
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_CHANGE_NOTICE_D);
}
void __ISR(_CHANGE_NOTICE_H_VECTOR, ipl1AUTO) _IntHandlerChangeNotification_PortH(void) /* This port reads the sync bits.*/
{
    uint32_t __attribute__ ((unused)) temp;

    temp = PLIB_PORTS_Read(PORTS_ID_0, GPT_SYNC_CN_PORT_CHANNEL);                       /* Read port to clear mismatch on change notice pin.*/
    if(SWITCH.command_setting == 1U)
    {
        if(GPT.sync_timer_started_flag == false)                                        /* If we have not received the start of a sync pulse,*/
        {
            GPT.sync_timer_started_flag = true;                                         /* Set the flag to show that we have started a sync pulse.*/
            DRV_TMR2_CounterClear();                                                    /* Reset the timer.*/
            (void)DRV_TMR2_Start();                                                     /* Start the timer again.*/
            GPT.sync_timer_value = 0U;
        //    LED1On();
        }
        else if(GPT.sync_timer_value == 0U)                                             /* If we have not recorded a sync pulse.*/
        {
        //    LED1Off();
            GPT.sync_timer_value = DRV_TMR2_CounterValueGet();                          /* Record the timer count when the a change was detected on the port pin.*/
            GPT.Rx_state = GPT_RX_STATE_SYNC;                                           /* move on to see if we received a valid sync pulse.*/
            GPT_RX_Tasks();
        }
    }           
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_CHANGE_NOTICE_H);
}
 


void __ISR(_TIMER_2_VECTOR, ipl4AUTO) IntHandlerDrvTmrInstance0(void)
{
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_2);
}
void __ISR(_TIMER_7_VECTOR, ipl3AUTO) IntHandlerDrvTmrInstance1(void)
{
    TIMER.timer1_100uS_tick = true;
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_7);
}
void __ISR(_TIMER_6_VECTOR, ipl1AUTO) IntHandlerDrvTmrInstance2(void)
{
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_6);
}
void __ISR(_TIMER_1_VECTOR, ipl2AUTO) IntHandlerDrvTmrInstance3(void)
{
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_1);
}
void __ISR(_TIMER_8_VECTOR, ipl2AUTO) IntHandlerDrvTmrInstance5(void)
{
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_8);
    DRV_TMR5_Tasks();
}
 
void __ISR(_FLASH_CONTROL_VECTOR, ipl3AUTO) _IntHandlerDrvNvm (void)
{
    DRV_NVM_Tasks(sysObj.drvNvm);

}

void __ISR(_USB_VECTOR, ipl4AUTO) _IntHandlerUSBInstance0(void)
{
    DRV_USBHS_Tasks_ISR(sysObj.drvUSBObject);
}

void __ISR ( _USB_DMA_VECTOR,ipl4AUTO) _IntHandlerUSBInstance0_USBDMA ( void )
{
    DRV_USBHS_Tasks_ISR_USBDMA(sysObj.drvUSBObject);
}
/*******************************************************************************
 End of File
*/
