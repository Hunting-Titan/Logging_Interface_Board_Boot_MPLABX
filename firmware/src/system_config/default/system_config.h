/*******************************************************************************
  MPLAB Harmony System Configuration Header

  File Name:
    system_config.h

  Summary:
    Build-time configuration header for the system defined by this MPLAB Harmony
    project.

  Description:
    An MPLAB Project may have multiple configurations.  This file defines the
    build-time options for a single configuration.

  Remarks:
    This configuration header must not define any prototypes or data
    definitions (or include any files that do).  It only provides macro
    definitions for build-time configuration options that are not instantiated
    until used by another MPLAB Harmony module or application.

    Created with MPLAB Harmony Version 2.06
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
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

#ifndef _SYSTEM_CONFIG_H
#define _SYSTEM_CONFIG_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section Includes other configuration headers necessary to completely
    define this configuration.
*/


// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: System Service Configuration
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
/* Common System Service Configuration Options
*/
#define SYS_VERSION_STR           "2.06"
#define SYS_VERSION               20600

// *****************************************************************************
/* Clock System Service Configuration Options
*/
#define SYS_CLK_FREQ                        200000000ul
#define SYS_CLK_BUS_PERIPHERAL_1            100000000ul
#define SYS_CLK_BUS_PERIPHERAL_2            100000000ul
#define SYS_CLK_BUS_PERIPHERAL_3            100000000ul
#define SYS_CLK_BUS_PERIPHERAL_4            100000000ul
#define SYS_CLK_BUS_PERIPHERAL_5            100000000ul
#define SYS_CLK_BUS_PERIPHERAL_7            200000000ul
#define SYS_CLK_BUS_PERIPHERAL_8            100000000ul
#define SYS_CLK_CONFIG_PRIMARY_XTAL         0ul
#define SYS_CLK_CONFIG_SECONDARY_XTAL       32768ul
   
/*** Ports System Service Configuration ***/
#define SYS_PORT_A_ANSEL        0x3B00
#define SYS_PORT_A_TRIS         0xFFE9
#define SYS_PORT_A_LAT          0x0010
#define SYS_PORT_A_ODC          0x0000
#define SYS_PORT_A_CNPU         0x0000
#define SYS_PORT_A_CNPD         0x0000
#define SYS_PORT_A_CNEN         0x0000

#define SYS_PORT_B_ANSEL        0x1008
#define SYS_PORT_B_TRIS         0x91DF
#define SYS_PORT_B_LAT          0x0000
#define SYS_PORT_B_ODC          0x0000
#define SYS_PORT_B_CNPU         0x0000
#define SYS_PORT_B_CNPD         0x0000
#define SYS_PORT_B_CNEN         0x0000

#define SYS_PORT_C_ANSEL        0x0FE1
#define SYS_PORT_C_TRIS         0x7FFF
#define SYS_PORT_C_LAT          0x0000
#define SYS_PORT_C_ODC          0x0000
#define SYS_PORT_C_CNPU         0x0000
#define SYS_PORT_C_CNPD         0x0000
#define SYS_PORT_C_CNEN         0x2000

#define SYS_PORT_D_ANSEL        0xC100
#define SYS_PORT_D_TRIS         0xDFFB
#define SYS_PORT_D_LAT          0x0000
#define SYS_PORT_D_ODC          0x0000
#define SYS_PORT_D_CNPU         0x0000
#define SYS_PORT_D_CNPD         0x0000
#define SYS_PORT_D_CNEN         0x0400

#define SYS_PORT_E_ANSEL        0xFC00
#define SYS_PORT_E_TRIS         0xFDFF
#define SYS_PORT_E_LAT          0x0000
#define SYS_PORT_E_ODC          0x0000
#define SYS_PORT_E_CNPU         0x0000
#define SYS_PORT_E_CNPD         0x0000
#define SYS_PORT_E_CNEN         0x0000

#define SYS_PORT_F_ANSEL        0xCEC0
#define SYS_PORT_F_TRIS         0xEEFF
#define SYS_PORT_F_LAT          0x0000
#define SYS_PORT_F_ODC          0x0000
#define SYS_PORT_F_CNPU         0x0000
#define SYS_PORT_F_CNPD         0x0000
#define SYS_PORT_F_CNEN         0x0000

