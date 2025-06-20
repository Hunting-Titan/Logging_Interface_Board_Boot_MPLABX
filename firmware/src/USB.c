/**************************************************************************************/
/** \file USB.c
     
  Company:
    Hunting Titan
  
  File Name:
    USB.c

  Summary:
    This file contains the state machine code for the USB operation.

  Description:
    This file contains the state machine code for the USB operation.  It implements
    the logic of the USB's state machine and it may call API routines of other
    MPLAB Harmony modules in the system, such as drivers, system services, and
    middleware.  Once configured this machine sends and receives data using a 
    WinUSB connection. The states are configured so that other system tasks can be 
    maintained while these tasks are waiting for an event to occur.     
*/
/**************************************************************************************/

/**************************************************************************************/
/**************************************************************************************/
/* Section: Included Files                                                            */
/**************************************************************************************/
/**************************************************************************************/

#include "USB.h"
#include "commands.h"
#include "commmodule.h"
#include "fifo.h"
#include "high_side.h"
#include <stdbool.h>

/**************************************************************************************/
/**************************************************************************************/
/* Section: Structure Data and Local Variables                                        */
/**************************************************************************************/
/**************************************************************************************/

#define USB_READ_BUFFER_SIZE 64

/* Fulfill USB DMA transfer criteria */
#define USB_MAKE_BUFFER_DMA_READY  __attribute__((coherent)) __attribute__((aligned(16)))

 
#define APP_EP_BULK_IN  1U                                                              /* Number of Endpoints used.*/   
  
#define APP_EP_BULK_OUT 1U                                                              /* Number of Endpoints used.*/

/**************************************************************************************/
/* USB Data

  Summary:
    These structures hold the required states and variables to perform the USB tasks.

  Description:
    These structures hold the required states and variables to perform the USB tasks. 
    These are here to link these structures for use by the local functions.
 
  Remarks: 
    These are defined in USB.h
*/

USB_DATA USB;


uint8_t receivedDataBuffer[USB_READ_BUFFER_SIZE] USB_MAKE_BUFFER_DMA_READY;             /*!< Receive data buffer.*/

uint8_t  transmitDataBuffer[USB_READ_BUFFER_SIZE] USB_MAKE_BUFFER_DMA_READY;            /*!< Transmit data buffer.*/

uint16_t endpointSize;                                                                  /*!< The endpoint size is 64 for FS and 512 for HS.*/

uint8_t usb_tick_count;                                                                 /*!< USB watchdog timer tick.*/
 
bool data_sent;


/**************************************************************************************/
/**************************************************************************************/
/* Application USB Device Layer Event Handler                                         */
/**************************************************************************************/
/**************************************************************************************/

void USB_USBDeviceEventHandler(USB_DEVICE_EVENT event, void * eventData, 
                uintptr_t context)
{
    uint8_t * configurationValue;
    USB_SETUP_PACKET * setupPacket;
    switch(event)
    {
        case USB_DEVICE_EVENT_RESET:                                                    
        { 
//            LED1On();
            USB.deviceIsConfigured = false;                                             /* Flag to show device is not configured. The host has not*/
                                                                                        /* enumerated it yet.*/
        }
        break;
        
        case USB_DEVICE_EVENT_DECONFIGURED:                                             /* Device is reset or de-configured.*/
        {
//            LED1On();
            USB.deviceIsConfigured = false;                                             /* Flag to show device is not configured. The host has not*/
                                                                                        /* enumerated it yet.*/
        }
        break;

        case USB_DEVICE_EVENT_CONFIGURED:
        {
            
            configurationValue = (uint8_t *)eventData;                                  /* Check the configuration */
            if(*configurationValue == 1U )                                              /* The device is in configured state. Update the LED indication.*/
            {
//                LED1Off();
                USB.deviceIsConfigured = true;                                          /* Reset endpoint data send & receive flag.*/
            }
        }
        break;

        case USB_DEVICE_EVENT_SUSPENDED:                                                /* Device is suspended. Update LED indication.*/
        { 
//            LED1On();
        }
        break;

        case USB_DEVICE_EVENT_POWER_DETECTED:                                           /* VBUS is detected. Attach the device.*/
        {
            USB_DEVICE_Attach(USB.usbDevHandle);
            USB.attached = true;                                                        /* Flag to show USB is attached to host.*/
        }
        break;

        case USB_DEVICE_EVENT_POWER_REMOVED:                                            /* VBUS is removed. Detach the device.*/
        { 
            USB_DEVICE_Detach (USB.usbDevHandle);
            USB.attached = false;                                                       /* Flag to show USB is detached from host.*/
        }
        break;

        case USB_DEVICE_EVENT_CONTROL_TRANSFER_SETUP_REQUEST:                           /* This means we have received a setup packet.*/
        {
            /*LDRA_INSPECTED 94 S*/                                                     /*MPLAB Harmony generated function.*/
            setupPacket = (USB_SETUP_PACKET *)eventData;
            if(setupPacket->bRequest == USB_REQUEST_SET_INTERFACE)                      /* If we have got the SET_INTERFACE request, we just acknowledge*/
            {                                                                           /* for now. This system has only one alternate setting which is already*/
                                                                                        /*active.*/ 
                USB_DEVICE_ControlStatus(USB.usbDevHandle,
                        USB_DEVICE_CONTROL_STATUS_OK);
            }
            else if(setupPacket->bRequest == USB_REQUEST_GET_INTERFACE)                 /* We have only one alternate setting and this setting 0. So*/
            {                                                                           /* we send this information to the host. */             
                USB_DEVICE_ControlSend(USB.usbDevHandle, &USB.altSetting, 1);
            }
            else                                                                        /* We have received a request that we cannot handle. Stall it.*/
            {
                USB_DEVICE_ControlStatus(USB.usbDevHandle, 
                        USB_DEVICE_CONTROL_STATUS_ERROR);
            }
        }
        break;

        case USB_DEVICE_EVENT_ENDPOINT_READ_COMPLETE:                                   /* Endpoint read is complete.*/
        {
            USB.epDataReadPending = false;                                              /* Reset this flag.*/
        }
        break;

        case USB_DEVICE_EVENT_ENDPOINT_WRITE_COMPLETE:                                  /* Endpoint write is complete.*/
        {
            USB.epDataWritePending = false;                                             /* Reset this flag.*/
        }
        break;

        
        case USB_DEVICE_EVENT_RESUMED:                                                  /* These events are not used. */
        {
            
        }
        break;
        
        case USB_DEVICE_EVENT_ERROR:                                                    /* These events are not used. */
        {
            
        }
        break;
        
        default:
        {
            /*Comment.*/
        }
        break;
    }
}

