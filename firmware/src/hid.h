/**************************************************************************************/
/** \file hid.h

  Company:
    Hunting Titan

  File Name:
    hid.h

  Summary:
    This header file provides prototypes and definitions for the USB HID tasks and
    functions.

  Description:
    This header file provides prototypes and definitions for the USB HID tasks and
    functions. Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the USB functions) This is taken from the HID basic demo program and 
    modified for use here.  Data is sent to the host every 10mS. No commands or data 
    is received from the host.
***************************************************************************************/

#ifndef HID_H                                                                           /* Guard against multiple inclusion.*/
#define HID_H

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
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"
#include "usb/usb_chapter_9.h"
#include "usb/usb_device.h"

/**************************************************************************************/
/**************************************************************************************/
/* Section: Data Types                                                                */
/**************************************************************************************/
/**************************************************************************************/

/**************************************************************************************/
/* HID states

  Summary:
    HID states enumeration

  Description:
    This enumeration defines the valid HID states.  These states
    determine the behavior of the HID state machine at various times.
*/   

typedef enum
{    
    HID_STATE_INIT,                                                                     /*!< HID state machine is initializing.*/    
    HID_STATE_WAIT_FOR_CONFIGURATION,                                                   /*!< HID is waiting for configuration from host.*/    
    HID_STATE_RECEIVE,                                                                /*!< Main HID tasks.*/  
    HID_STATE_WAIT,
    HID_STATE_TRANSMIT,
    HID_STATE_ERROR                                                                     /*!< HID task is in an error state.*/
            
} HID_STATES;


/**************************************************************************************/
/* APP_DATA

  Summary:
    Holds APP_DATA used for the HID functions.

  Description:
    Holds APP_DATA used for the HID functions. The variables used to control data
    transfer via a USB HID connection.  Data is only transferred to the host.  No 
    commands or data is received from the host.

  Remarks:
    None
 */

typedef struct
{
    
    HID_STATES state;                                                                   /*!< The HID tasks current state.*/      
    USB_DEVICE_HANDLE  usbDevHandle;                                                    /*!< Device layer handle returned by device layer open function.*/    
    uint8_t * receiveDataBuffer;                                                        /*!< Receive data buffer.*/    
    uint8_t * transmitDataBuffer;                                                       /*!< Transmit data buffer.*/    
    bool deviceConfigured;                                                              /*!< Flag indicating the device is configured.*/    
    USB_DEVICE_HID_TRANSFER_HANDLE txTransferHandle;                                    /*!< Send report transfer handle.*/    
    USB_DEVICE_HID_TRANSFER_HANDLE rxTransferHandle;                                    /*!< Receive report transfer handle.*/    
    uint8_t configurationValue;                                                         /*!< Configuration value selected by the host.*/  
    bool hidDataReceived;                                                               /*!< HID data received flag.*/    
    bool hidDataTransmitted;                                                            /*!< HID data transmitted flag.*/     
    uint8_t idleRate;                                                                   /*!< USB HID current Idle.*/
    uint8_t byte_count;
    bool timer_tick;
    
    
//
} APP_DATA;

//extern APP_DATA appData;	
/**************************************************************************************/
/**************************************************************************************/
/*   HID Initialization and State Machine Functions                                   */
/**************************************************************************************/
/**************************************************************************************/

/*******************************************************************************
  Function:
    void HID_Initialize ( void )

  Summary:
     USB HID initialization routine.

  Description:
    USB HID initialization routine.  This function initializes the HID task variables 
    and state machine.      

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    HID_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void HID_Initialize ( void );


/*!*************************************************************************************
  Function:
    void HID_Tasks ( void )

  Summary:
    HID tasks function

  Description:
    This routine is the HID tasks function.  It defines the HID's state machine and 
    core logic. This machine initializes opens a USB handle, waits for configuration
    from the host and sends data to the host when a timer flag is set.  No data is 
    read from the host.

  Precondition:
    The system ("SYS_Initialize") and application ("APP_Initialize")initialization 
    should be called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Example:
    HID_Tasks()
  
  Remarks:
    This routine must be called from the APP_Tasks() routine.
 */

void HID_Tasks ( void );

extern const USB_DEVICE_FUNCTION_REGISTRATION_TABLE funcRegistrationTable[1];           /*!< Assign the USB function to function 1.*/
extern const USB_DEVICE_MASTER_DESCRIPTOR usbMasterDescriptor;                          /*!< Assign the USB master descriptor.*/

#ifdef __cplusplus                                                                      /* Provide C++ Compatibility.*/
}
#endif

#endif                                                                                  /*HID_H */

/***************************************************************************************
 End of File
 */