#define SYS_PORT_G_ANSEL        0x8C3C
#define SYS_PORT_G_TRIS         0xDF7F
#define SYS_PORT_G_LAT          0x0000
#define SYS_PORT_G_ODC          0x0000
#define SYS_PORT_G_CNPU         0x0000
#define SYS_PORT_G_CNPD         0x0000
#define SYS_PORT_G_CNEN         0x0000

#define SYS_PORT_H_ANSEL        0x0050
#define SYS_PORT_H_TRIS         0xB1DB
#define SYS_PORT_H_LAT          0x0000
#define SYS_PORT_H_ODC          0x0000
#define SYS_PORT_H_CNPU         0x0000
#define SYS_PORT_H_CNPD         0x0000
#define SYS_PORT_H_CNEN         0x2000

#define SYS_PORT_J_ANSEL        0x0000
#define SYS_PORT_J_TRIS         0x8B7F
#define SYS_PORT_J_LAT          0x0080
#define SYS_PORT_J_ODC          0x0000
#define SYS_PORT_J_CNPU         0x0000
#define SYS_PORT_J_CNPD         0x0000
#define SYS_PORT_J_CNEN         0x0000

#define SYS_PORT_K_ANSEL        0xFF00
#define SYS_PORT_K_TRIS         0xFFFF
#define SYS_PORT_K_LAT          0x0000
#define SYS_PORT_K_ODC          0x0000
#define SYS_PORT_K_CNPU         0x0000
#define SYS_PORT_K_CNPD         0x0000
#define SYS_PORT_K_CNEN         0x0000


/*** File System Service Configuration ***/

#define SYS_FS_MEDIA_NUMBER         	1

#define SYS_FS_VOLUME_NUMBER		1

#define SYS_FS_AUTOMOUNT_ENABLE		false
#define SYS_FS_MAX_FILES	    	1
#define SYS_FS_MAX_FILE_SYSTEM_TYPE 	1
#define SYS_FS_MEDIA_MAX_BLOCK_SIZE  	512
#define SYS_FS_MEDIA_MANAGER_BUFFER_SIZE 2048
#define SYS_FS_FILE_NAME_LEN 255
#define SYS_FS_CWD_STRING_LEN 1024


#define SYS_FS_MEDIA_TYPE_IDX0 				
#define SYS_FS_TYPE_IDX0 					










/*** Interrupt System Service Configuration ***/
#define SYS_INT                     true
/*** Timer System Service Configuration ***/
#define SYS_TMR_POWER_STATE             SYS_MODULE_POWER_RUN_FULL
#define SYS_TMR_DRIVER_INDEX            DRV_TMR_INDEX_0
#define SYS_TMR_MAX_CLIENT_OBJECTS      5
#define SYS_TMR_FREQUENCY               1000
#define SYS_TMR_FREQUENCY_TOLERANCE     10
#define SYS_TMR_UNIT_RESOLUTION         10000
#define SYS_TMR_CLIENT_TOLERANCE        10
#define SYS_TMR_INTERRUPT_NOTIFICATION  false

// *****************************************************************************
// *****************************************************************************
// Section: Driver Configuration
// *****************************************************************************
// *****************************************************************************

/*** NVM Driver Configuration ***/
#define DRV_NVM_INSTANCES_NUMBER     	1
#define DRV_NVM_CLIENTS_NUMBER        	1
#define DRV_NVM_BUFFER_OBJECT_NUMBER  	5
#define DRV_NVM_INTERRUPT_MODE        	true
#define DRV_NVM_INTERRUPT_SOURCE      	INT_SOURCE_FLASH_CONTROL

#define DRV_NVM_MEDIA_SIZE              32
#define DRV_NVM_MEDIA_START_ADDRESS     0x9D010000

#define DRV_NVM_ERASE_WRITE_ENABLE


#define DRV_NVM_SYS_FS_REGISTER