/**************************************************************************************/
/**************************************************************************************/
/* Section: State Machine Functions                                                   */
/**************************************************************************************/
/**************************************************************************************/


/***************************************************************************************
  Function:
    void USB_Tasks ( void )
  
  Summary:
   This routine is the USB_tasks function.  It defines the (USB) state machine and
   core logic.

  Remarks:
    Refer to the USB.h interface header for function usage details.
 */

void USB_Tasks (void )                                                                  /* USB state machine.*/
{
    switch(USB.state)                                                                   /* Check the machines current state.*/
    {
        case USB_STATE_INIT:                                                            /* This machines initial state.*/
        {            
            USB.usbDevHandle = USB_DEVICE_HANDLE_INVALID;                               /* Set the handle to invalid.*/
            USB.deviceIsConfigured = false;                                             /* The device has not been configured.*/
            USB.endpointRx = (APP_EP_BULK_OUT | USB_EP_DIRECTION_OUT);                  /* Define the receive endpoint.*/
            USB.endpointTx = (APP_EP_BULK_IN | USB_EP_DIRECTION_IN);                    /* Define the transmit endpoint.*/
            USB.epDataReadPending = false;                                              /* Initialize to no reads pending.*/
            USB.epDataWritePending = false;                                             /* Initialize to no writes pending.*/
            USB.altSetting = 0U;
            USB.byte_count = 0U;
            USB.attached = false;          
            USB.tick = false;                                                           /* Initialize timer tick.*/ 
            USB_RST_On();
//            TPAN2On();                                                                  /* Set high so USB can enumerate.*/
            USB.state = USB_STATE_OPEN;                                                 /* Move on to open the USB port.*/
            
            usb_tick_count = 0U;                                                        /* Initialize timer tick count.*/
            data_sent = false;
        }
        break;
        
        case USB_STATE_OPEN:
        {    
            USB.usbDevHandle = USB_DEVICE_Open( USB_DEVICE_INDEX_0,                     /* Open the device layer.*/
                    DRV_IO_INTENT_READWRITE );

            if(USB.usbDevHandle != USB_DEVICE_HANDLE_INVALID)                           /* If the device was opened,*/
            { 
                USB_DEVICE_EventHandlerSet(USB.usbDevHandle,                            /* Register a callback with device layer to get event*/
                    USB_USBDeviceEventHandler, 0);                                      /* notification (for end point 0).*/

                USB.state = USB_STATE_WAIT_FOR_CONFIGURATION;
            }
            else                                                                        /* The Device Layer is not ready to be opened. We should try*/                 
            {                                                                           /* again later.*/
                /*Comment.*/
            }
        }
        break;

        case USB_STATE_WAIT_FOR_CONFIGURATION:
        {
            usb_watchdog();
            if(USB.deviceIsConfigured == true)                                          /* Check if the device is configured.*/
            {
                if (USB_DEVICE_ActiveSpeedGet(USB.usbDevHandle) == USB_SPEED_FULL)      /* If the speed has been set to full,*/
                {
                    endpointSize = 64;                                                  /* set the endpoint size to 64.*/
                }
                else if (USB_DEVICE_ActiveSpeedGet(USB.usbDevHandle) == USB_SPEED_HIGH) /* Otherwise, if the speed has been set to high,*/
                {
                    endpointSize = 512;                                                 /* set the endpoint size to 512.*/
                }
                else
                {
                    /*Comment.*/
                }
                /*LDRA_INSPECTED 433 S*/                                                /* MPLAB Harmony generated function.*/
                if (USB_DEVICE_EndpointIsEnabled(USB.usbDevHandle,                      /* If the receive endpoint has not been enabled,*/
                        USB.endpointRx) == false )
                {                    
                    USB_DEVICE_EndpointEnable(USB.usbDevHandle, 0, USB.endpointRx,      /* Enable Read Endpoint for bulk transfers.*/
                        USB_TRANSFER_TYPE_BULK, endpointSize);
                }
                /*LDRA_INSPECTED 433 S*/                                                /* MPLAB Harmony generated function.*/
                if (USB_DEVICE_EndpointIsEnabled(USB.usbDevHandle,                      /* If the transmit endpoint has not been enabled,*/
                        USB.endpointTx) == false )
                {                    
                    USB_DEVICE_EndpointEnable(USB.usbDevHandle, 0, USB.endpointTx,      /* Enable Write Endpoint for bulk transfers.*/
                        USB_TRANSFER_TYPE_BULK, endpointSize);
                }
                
                USB.epDataReadPending = true;                                           /* Indicate that we are waiting for read */

                USB_DEVICE_EndpointRead(USB.usbDevHandle, &USB.readTranferHandle,       /* Place a new read request. */
                    USB.endpointRx, &receivedDataBuffer[0],sizeof(receivedDataBuffer) );
   
                USB.state = USB_STATE_READ;                                             /* Device is ready to run the read task */
            }
        }
        break;

        case USB_STATE_READ:
        {
            usb_watchdog();
            if(USB.deviceIsConfigured == false)                                         /* This means the device got de-configured. Change the*/                 
            {                                                                           /* application state back to waiting for configuration.*/       
                USB.state = USB_STATE_WAIT_FOR_CONFIGURATION;
                
                USB_DEVICE_EndpointDisable(USB.usbDevHandle, USB.endpointRx);           /* Disable the receive endpoint.*/
                USB_DEVICE_EndpointDisable(USB.usbDevHandle, USB.endpointTx);           /* Disable the transmit endpoint.*/
                USB.epDataReadPending = false;                                          /* Reset the flag to show no read is occurring.*/
                USB.epDataWritePending = false;                                         /* Reset the flag to show no write is occurring.*/
            }
            else if (USB.epDataReadPending == false)                                    /* If we have received data,*/
            {
                usb_tick_count = 0U;                                                    /* Reset watchdog counter.*/
                USB.tick = false;                                                       /* Reset the timer tick.*/
                if( USB.byte_count < CMD.cmd_size )                                     /* transfer the data to the RxFifo buffer.*/
                {
                    (void) Fifo_Put( &RX_FIFO, receivedDataBuffer[USB.byte_count] );    /* put the byte into the RxFifo for later analysis.*/
                    USB.byte_count = USB.byte_count + 1U;
                }
                else if (USB.byte_count == CMD.cmd_size)                                /* If we have received enough bytes,*/
                {
                    USB.byte_count = 0U;                                                /* reset the counter.*/ 
                    if( Fifo_Length( &RX_FIFO ) == CMD.cmd_size )                       /* If we have received enough bytes for a command,*/
                    {
                        COMM.state = COMM_STATE_VALIDATE;                               /* move on to see if it is a valid command in commmodule.c.*/
                    }
                    USB.state = USB_STATE_WAIT;                                         /* move on to wait for the command to be processed.*/
                }
                else
                {
                                                                                        /*MISRA compliance.*/
                }
            }
            else
            {
                                                                                        /*MISRA compliance.*/
            }
        }
        break;
        
        case USB_STATE_WAIT:                                                            /* Wait here to process a command before sending response.*/
        {                                                                               /* State will move to WRITE from commmodule.c.*/
            
        }
        break;
        
        case USB_STATE_WRITE:
        {
            usb_watchdog();
            if(!USB.deviceIsConfigured)                                                 /* This means the device got de-configured. Change the*/                 
            {                                                                           /* application state back to waiting for configuration.*/       
                USB.state = USB_STATE_WAIT_FOR_CONFIGURATION;
                
                USB_DEVICE_EndpointDisable(USB.usbDevHandle, USB.endpointRx);           /* Disable the endpoints.*/
                USB_DEVICE_EndpointDisable(USB.usbDevHandle, USB.endpointTx);
                USB.epDataReadPending = false;
                USB.epDataWritePending = false;
            }
            else if(USB.epDataWritePending == false)                                    /* If we are not currently writing any data to the host,*/
            {
                usb_tick_count = 0U;                                                    /* Reset watchdog counter.*/
                data_sent = true;                                                       /* Set flag to show data was sent.*/
                USB.tick = false;
                if(( USB.byte_count < CMD.cmd_size )&&((HIGH_SIDE.good_data_flag == true)))                                     /* If not all of the data has been sent,*/
                {
                    transmitDataBuffer[USB.byte_count] = Fifo_Get( &TX_FIFO );          /* Place the data to write into the transmit DataBufer.*/                  
                    USB.byte_count = USB.byte_count + 1U;
                }
                else if ((USB.byte_count == CMD.cmd_size)&&((HIGH_SIDE.good_data_flag == true)))
                {
                    USB.byte_count = 0U;                                                /* Reset the count.*/
                    USB.epDataWritePending = true;                                      /* Set this flag to show we are about to write the data to the host.*/

                    USB_DEVICE_EndpointWrite ( USB.usbDevHandle,                        /* Write the data to the host.*/ 
                        &USB.writeTranferHandle, USB.endpointTx, 
                        &transmitDataBuffer[0], sizeof(transmitDataBuffer),
                        USB_DEVICE_TRANSFER_FLAGS_MORE_DATA_PENDING);
                    
                    USB.state = USB_STATE_INITIATE_READ;
                }
                else
                {
                                                                                        /*MISRA compliance.*/
                }
            }
            else
            {
                                                                                        /*MISRA compliance.*/
            }
        }
        break;
        
        case USB_STATE_INITIATE_READ:
        {
           usb_watchdog();
            if(!USB.deviceIsConfigured)                                                 /* This means the device got de-configured. Change the*/                 
            {                                                                           /* application state back to waiting for configuration.*/       
                USB.state = USB_STATE_WAIT_FOR_CONFIGURATION;
                
                USB_DEVICE_EndpointDisable(USB.usbDevHandle, USB.endpointRx);           /* Disable the endpoints.*/
                USB_DEVICE_EndpointDisable(USB.usbDevHandle, USB.endpointTx);
                USB.epDataReadPending = false;
                USB.epDataWritePending = false;
            }
            else if(USB.epDataWritePending == false)                                    /* If we are not currently writing any data to the host,*/
            {            
                USB.epDataReadPending = true;                                           /* Indicate that we are waiting for read.*/

                USB_DEVICE_EndpointRead(USB.usbDevHandle, &USB.readTranferHandle,       /* Place a new read request.*/
                    USB.endpointRx, &receivedDataBuffer[0],sizeof(receivedDataBuffer) );

                USB.state = USB_STATE_READ;                                             /* Device is ready to run the read task.*/
            }
            else
            {
                                                                                        /*MISRA compliance.*/
            }
        }
        break;

        case USB_STATE_ERROR:
        {
                                                                                        /*MISRA compliance.*/
        }
        break;

        default:
        {
            /*Comment.*/
        }
        break;
    }
}

