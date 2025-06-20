/**************************************************************************************/
/** \file hid.c
  
  Company:
 Hunting Titan
  
  File Name:
    hid.c

  Summary:
    This file contains the source code for the USB HID tasks and functions.

  Description:
    This file contains the source code for the USB HID tasks and functions. It 
    implements the logic of the HID's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  This code is taken from the "hid_basic" example
    project in Harmony v2.06.  It has been modified for use here. These functions work 
    with the host to transfer data to the host in 10mS increments.  This is controlled 
    in timers.c.  While the system is configured to received data, no data or commands 
    are received from the host. The task is configured to assume the data received 
    is 0X81H.  This allows for proper operation of the HID functions.  Callback and 
    event handler functions monitor the USB for changes and configuration data from 
    the host.
 **************************************************************************************/


/**************************************************************************************/
/**************************************************************************************/
/* Section: Included Files                                                            */
/**************************************************************************************/
/**************************************************************************************/

#include "system_definitions.h"
#include "hid.h"
#include "commands.h"
#include "commmodule.h"
#include "fifo.h"
/**************************************************************************************/
/**************************************************************************************/
/* Section: Structure Data and Local Variables                                        */
/**************************************************************************************/
/**************************************************************************************/

uint8_t receiveDataBuffer[64] APP_MAKE_BUFFER_DMA_READY;                                /*!< Receive data buffer.*/
uint8_t  transmitDataBuffer[64] APP_MAKE_BUFFER_DMA_READY;                              /*!< Transmit data buffer.*/

/**************************************************************************************/
/* appData Data

  Summary:
    These structures hold the required states and variables to perform the HID tasks.

  Description:
    These structures hold the required states and variables to perform the HID tasks. 
    These are here to link these structures for use by the local functions.
 
  Remarks: 
    These are defined in hid.h
*/

APP_DATA appData;

/**************************************************************************************/ 
/**************************************************************************************/ 
/* Section: USB HID Callback Functions                                                */ 
/**************************************************************************************/ 
/**************************************************************************************/

/*!*************************************************************************************
  Function:
   USB_DEVICE_HID_EVENT_RESPONSE APP_USBDeviceHIDEventHandler 

  Summary:
    Function to track HID events.

  Description:
    Function to track HID events. Events such as when reports are sent and received,
    and when the system is in idle.  
    
  Precondition:
    None.

  Parameters:
    None.

  Returns
    None.
 
  Remarks
    None.
   
   Example:
    USB_DEVICE_HID_EVENT_RESPONSE APP_USBDeviceHIDEventHandler
*/  

USB_DEVICE_HID_EVENT_RESPONSE APP_USBDeviceHIDEventHandler
(
    USB_DEVICE_HID_INDEX iHID,
    USB_DEVICE_HID_EVENT event,
    void * eventData,
    uintptr_t userData
)
{
    USB_DEVICE_HID_EVENT_DATA_REPORT_SENT * reportSent;
    USB_DEVICE_HID_EVENT_DATA_REPORT_RECEIVED * reportReceived;

    
    switch (event)                                                                      /* Check type of event.*/
    {
        case USB_DEVICE_HID_EVENT_REPORT_SENT:
        {
                                                                                        /* The eventData parameter will be USB_DEVICE_HID_EVENT_REPORT_SENT
                                                                                         * pointer type containing details about the report that was
                                                                                         * sent.*/
            reportSent = (USB_DEVICE_HID_EVENT_DATA_REPORT_SENT *) eventData;           /* Check to see if a report was sent.*/
            if(reportSent->handle == appData.txTransferHandle )                         /* If a report was sent,*/
            {               
                appData.hidDataTransmitted = true;                                      /* Set the flag to true.*/
            }
        }    
        break;

        case USB_DEVICE_HID_EVENT_REPORT_RECEIVED:
        {
                                                                                        /* The eventData parameter will be USB_DEVICE_HID_EVENT_REPORT_RECEIVED
                                                                                         * pointer type containing details about the report that was
                                                                                         * received.  This is not used in this application.*/

            reportReceived = (USB_DEVICE_HID_EVENT_DATA_REPORT_RECEIVED *) eventData;   /* Check to see if a report was received.*/
            if(reportReceived->handle == appData.rxTransferHandle )                     /* If a report was received,*/                     
            {                
                appData.hidDataReceived = true;                                         /* Set the flag to true. This flag is set true in timers.c. This is checked*/ 
            }

        }  
        break;

        case USB_DEVICE_HID_EVENT_SET_IDLE:
        {
                                                                                        /* For now we just accept this request as is. We acknowledge
                                                                                         * this request using the USB_DEVICE_HID_ControlStatus()
                                                                                         * function with a USB_DEVICE_CONTROL_STATUS_OK flag.*/

            USB_DEVICE_ControlStatus(appData.usbDevHandle, USB_DEVICE_CONTROL_STATUS_OK);

            
            appData.idleRate =                                                          /* Save Idle rate received from Host.*/
                    ((USB_DEVICE_HID_EVENT_DATA_SET_IDLE*)eventData)->duration;
        }    
        break;

        case USB_DEVICE_HID_EVENT_GET_IDLE:
        {            
            USB_DEVICE_ControlSend(appData.usbDevHandle, & (appData.idleRate),1);       /* Host is requesting for Idle rate. Now send the Idle rate.*/

                                                                                        /* On successfully receiving Idle rate, the Host would acknowledge back with a
                                                                                           Zero Length packet. The HID function driver returns an event
                                                                                           USB_DEVICE_HID_EVENT_CONTROL_TRANSFER_DATA_SENT to the application upon
                                                                                           receiving this Zero Length packet from Host.
                                                                                           USB_DEVICE_HID_EVENT_CONTROL_TRANSFER_DATA_SENT event indicates this control transfer
                                                                                           event is complete.*/
        }
        break;
        
        default:
        {
            // Nothing to do.
        }    
        break;
    }
    return USB_DEVICE_HID_EVENT_RESPONSE_NONE;
}

