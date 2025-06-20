/**************************************************************************************/
/** \file statusst.h

  Company:
    Hunting Titan

  File Name:
    statusst.h

  Summary:
    This header file provides prototypes and definitions for statusst.c. These 
    functions are used to manipulate the status register bits used in the 
    Protocol A and B commands.

  Description:
    This header file provides function prototypes and data type definitions for
    statusst.c.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "WL_SPS_STATES" definition).  Both
    are defined here for convenience.
 */
/**************************************************************************************/

#ifndef STATUSST_H                                                                        /* Guard against multiple inclusion */
#define STATUSST_H
                
#ifdef __cplusplus                                                                      /* Provide C++ Compatibility */
extern "C" {
#endif
    
/**************************************************************************************/
/**************************************************************************************/
/* Section: Included Files                                                            */
/**************************************************************************************/
/**************************************************************************************/

#include <stdbool.h>
#include <stdint.h>
    
/*typedef unsigned char uchar8_t*/

/**************************************************************************************/
/**************************************************************************************/
/* Section: Data Types                                                                */
/**************************************************************************************/
/**************************************************************************************/
  
//uint16_t  PIB_Status;    
    
/**************************************************************************************/
/**************************************************************************************/
/* Section: Interface Functions                                                       */
/**************************************************************************************/
/**************************************************************************************/
    
/*!*************************************************************************************
  Function:
    void Set_Status(uint8_t bitposn)

  Summary:
    This function sets the desired bit to a one in the PIB status register. 

  Description:
    This function sets the desired bit to a one in the PIB status register.  This is 
    called by various functions to indicate a command result or switch setting.
    
  Precondition:
    None.

  Parameters:
    uint8_t bitposn - the desired bit position in the PIB status register.

  Returns
    None.
 
  Remarks:
    None.
 
  Example:
    Set_Status(6)  
 */

void Set_Status(uint8_t bitposn);

/*!*************************************************************************************
  Function:
    void Clear_Status(unsigned short bitposn)

  Summary:
    This function sets the desired bit to a zero in the PIB status register.  

  Description:
    This function sets the desired bit to a zero in the PIB status register. This is 
    called by various functions to indicate a command result or switch setting. 
    
  Precondition:
    None.

  Parameters:
    uint8_t bitposn - the desired bit position in the PIB status register.

  Returns
    None.
 
  Remarks:
    None.
 
  Example:
   ClearStatus(7) 
 */

void Clear_Status(uint8_t bitposn);

/*!*************************************************************************************
  Function:
    void Prepare_Return_A(uint8_t byte, uint16_t data2, uint16_t data1 )

  Summary:
    Function to prepare the protocol A response.

  Description:
    Function to prepare the protocol A response. The return message is seven bytes.
    the first byte is the command that was sent. the next two bytes are the PIB status 
    register. The next three bytes can contain two - 12 bit data fields. The data is 
    then transferred to the TxFifo.  The CRC for the return message is calculated 
    and placed in the last byte.
    
  Precondition:
    None.

  Parameters:
    uint8_t byte - The command byte.
    uint16_t data2 - a 12 bit data field.
    uint16_t data1 - 1 12 bit data field.

  Returns
    None.
 
  Remarks:
    None.
 
  Example:
    Prepare_Return_A(CMD.COMMAND[ 0 ], 0, 0) 
 */

void Prepare_Return_A(uint8_t byte, uint16_t data2, uint16_t data1 );
					 
#ifdef __cplusplus                                                                      /* Provide C++ Compatibility.*/
}
#endif

#endif                                                                                  /* STATUSST_H */

/***************************************************************************************
 End of File
 */
					 
