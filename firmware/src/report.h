/**************************************************************************************/
/** \file report.h

  Company:
    Hunting Titan

  File Name:
    report.h

  Summary:
    This header file provides prototypes and definitions for report.c.

  Description:
    This header file provides function prototypes and data type definitions for
    report.c.  This function creates the data array that is transmitted back to the 
    host.  
 */
/**************************************************************************************/


#ifndef REPORT_H                                                                        /* Guard against multiple inclusion.*/
#define REPORT_H

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
#include "system_config.h"
#include "system/system.h"
#include "usb/usb_common.h"
#include "usb/usb_chapter_9.h"
#include "usb/usb_device.h"
#include "usb/usb_device_hid.h"

/**************************************************************************************/
/* REPORT_DATA

  Summary:
    Holds REPORT_DATA used for generating data report.

  Description:
    Holds REPORT_DATA used for generating data report.  

  Remarks:
    None
 */

typedef struct
{
    uint8_t data[64];    
}
DACQ_REPORT;

extern DACQ_REPORT REPORT;

/**************************************************************************************/
/**************************************************************************************/
/*       Interface Functions                                                          */
/**************************************************************************************/
/**************************************************************************************/

/*!*************************************************************************************
  Function:
    void DACQ_ReportCreate(void)

  Summary:
    This function creates a report.

  Description:
    This function creates a report. The application can use this function 
    to create the report. The report can then be sent to the host by using
    the USB_DEVICE_HID_ReportSend() function.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None

  Example:
    DACQ_ReportCreate( )

  Remarks:
    None.
*/

void DACQ_ReportCreate( void );


#ifdef __cplusplus                                                                      /* Provide C++ Compatibility.*/
}
#endif

#endif                                                                                  /* REPORT_H */

/***************************************************************************************
 End of File
 */