/*!*************************************************************************************
  Function:
   void APP_USBDeviceEventHandler
                        (USB_DEVICE_EVENT event, void * eventData, uintptr_t context)

  Summary:
    Function to track USB device events.

  Description:
    Function to track USB device events. Events such as when USB power is detected and 
    removed and when the host has configured the HID connection.  
    
  Precondition:
    None.

  Parameters:
    None.

  Returns
    None.
 
  Remarks
    None.
   
   Example:
    void APP_USBDeviceEventHandler
                        (USB_DEVICE_EVENT event, void * eventData, uintptr_t context)
*/  

void APP_USBDeviceEventHandler
                        (USB_DEVICE_EVENT event, void * eventData, uintptr_t context)
{
    switch(event)
    {
        case USB_DEVICE_EVENT_RESET:
        case USB_DEVICE_EVENT_DECONFIGURED:
        {
                                                                                        /* Host has de-configured the device or a bus reset has happened.
                                                                                         * Device layer is going to de-initialize all function drivers.
                                                                                         * Hence close handles to all function drivers (Only if they are
                                                                                         * opened previously.*/

            appData.deviceConfigured = false;                                           /* Reset flag.*/
            appData.state = HID_STATE_WAIT_FOR_CONFIGURATION;                           /* Set the main HID task to wait for configuration.*/
        }
        break;

        case USB_DEVICE_EVENT_CONFIGURED:
        {    
            appData.deviceConfigured = true;                                            /* Set the flag indicating device is configured.*/            
            appData.configurationValue =                                                /* Save the other details for later use.*/
                    ((USB_DEVICE_EVENT_DATA_CONFIGURED*)eventData)->configurationValue; /* Not used currently.*/
            
            USB_DEVICE_HID_EventHandlerSet(USB_DEVICE_HID_INDEX_0,                      /* Register application HID event handler.*/
                                    APP_USBDeviceHIDEventHandler, (uintptr_t)&appData);
        }
        break;

        case USB_DEVICE_EVENT_SUSPENDED:
        {
                                                                                        /* This event is not used here.*/
        }
        break;

        case USB_DEVICE_EVENT_POWER_DETECTED:
        {
            USB_DEVICE_Attach (appData.usbDevHandle);                                   /* VBUS was detected. We can attach the device.*/
        }
        break;

        case USB_DEVICE_EVENT_POWER_REMOVED:
        {            
            USB_DEVICE_Detach(appData.usbDevHandle);                                    /* VBUS is not available. Detach the USB.*/
        }
        break;
        
        case USB_DEVICE_EVENT_RESUMED:                                                  /* These events are not used here.*/
        case USB_DEVICE_EVENT_ERROR:
        default:
        {
            
        }
        break;
    }
}

