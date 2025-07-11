/*******************************************************************************
  Timer Driver Interface Declarations for Static Single Instance Driver

  Company:
    Microchip Technology Inc.

  File Name:
    drv_tmr_static.h

  Summary:
    Timer driver interface declarations for the static single instance driver.

  Description:
    The Timer device driver provides a simple interface to manage the Timer
    modules on Microchip microcontrollers. This file defines the interface
    Declarations for the TMR driver.
    
  Remarks:
    Static interfaces incorporate the driver instance number within the names
    of the routines, eliminating the need for an object ID or object handle.
    
    Static single-open interfaces also eliminate the need for the open handle.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTOCULAR PURPOSE.
IN NO EVENT SHALL MOCROCHIP OR ITS LOCENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STROCT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVOCES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*******************************************************************************/
//DOM-IGNORE-END

#ifndef _DRV_TMR_STATIC_H
#define _DRV_TMR_STATIC_H
// *****************************************************************************
// *****************************************************************************
// Section: Include Headers
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include "driver/tmr/drv_tmr.h"
#include "peripheral/tmr/plib_tmr.h"
#include "peripheral/int/plib_int.h"

// maximum divider value for 32 bit operation mode
#define     DRV_TIMER_DIVIDER_MAX_32BIT     0xffffffff

// minimum divider value for 32 bit operation mode
#define     DRV_TIMER_DIVIDER_MIN_32BIT     0x2

// maximum divider value for 16 bit operation mode
#define     DRV_TIMER_DIVIDER_MAX_16BIT     0x10000

// minimum divider value for 16 bit operation mode
#define     DRV_TIMER_DIVIDER_MIN_16BIT     0x2


// *****************************************************************************
// *****************************************************************************
// Section: Interface Headers for Instance 0 for the static driver
// *****************************************************************************
// *****************************************************************************

void DRV_TMR0_Initialize(void);
bool DRV_TMR0_Start(void);
void DRV_TMR0_Stop(void);
static inline void DRV_TMR0_DeInitialize(void)
{
	DRV_TMR0_Stop();
}
static inline SYS_STATUS DRV_TMR0_Status(void)
{
	/* Return the status as ready always */
    return SYS_STATUS_READY; 
}
static inline void DRV_TMR0_Open(void) {}
DRV_TMR_CLIENT_STATUS DRV_TMR0_ClientStatus ( void );
static inline DRV_TMR_OPERATION_MODE DRV_TMR0_OperationModeGet(void)
{
    return DRV_TMR_OPERATION_MODE_16_BIT;
}
static inline void DRV_TMR0_Close(void) 
{
    DRV_TMR0_Stop();
}
bool DRV_TMR0_ClockSet
(
    DRV_TMR_CLK_SOURCES clockSource, 
    TMR_PRESCALE  prescale 
);
void DRV_TMR0_CounterValueSet(uint32_t value);
uint32_t DRV_TMR0_CounterValueGet(void);
void DRV_TMR0_CounterClear(void);
TMR_PRESCALE DRV_TMR0_PrescalerGet(void);
void DRV_TMR0_PeriodValueSet(uint32_t value);
uint32_t DRV_TMR0_PeriodValueGet(void);
void DRV_TMR0_StopInIdleDisable(void);
void DRV_TMR0_StopInIdleEnable(void);
static inline void DRV_TMR0_Tasks(void) {}
uint32_t DRV_TMR0_CounterFrequencyGet(void);
DRV_TMR_OPERATION_MODE DRV_TMR0_DividerRangeGet
(
    DRV_TMR_DIVIDER_RANGE * pDivRange
);
// *****************************************************************************
// *****************************************************************************
// Section: Interface Headers for Instance 1 for the static driver
// *****************************************************************************
// *****************************************************************************