/**************************************************************************************/
/**************************************************************************************/
/* Section: Local Functions                                                           */
/**************************************************************************************/
/**************************************************************************************/

/*!************************************************************************************* 
  Function:
    static void usb_watchdog(void)

  Summary:
    Function to initialize Manchester parameters.

  Remarks:
    Refer to the man.h interface header for function usage details.
 */

static void usb_watchdog(void)
{ 
    if((USB.tick == true) && (data_sent == true))  
    if((USB.tick == true) )     
    {
        usb_tick_count++;
        USB.tick = false;                                                               /* Reset the timer tick.*/
    }    

    if((usb_tick_count == 2U) && (USB.attached == true))                                /* If two seconds have gone by,*/
    {
        USB_RST_On();                                                                   /* reset the USB VBUS line.*/
        USB_DEVICE_Detach (USB.usbDevHandle);                                           /* Detach the USB.*/
        USB.tick = false;                                                               /* Reset the timer tick.*/
    }    

    if(usb_tick_count == 5U)
    {        
//        LED1Off();
        USB_RST_Off();
        USB_DEVICE_Attach (USB.usbDevHandle);                                           /* Attach the USB connection.*/
        USB.tick = false;                                                               /* Reset the timer tick.*/
    }
    if(usb_tick_count == 30U)
    {
        usb_tick_count = 0U;                                                            /* Reset watchdog counter.*/
        USB.tick = false;                                                               /* Reset the timer tick.*/                                                                      
    }
}

/***************************************************************************************
 End of File
 */