/**************************************************************************************/
/**************************************************************************************/
/* Section: HID Initialization and State Machine Functions                            */
/**************************************************************************************/
/**************************************************************************************/

/*************************************************************************************** 
  Function:
    void HID_Initialize ( void )

  Summary:
   This routine is the HID_Initialize function.  It initializes the (HID) state machine 
    and core logic.

  Remarks:
    Refer to the hid.h interface header for function usage details.
 */

void HID_Initialize ( void )
{    
    appData.state = HID_STATE_INIT;                                                     /* Place the HID state machine in its initial state.*/
    
    appData.usbDevHandle = USB_DEVICE_HANDLE_INVALID;                                   /* Initialize variables.*/
    appData.deviceConfigured = false;
    appData.txTransferHandle = USB_DEVICE_HID_TRANSFER_HANDLE_INVALID;
    appData.rxTransferHandle = USB_DEVICE_HID_TRANSFER_HANDLE_INVALID;
    appData.hidDataReceived = false;
    appData.hidDataTransmitted = true;
    appData.receiveDataBuffer = &receiveDataBuffer[0];
    appData.transmitDataBuffer = &transmitDataBuffer[0];
    appData.timer_tick = false;
    USB_RST_On();                                                                       /* Set this line high so VBUS can be detected.*/
}


/*************************************************************************************** 
  Function:
    void HID_Tasks ( void )

  Summary:
   This routine is the HID_Tasks function.  It defines the (HID) state machine and
   core logic.

  Remarks:
    Refer to the hid.h interface header for function usage details.
 */