void DRV_TMR1_Initialize(void);
bool DRV_TMR1_Start(void);
void DRV_TMR1_Stop(void);
static inline void DRV_TMR1_DeInitialize(void)
{
	DRV_TMR1_Stop();
}
static inline SYS_STATUS DRV_TMR1_Status(void)
{
	/* Return the status as ready always */
    return SYS_STATUS_READY; 
}
static inline void DRV_TMR1_Open(void) {}
DRV_TMR_CLIENT_STATUS DRV_TMR1_ClientStatus ( void );
static inline DRV_TMR_OPERATION_MODE DRV_TMR1_OperationModeGet(void)
{
    return DRV_TMR_OPERATION_MODE_16_BIT;
}
static inline void DRV_TMR1_Close(void) 
{
    DRV_TMR1_Stop();
}
bool DRV_TMR1_ClockSet
(
    DRV_TMR_CLK_SOURCES clockSource, 
    TMR_PRESCALE  prescale 
);
void DRV_TMR1_CounterValueSet(uint32_t value);
uint32_t DRV_TMR1_CounterValueGet(void);
void DRV_TMR1_CounterClear(void);
TMR_PRESCALE DRV_TMR1_PrescalerGet(void);
void DRV_TMR1_PeriodValueSet(uint32_t value);
uint32_t DRV_TMR1_PeriodValueGet(void);
void DRV_TMR1_StopInIdleDisable(void);
void DRV_TMR1_StopInIdleEnable(void);
static inline void DRV_TMR1_Tasks(void) {}
uint32_t DRV_TMR1_CounterFrequencyGet(void);
DRV_TMR_OPERATION_MODE DRV_TMR1_DividerRangeGet
(
    DRV_TMR_DIVIDER_RANGE * pDivRange
);
// *****************************************************************************
// *****************************************************************************
// Section: Interface Headers for Instance 2 for the static driver
// *****************************************************************************
// *****************************************************************************

void DRV_TMR2_Initialize(void);
bool DRV_TMR2_Start(void);
void DRV_TMR2_Stop(void);
static inline void DRV_TMR2_DeInitialize(void)
{
	DRV_TMR2_Stop();
}
static inline SYS_STATUS DRV_TMR2_Status(void)
{
	/* Return the status as ready always */
    return SYS_STATUS_READY; 
}
static inline void DRV_TMR2_Open(void) {}
DRV_TMR_CLIENT_STATUS DRV_TMR2_ClientStatus ( void );
static inline DRV_TMR_OPERATION_MODE DRV_TMR2_OperationModeGet(void)
{
    return DRV_TMR_OPERATION_MODE_16_BIT;
}
static inline void DRV_TMR2_Close(void) 
{
    DRV_TMR2_Stop();
}
bool DRV_TMR2_ClockSet
(
    DRV_TMR_CLK_SOURCES clockSource, 
    TMR_PRESCALE  prescale 
);
void DRV_TMR2_CounterValueSet(uint32_t value);
uint32_t DRV_TMR2_CounterValueGet(void);
void DRV_TMR2_CounterClear(void);
TMR_PRESCALE DRV_TMR2_PrescalerGet(void);
void DRV_TMR2_PeriodValueSet(uint32_t value);
uint32_t DRV_TMR2_PeriodValueGet(void);
void DRV_TMR2_StopInIdleDisable(void);
void DRV_TMR2_StopInIdleEnable(void);
static inline void DRV_TMR2_Tasks(void) {}
uint32_t DRV_TMR2_CounterFrequencyGet(void);
DRV_TMR_OPERATION_MODE DRV_TMR2_DividerRangeGet
(
    DRV_TMR_DIVIDER_RANGE * pDivRange
);
// *****************************************************************************
// *****************************************************************************
// Section: Interface Headers for Instance 3 for the static driver
// *****************************************************************************
// *****************************************************************************