/*** SPI Driver Configuration ***/
#define DRV_SPI_NUMBER_OF_MODULES		6
/*** Driver Compilation and static configuration options. ***/
/*** Select SPI compilation units.***/
#define DRV_SPI_POLLED 				1
#define DRV_SPI_ISR 				0
#define DRV_SPI_MASTER 				1
#define DRV_SPI_SLAVE 				0
#define DRV_SPI_RM 					0
#define DRV_SPI_EBM 				1
#define DRV_SPI_8BIT 				1
#define DRV_SPI_16BIT 				1
#define DRV_SPI_32BIT 				0
#define DRV_SPI_DMA 				0

/*** SPI Driver Static Allocation Options ***/
#define DRV_SPI_INSTANCES_NUMBER 		1
#define DRV_SPI_CLIENTS_NUMBER 			1
#define DRV_SPI_ELEMENTS_PER_QUEUE 		10
/* SPI Driver Instance 0 Configuration */
#define DRV_SPI_SPI_ID_IDX0 				SPI_ID_1
#define DRV_SPI_TASK_MODE_IDX0 				DRV_SPI_TASK_MODE_POLLED
#define DRV_SPI_SPI_MODE_IDX0				DRV_SPI_MODE_MASTER
#define DRV_SPI_ALLOW_IDLE_RUN_IDX0			false
#define DRV_SPI_SPI_PROTOCOL_TYPE_IDX0 		DRV_SPI_PROTOCOL_TYPE_FRAMED
#define DRV_SPI_FRAME_SYNC_PULSE_IDX0 		SPI_FRAME_SYNC_PULSE_ON_EVERY_DATA_CHARACTER
#define DRV_SPI_FRAME_PULSE_POLARITY_IDX0 	SPI_FRAME_PULSE_POLARITY_ACTIVE_LOW
#define DRV_SPI_FRAME_PULSE_DIRECTION_IDX0 	SPI_FRAME_PULSE_DIRECTION_OUTPUT
#define DRV_SPI_FRAME_PULSE_EDGE_IDX0 		SPI_FRAME_PULSE_EDGE_PRECEDES_FIRST_BIT_CLOCK
#define DRV_SPI_FRAME_PULSE_WIDTH_IDX0 		SPI_FRAME_PULSE_WIDTH_ONE_WORD_LENGTH
#define DRV_SPI_COMM_WIDTH_IDX0 			SPI_COMMUNICATION_WIDTH_8BITS
#define DRV_SPI_CLOCK_SOURCE_IDX0 		    SPI_BAUD_RATE_PBCLK_CLOCK
#define DRV_SPI_SPI_CLOCK_IDX0 				CLK_BUS_PERIPHERAL_2
#define DRV_SPI_BAUD_RATE_IDX0 				1000000
#define DRV_SPI_BUFFER_TYPE_IDX0 			DRV_SPI_BUFFER_TYPE_ENHANCED
#define DRV_SPI_CLOCK_MODE_IDX0 			DRV_SPI_CLOCK_MODE_IDLE_LOW_EDGE_FALL
#define DRV_SPI_INPUT_PHASE_IDX0 			SPI_INPUT_SAMPLING_PHASE_IN_MIDDLE
#define DRV_SPI_TRANSMIT_DUMMY_BYTE_VALUE_IDX0      0xFF

#define DRV_SPI_QUEUE_SIZE_IDX0 			10
#define DRV_SPI_RESERVED_JOB_IDX0 			1
/*** Timer Driver Configuration ***/
#define DRV_TMR_INTERRUPT_MODE             true

/*** Timer Driver 0 Configuration ***/
#define DRV_TMR_PERIPHERAL_ID_IDX0          TMR_ID_2
#define DRV_TMR_INTERRUPT_SOURCE_IDX0       INT_SOURCE_TIMER_2
#define DRV_TMR_INTERRUPT_VECTOR_IDX0       INT_VECTOR_T2
#define DRV_TMR_ISR_VECTOR_IDX0             _TIMER_2_VECTOR
#define DRV_TMR_INTERRUPT_PRIORITY_IDX0     INT_PRIORITY_LEVEL4
#define DRV_TMR_INTERRUPT_SUB_PRIORITY_IDX0 INT_SUBPRIORITY_LEVEL0
#define DRV_TMR_CLOCK_SOURCE_IDX0           DRV_TMR_CLKSOURCE_INTERNAL
#define DRV_TMR_PRESCALE_IDX0               TMR_PRESCALE_VALUE_8
#define DRV_TMR_OPERATION_MODE_IDX0         DRV_TMR_OPERATION_MODE_16_BIT
#define DRV_TMR_ASYNC_WRITE_ENABLE_IDX0     false
#define DRV_TMR_POWER_STATE_IDX0            