void HID_Tasks (void )
{ 
    switch(appData.state)
    {
        case HID_STATE_INIT:
        {            
            appData.usbDevHandle =                                                      /* Open the device layer.*/
                    USB_DEVICE_Open( USB_DEVICE_INDEX_0, DRV_IO_INTENT_READWRITE );

            if(appData.usbDevHandle != USB_DEVICE_HANDLE_INVALID)                       /* If the device has been opened,*/
            {               
                USB_DEVICE_EventHandlerSet(appData.usbDevHandle,                        /* Register a callback with device layer to get event*/
                        APP_USBDeviceEventHandler, 0);                                  /* notification (for end point 0).*/ 

                appData.state = HID_STATE_WAIT_FOR_CONFIGURATION;                       /* Move on to wait for the host to configure the USB.*/
            }
            else
            {
                                                                                        /* The Device Layer is not ready to be opened. We should try*/
                                                                                        /* again later.*/
            }
        }
        break;

        case HID_STATE_WAIT_FOR_CONFIGURATION:
        {
            if(appData.deviceConfigured == true)                                        /* If the USB is configured from the USB Device Event handler,*/
            {               
                appData.hidDataReceived = false;                                        /* Initialize the flags.*/                                     
                appData.hidDataTransmitted = true;
                appData.state = HID_STATE_RECEIVE;                                      /* Device is ready to run the main task.*/
                
                USB_DEVICE_HID_ReportReceive (USB_DEVICE_HID_INDEX_0,                   /* Place a new read request.*/
                        &appData.rxTransferHandle, appData.receiveDataBuffer, 64);
            }
        }
        break;

        case HID_STATE_RECEIVE:
        {
            if(!appData.deviceConfigured)                                               /* If the device is not configured,*/
            {               
                appData.state = HID_STATE_WAIT_FOR_CONFIGURATION;                       /* move on to wait for the device to be configured.*/
            }
            else if( appData.hidDataReceived )                                          /* This is used as a flag in timers.c to send data every 10mS.*/
            {
                                                                                        /* Look at the data the host sent, to see what
                                                                                         * kind of application specific command it sent.*/
//            usb_tick_count = 0U;                                                    /* Reset watchdog counter.*/
//                USB.tick = false;                                                       /* Reset the timer tick.*/
                if( appData.byte_count < CMD.cmd_size )                                     /* transfer the data to the RxFifo buffer.*/
                {
                    (void) Fifo_Put( &RX_FIFO, receiveDataBuffer[appData.byte_count] );    /* put the byte into the RxFifo for later analysis.*/
                    appData.byte_count = appData.byte_count + 1U;
                }
                else if (appData.byte_count == CMD.cmd_size)                                /* If we have received enough bytes,*/
                {
                    appData.byte_count = 0U;                                                /* reset the counter.*/ 
                    if( Fifo_Length( &RX_FIFO ) == CMD.cmd_size )                       /* If we have received enough bytes for a command,*/
                    {
                        COMM.state = COMM_STATE_VALIDATE;                               /* move on to see if it is a valid command in commmodule.c.*/
                    }
//                    appData.state = HID_STATE_WAIT;                                         /* move on to wait for the command to be processed.*/
                    appData.state = HID_STATE_TRANSMIT;
                }
                else
                {
                                                                                        /*MISRA compliance.*/
                }/* in the HID main task.*/
//                switch(appData.receiveDataBuffer[0])
//                {
//                    case 0x80:                                                          /* This case is not used.*/
//                    { 
//                        appData.hidDataReceived = false;                                /* Reset the flag.*/                        
//                        USB_DEVICE_HID_ReportReceive (USB_DEVICE_HID_INDEX_0,           /* Place a new read request. */
//                            &appData.rxTransferHandle, appData.receiveDataBuffer, 64 );
//                    }
//                    break;
//
//                    case 0x81:                                                          /* This case is always chosen from timers.c so*/
//                    {                                                                   /* data can be transmitted.*/
//                        if(appData.hidDataTransmitted == true)                          /* This is set true in USB Device Event Handler after*/
//                        {                                                               /* a transmission is completed.*/
//                            appData.hidDataTransmitted = false;                         /* Reset the flag.*/
//                            
//                            USB_DEVICE_HID_ReportSend (USB_DEVICE_HID_INDEX_0,          /* Prepare the USB module to send the data*/
//                                                    &appData.txTransferHandle,          /* packet to the host. The data packet is filled in report.c.*/
//                                                    appData.transmitDataBuffer, 64 );
//                            
//                            appData.hidDataReceived = false;                            /* Reset the flag.*/
//                            
//                            USB_DEVICE_HID_ReportReceive (USB_DEVICE_HID_INDEX_0,       /* Place a new read request.*/
//                                                    &appData.rxTransferHandle, 
//                                                    appData.receiveDataBuffer, 64 );
//                        }
            }    
//                break;

//                default:
//                {
//                    appData.hidDataReceived = false;                                /* Reset the flag.*/
//
//                    USB_DEVICE_HID_ReportReceive (USB_DEVICE_HID_INDEX_0,           /* Place a new read request.*/
//                        &appData.rxTransferHandle, appData.receiveDataBuffer, 64 );
//                }
//                break;
        }
        break;
//        }
//        break;
        
        case HID_STATE_WAIT:
        {
            
        }
        break;
        
        case HID_STATE_TRANSMIT:
        {
            if((appData.hidDataTransmitted == true) && 
                    (CMD.process_complete_flag == true) &&(appData.timer_tick == true)) /* This is set true in USB Device Event Handler after*/
            {                                                                           /* a transmission is completed.*/
                appData.hidDataTransmitted = false;                                     /* Reset the flag.*/
                appData.timer_tick = false;

                USB_DEVICE_HID_ReportSend (USB_DEVICE_HID_INDEX_0,                      /* Prepare the USB module to send the data*/
                                        &appData.txTransferHandle,                      /* packet to the host. The data packet is filled in report.c.*/
                                        appData.transmitDataBuffer, 64 );

                appData.hidDataReceived = false;                                        /* Reset the flag.*/

                USB_DEVICE_HID_ReportReceive (USB_DEVICE_HID_INDEX_0,                   /* Place a new read request.*/
                                        &appData.rxTransferHandle, 
                                        appData.receiveDataBuffer, 64 );
                
                appData.state = HID_STATE_RECEIVE;
            }
        }
        break;
        
        case HID_STATE_ERROR:
        {
            /*Comment.*/
        }
        break;
        
        default:
        {
            /*Comment.*/
            appData.hidDataReceived = false;                                            /* Reset the flag.*/
                        
            USB_DEVICE_HID_ReportReceive (USB_DEVICE_HID_INDEX_0,                       /* Place a new read request.*/
                &appData.rxTransferHandle, appData.receiveDataBuffer, 64 );
        }
        break;
    }
}
 

/***************************************************************************************
 End of File
 */