void DRV_TMR3_Initialize(void);
bool DRV_TMR3_Start(void);
void DRV_TMR3_Stop(void);
static inline void DRV_TMR3_DeInitialize(void)
{
	DRV_TMR3_Stop();
}
static inline SYS_STATUS DRV_TMR3_Status(void)
{
	/* Return the status as ready always */
    return SYS_STATUS_READY; 
}
static inline void DRV_TMR3_Open(void) {}
DRV_TMR_CLIENT_STATUS DRV_TMR3_ClientStatus ( void );
static inline DRV_TMR_OPERATION_MODE DRV_TMR3_OperationModeGet(void)
{
    return DRV_TMR_OPERATION_MODE_16_BIT;
}
static inline void DRV_TMR3_Close(void) 
{
    DRV_TMR3_Stop();
}
bool DRV_TMR3_ClockSet
(
    DRV_TMR_CLK_SOURCES clockSource, 
    TMR_PRESCALE  prescale 
);
void DRV_TMR3_CounterValueSet(uint32_t value);
uint32_t DRV_TMR3_CounterValueGet(void);
void DRV_TMR3_CounterClear(void);
TMR_PRESCALE DRV_TMR3_PrescalerGet(void);
void DRV_TMR3_PeriodValueSet(uint32_t value);
uint32_t DRV_TMR3_PeriodValueGet(void);
void DRV_TMR3_StopInIdleDisable(void);
void DRV_TMR3_StopInIdleEnable(void);
static inline void DRV_TMR3_Tasks(void) {}
uint32_t DRV_TMR3_CounterFrequencyGet(void);
DRV_TMR_OPERATION_MODE DRV_TMR3_DividerRangeGet
(
    DRV_TMR_DIVIDER_RANGE * pDivRange
);
// *****************************************************************************
// *****************************************************************************
// Section: Interface Headers for Instance 5 for the static driver
// *****************************************************************************
// *****************************************************************************

void DRV_TMR5_Initialize(void);
bool DRV_TMR5_Start(void);
void DRV_TMR5_Stop(void);
static inline void DRV_TMR5_DeInitialize(void)
{
	DRV_TMR5_Stop();
}
static inline SYS_STATUS DRV_TMR5_Status(void)
{
	/* Return the status as ready always */
    return SYS_STATUS_READY; 
}
static inline void DRV_TMR5_Open(void) {}
DRV_TMR_CLIENT_STATUS DRV_TMR5_ClientStatus ( void );
static inline DRV_TMR_OPERATION_MODE DRV_TMR5_OperationModeGet(void)
{
    return DRV_TMR_OPERATION_MODE_16_BIT;
}
static inline void DRV_TMR5_Close(void) 
{
    DRV_TMR5_Stop();
}
bool DRV_TMR5_ClockSet
(
    DRV_TMR_CLK_SOURCES clockSource, 
    TMR_PRESCALE  prescale 
);
void DRV_TMR5_CounterValueSet(uint32_t value);
uint32_t DRV_TMR5_CounterValueGet(void);
void DRV_TMR5_CounterClear(void);
TMR_PRESCALE DRV_TMR5_PrescalerGet(void);
void DRV_TMR5_PeriodValueSet(uint32_t value);
uint32_t DRV_TMR5_PeriodValueGet(void);
void DRV_TMR5_StopInIdleDisable(void);
void DRV_TMR5_StopInIdleEnable(void);
bool DRV_TMR5_AlarmRegister(
    uint32_t divider, 
    bool isPeriodic, 
    uintptr_t context, 
    DRV_TMR_CALLBACK callBack 
);
bool DRV_TMR5_AlarmDisable(void);
void DRV_TMR5_AlarmEnable(bool enable);
void DRV_TMR5_AlarmPeriodSet(uint32_t value);
uint32_t DRV_TMR5_AlarmPeriodGet(void);
void DRV_TMR5_AlarmDeregister(void);
uint32_t DRV_TMR5_AlarmHasElapsed(void);
void DRV_TMR5_Tasks(void);
uint32_t DRV_TMR5_CounterFrequencyGet(void);
DRV_TMR_OPERATION_MODE DRV_TMR5_DividerRangeGet
(
    DRV_TMR_DIVIDER_RANGE * pDivRange
);
#endif // #ifndef _DRV_TMR_STATIC_H

/*******************************************************************************
 End of File
*/