#define DRV_TMR_PERIPHERAL_ID_IDX1          TMR_ID_7
#define DRV_TMR_INTERRUPT_SOURCE_IDX1       INT_SOURCE_TIMER_7
#define DRV_TMR_INTERRUPT_VECTOR_IDX1       INT_VECTOR_T7
#define DRV_TMR_ISR_VECTOR_IDX1             _TIMER_7_VECTOR
#define DRV_TMR_INTERRUPT_PRIORITY_IDX1     INT_PRIORITY_LEVEL3
#define DRV_TMR_INTERRUPT_SUB_PRIORITY_IDX1 INT_SUBPRIORITY_LEVEL0
#define DRV_TMR_CLOCK_SOURCE_IDX1           DRV_TMR_CLKSOURCE_INTERNAL
#define DRV_TMR_PRESCALE_IDX1               TMR_PRESCALE_VALUE_16
#define DRV_TMR_OPERATION_MODE_IDX1         DRV_TMR_OPERATION_MODE_16_BIT

#define DRV_TMR_ASYNC_WRITE_ENABLE_IDX1     false
#define DRV_TMR_POWER_STATE_IDX1            
/*** Timer Driver 2 Configuration ***/
#define DRV_TMR_PERIPHERAL_ID_IDX2          TMR_ID_6
#define DRV_TMR_INTERRUPT_SOURCE_IDX2       INT_SOURCE_TIMER_6
#define DRV_TMR_INTERRUPT_VECTOR_IDX2       INT_VECTOR_T6
#define DRV_TMR_ISR_VECTOR_IDX2             _TIMER_6_VECTOR
#define DRV_TMR_INTERRUPT_PRIORITY_IDX2     INT_PRIORITY_LEVEL1
#define DRV_TMR_INTERRUPT_SUB_PRIORITY_IDX2 INT_SUBPRIORITY_LEVEL0
#define DRV_TMR_CLOCK_SOURCE_IDX2           DRV_TMR_CLKSOURCE_INTERNAL
#define DRV_TMR_PRESCALE_IDX2               TMR_PRESCALE_VALUE_16
#define DRV_TMR_OPERATION_MODE_IDX2         DRV_TMR_OPERATION_MODE_16_BIT
#define DRV_TMR_ASYNC_WRITE_ENABLE_IDX2     false
#define DRV_TMR_POWER_STATE_IDX2            
/*** Timer Driver 3 Configuration ***/
#define DRV_TMR_PERIPHERAL_ID_IDX3          TMR_ID_1
#define DRV_TMR_INTERRUPT_SOURCE_IDX3       INT_SOURCE_TIMER_1
#define DRV_TMR_INTERRUPT_VECTOR_IDX3       INT_VECTOR_T1
#define DRV_TMR_ISR_VECTOR_IDX3             _TIMER_1_VECTOR
#define DRV_TMR_INTERRUPT_PRIORITY_IDX3     INT_PRIORITY_LEVEL2
#define DRV_TMR_INTERRUPT_SUB_PRIORITY_IDX3 INT_SUBPRIORITY_LEVEL0
#define DRV_TMR_CLOCK_SOURCE_IDX3           DRV_TMR_CLKSOURCE_INTERNAL
#define DRV_TMR_PRESCALE_IDX3               TMR_PRESCALE_VALUE_256
#define DRV_TMR_OPERATION_MODE_IDX3         DRV_TMR_OPERATION_MODE_16_BIT
#define DRV_TMR_ASYNC_WRITE_ENABLE_IDX3     false
#define DRV_TMR_POWER_STATE_IDX3            
 
