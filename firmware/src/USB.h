/**************************************************************************************/
/** \file USB.h

  Company:
    Hunting Titan

  File Name:
    USB.h

  Summary:
    This header file provides prototypes and definitions for USB.c.

  Description:
    This header file provides function prototypes and data type definitions for
    USB.c.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "USB_TASKS" definition).  Both
    are defined here for convenience.
 */
/**************************************************************************************/

#ifndef USB_H                                                                           /* Guard against multiple inclusion */
#define USB_H

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

/**************************************************************************************/
/**************************************************************************************/
/* Section: Data Types                                                                */
/**************************************************************************************/
/**************************************************************************************/

/**************************************************************************************/
/* USB states

  Summary:
    USB states enumeration

  Description:
    This enumeration defines the valid USB states.  These states
    determine the behavior of the USB state machine at various times.
*/    

typedef enum
{
    
    USB_STATE_INIT=0,                                                                   /*!< USB's state machine's initial state. */            
    USB_STATE_OPEN,                                                                     /*!< Open the USB port if necessary.*/    
    USB_STATE_WAIT_FOR_CONFIGURATION,                                                   /*!< Wait for device configuration.*/  
    USB_STATE_READ,                                                                     /*!< Read the data sent from the host.*/           
    USB_STATE_WAIT,                                                                     /*!< Wait fora command to be processed.*/            
    USB_STATE_WRITE,                                                                    /*!< Send the command response data to the host.*/            
    USB_STATE_INITIATE_READ,                                                            /*!< Configure device to wait for new data from host.*/
    USB_STATE_ERROR                                                                     /*!< Error state. Currently nothing is done.*/
                                                                                         

} USB_STATES;


/**************************************************************************************/
/* USB_DATA

  Summary:
    Holds USB_DATA used for the USB tasks.

  Description:
    Holds USB_DATA used for the USB tasks. The state machine and variables
    used to control USB functions are stored here.

  Remarks:
    None
 */

typedef struct
{ 
    USB_STATES state;                                                                   /*!< The USB tasks current state.*/    
    USB_DEVICE_HANDLE usbDevHandle;                                                     /*!< Device layer handle returned by device layer open function.*/     
    bool deviceIsConfigured;                                                            /*!< Track device configuration.*/    
    uint8_t configValue;                                                                /*!< Configuration value.*/    
    USB_SPEED speed;                                                                    /*!< speed. */
    
    bool epDataWritePending;                                                            /*!< endpoint data sent */    
    bool epDataReadPending;                                                             /*!< endpoint data received.*/    
    USB_DEVICE_TRANSFER_HANDLE writeTranferHandle;                                      /* Write transfer handle.*/    
    USB_DEVICE_TRANSFER_HANDLE readTranferHandle;                                       /* Read transfer handle.*/
    
    USB_ENDPOINT_ADDRESS endpointTx;                                                    /*!< The transmit endpoint address.*/    
    USB_ENDPOINT_ADDRESS endpointRx;                                                    /*!< The receive endpoint address.*/
   
    uint8_t altSetting;                                                                 /*!< Tracks the alternate setting.*/    
    uint8_t byte_count;                                                                 /*!< the number of bytes sent or received.*/
    
    bool attached;                                                                      /*!< Flag to indicate that the USB cable is attached.*/
    bool tick;                                                                          /*!< Timer tick for resetting the USB connection.*/   
    

} USB_DATA;

extern USB_DATA USB;

/**************************************************************************************/
/**************************************************************************************/
/* Section: Local Functions                                                           */
/**************************************************************************************/
/**************************************************************************************/

/*!************************************************************************************* 
  Function:
    static void usb_watchdog(void) 

  Summary:
    This function initializes the wire-line communication power supply parameters.

  Description:
    This function initializes the wire-line communication power supply parameters.  
    Initial limits, flags and constants are set here.
    
  Precondition:
    None.

  Parameters:
    None.

  Returns
    None.
 
  Remarks
    None.
   
   Example:
    usb_watchdog()    
 */
static void usb_watchdog(void);
	
/**************************************************************************************/
/**************************************************************************************/
/*       State Machine Functions                                                      */
/**************************************************************************************/
/**************************************************************************************/

/*!*************************************************************************************
  Function:
    void USB_Tasks(void)

  Summary:
    USB_Tasks function

  Description:
    This routine is the USB Tasks function.  It defines the USB's state machine and 
    core logic. This machine controls the USB operation and sets flags indicating 
    new values are available. 

  Precondition:
    The system ("SYS_Initialize") and application ("APP_Initialize")initialization 
    should be called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Example:
    USB_Tasks()
  
  Remarks:
    This routine must be called from the APP_Tasks() routine.
 */

void USB_Tasks ( void );
   
#ifdef __cplusplus                                                                      /* Provide C++ Compatibility */
}
#endif

#endif                                                                                  /* USB_H */

/***************************************************************************************
 End of File
 */