/*** Timer Driver 5 Configuration ***/
#define DRV_TMR_PERIPHERAL_ID_IDX5          TMR_ID_8
#define DRV_TMR_INTERRUPT_SOURCE_IDX5       INT_SOURCE_TIMER_8
#define DRV_TMR_INTERRUPT_VECTOR_IDX5       INT_VECTOR_T8
#define DRV_TMR_ISR_VECTOR_IDX5             _TIMER_8_VECTOR
#define DRV_TMR_INTERRUPT_PRIORITY_IDX5     INT_PRIORITY_LEVEL2
#define DRV_TMR_INTERRUPT_SUB_PRIORITY_IDX5 INT_SUBPRIORITY_LEVEL0
#define DRV_TMR_CLOCK_SOURCE_IDX5           DRV_TMR_CLKSOURCE_INTERNAL
#define DRV_TMR_PRESCALE_IDX5               TMR_PRESCALE_VALUE_1
#define DRV_TMR_OPERATION_MODE_IDX5         DRV_TMR_OPERATION_MODE_16_BIT
#define DRV_TMR_ASYNC_WRITE_ENABLE_IDX5     false
#define DRV_TMR_POWER_STATE_IDX5            


 // *****************************************************************************
/* USART Driver Configuration Options
*/
#define DRV_USART_INSTANCES_NUMBER                  2
#define DRV_USART_CLIENTS_NUMBER                    2
#define DRV_USART_INTERRUPT_MODE                    false
#define DRV_USART_BYTE_MODEL_SUPPORT                true
#define DRV_USART_READ_WRITE_MODEL_SUPPORT          false
#define DRV_USART_BUFFER_QUEUE_SUPPORT              false
 
 // *****************************************************************************
// *****************************************************************************
// Section: Middleware & Other Library Configuration
// *****************************************************************************
// *****************************************************************************

/*** USB Driver Configuration ***/


/* Enables Device Support */
#define DRV_USBHS_DEVICE_SUPPORT      true

/* Disable Host Support */
#define DRV_USBHS_HOST_SUPPORT      false

/* Maximum USB driver instances */
#define DRV_USBHS_INSTANCES_NUMBER    1

/* Interrupt mode enabled */
#define DRV_USBHS_INTERRUPT_MODE      true


/* Number of Endpoints used */
#define DRV_USBHS_ENDPOINTS_NUMBER    2




/*** USB Device Stack Configuration ***/










/* The USB Device Layer will not initialize the USB Driver */
#define USB_DEVICE_DRIVER_INITIALIZE_EXPLICIT

/* Maximum device layer instances */
#define USB_DEVICE_INSTANCES_NUMBER     1

/* EP0 size in bytes */
#define USB_DEVICE_EP0_BUFFER_SIZE      64









/* Maximum instances of HID function driver */
#define USB_DEVICE_HID_INSTANCES_NUMBER     1










/* HID Transfer Queue Size for both read and
   write. Applicable to all instances of the
   function driver */
#define USB_DEVICE_HID_QUEUE_DEPTH_COMBINED 2





// *****************************************************************************
// *****************************************************************************
// Section: Application Configuration
// *****************************************************************************
// *****************************************************************************
/*** Application Defined Pins ***/

/*** Functions for LED1 pin ***/
#define LED1Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_J, PORTS_BIT_POS_12)
#define LED1On() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_J, PORTS_BIT_POS_12)
#define LED1Off() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_J, PORTS_BIT_POS_12)
#define LED1StateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_J, PORTS_BIT_POS_12)
#define LED1StateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_J, PORTS_BIT_POS_12, Value)

/*** Functions for LED2 pin ***/
#define LED2Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_J, PORTS_BIT_POS_10)
#define LED2On() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_J, PORTS_BIT_POS_10)
#define LED2Off() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_J, PORTS_BIT_POS_10)
#define LED2StateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_J, PORTS_BIT_POS_10)
#define LED2StateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_J, PORTS_BIT_POS_10, Value)

/*** Functions for RLY_WL_MON pin ***/
#define RLY_WL_MONToggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_7)
#define RLY_WL_MONOn() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_7)
#define RLY_WL_MONOff() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_7)
#define RLY_WL_MONStateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_7)
#define RLY_WL_MONStateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_7, Value)

/*** Functions for STATUS_LED_ pin ***/
#define STATUS_LED_Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_9)
#define STATUS_LED_On() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_9)
#define STATUS_LED_Off() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_9)
#define STATUS_LED_StateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_9)
#define STATUS_LED_StateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_9, Value)

/*** Functions for USB_RST_ pin ***/
#define USB_RST_Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_15)
#define USB_RST_On() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_15)
#define USB_RST_Off() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_15)
#define USB_RST_StateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_15)
#define USB_RST_StateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_15, Value)

/*** Functions for RLY_HI_SIDE_MON_ pin ***/
#define RLY_HI_SIDE_MON_Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_9)
#define RLY_HI_SIDE_MON_On() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_9)
#define RLY_HI_SIDE_MON_Off() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_9)
#define RLY_HI_SIDE_MON_StateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_9)
#define RLY_HI_SIDE_MON_StateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_9, Value)

/*** Functions for RLY_GPT_ pin ***/
#define RLY_GPT_Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_10)
#define RLY_GPT_On() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_10)
#define RLY_GPT_Off() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_10)
#define RLY_GPT_StateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_10)
#define RLY_GPT_StateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_10, Value)

/*** Functions for TPAN1 pin ***/
#define TPAN1Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_11)
#define TPAN1On() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_11)
#define TPAN1Off() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_11)
#define TPAN1StateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_11)
#define TPAN1StateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_11, Value)

/*** Functions for TPAN2 pin ***/
#define TPAN2Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_2)
#define TPAN2On() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_2)
#define TPAN2Off() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_2)
#define TPAN2StateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_2)
#define TPAN2StateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_2, Value)

/*** Functions for GAIN_RESET_ pin ***/
#define GAIN_RESET_Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_2)
#define GAIN_RESET_On() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_2)
#define GAIN_RESET_Off() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_2)
#define GAIN_RESET_StateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_2)
#define GAIN_RESET_StateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_2, Value)

/*** Functions for RLY_GAM_CCL_ pin ***/
#define RLY_GAM_CCL_Toggle() PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_13)
#define RLY_GAM_CCL_On() PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_13)
#define RLY_GAM_CCL_Off() PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_13)
#define RLY_GAM_CCL_StateGet() PLIB_PORTS_PinGetLatched(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_13)
#define RLY_GAM_CCL_StateSet(Value) PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_13, Value)

/*** Functions for STATUS_SW_ pin ***/
#define STATUS_SW_StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_8)

/*** Functions for DRUM1_SW pin ***/
#define DRUM1_SWStateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_2)

/*** Functions for SAFE_SW pin ***/
#define SAFE_SWStateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_1)

/*** Functions for DRUM2_SW pin ***/
#define DRUM2_SWStateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_0)

/*** Functions for HSI_SW pin ***/
#define HSI_SWStateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_8)

/*** Functions for GPT_SW_ pin ***/
#define GPT_SW_StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_K, PORTS_BIT_POS_1)

/*** Functions for GAM_CCL_SW_ pin ***/
#define GAM_CCL_SW_StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_K, PORTS_BIT_POS_2)

/*** Functions for GPT_DATA pin ***/
#define GPT_DATAStateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_10)

/*** Functions for GPT_SYNC pin ***/
#define GPT_SYNCStateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_13)

/*** Functions for GAMMA_PULSE_ pin ***/
#define GAMMA_PULSE_StateGet() PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_13)
    
#define GPT_SYNC_CN_PORT_CHANNEL         PORT_CHANNEL_H
#define GPT_SYNC_CN_PORT_BIT             PORTS_BIT_POS_13   
#define GPT_SYNC_CN_PORT_INTERRUPT       INT_SOURCE_CHANGE_NOTICE_H 
    
#define GPT_DATA_CN_PORT_CHANNEL         PORT_CHANNEL_D
#define GPT_DATA_CN_PORT_BIT             PORTS_BIT_POS_10   
#define GPT_DATA_CN_PORT_INTERRUPT       INT_SOURCE_CHANGE_NOTICE_D    
    
#define GAMMA_PULSE_CN_PORT_CHANNEL         PORT_CHANNEL_C
#define GAMMA_PULSE_CN_PORT_BIT             PORTS_BIT_POS_13
#define GAMMA_PULSE_CN_PORT_INTERRUPT       INT_SOURCE_CHANGE_NOTICE_C     
    
/*** Application Instance 0 Configuration ***/
  
#define APP_MAKE_BUFFER_DMA_READY __attribute__ ((coherent, aligned(16)))    

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // _SYSTEM_CONFIG_H
/*******************************************************************************
 End of File
*/
