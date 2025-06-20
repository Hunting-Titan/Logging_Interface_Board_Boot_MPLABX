/**************************************************************************************/
/** \file crc.h

  Company:
    Hunting Titan

  File Name:
    crc.h

  Summary:
    This header file provides prototypes and definitions for crc.c.

  Description:
    This header file provides function prototypes and data type definitions for
    crc.c. These are required by the system to validate communications between 
    the host PC and the panel as well as communications between a PerfSwitch or 
    other tool and the Panel.  
 */
/**************************************************************************************/

#ifndef CRC_H                                                                           /* Guard against multiple inclusion.*/
#define CRC_H
                                                                                       
#ifdef __cplusplus                                                                      /* Provide C++ Compatibility */
extern "C"
{
#endif

/**************************************************************************************/
/* ************************************************************************************/
/* Section: Included Files                                                            */
/**************************************************************************************/
/**************************************************************************************/

#include <stdint.h>
    
typedef unsigned char uchar8_t;

/**************************************************************************************/
/**************************************************************************************/
/*       Interface Functions                                                          */
/**************************************************************************************/
/**************************************************************************************/

/*!************************************************************************************* 
  Function:
   void Calc_CRC(uint16_t nbits, uint8_t thebits) 

  Summary:
    Function to calculate the CRC for a number of data bits.

  Description:
    Function to calculate the CRC for a number of data bits. The algorithm for the 
    CRC calculation was created by Tom Woods.  CRCVal is usually reset to 0xFF prior 
    to calling this function. This is not the case when calculating the CRC for an 
    array.    
    
  Precondition:
    None.

  Parameters:
    int16_t nbits -  the number of data bits.
    uint8_t thebits - the data bits themselves.

  Returns
    None.
 
  Remarks
    None.
   
   Example:
    Calc_CRC( 8, Bytes[ 1 ] )   
 */
void Calc_CRC(uint16_t nbits, uint8_t thebits);

/*!************************************************************************************* 
  Function:
    uint8_t Calc_CRC_Array(uint16_t Count, const uint8_t Bytes[ ] )

  Summary:
    Function to calculate the CRC of an array of bytes. This function uses the function
    CalcCRC to complete this task.

  Description:
    Function to calculate the CRC of an array of bytes. This function uses the function
    CalcCRC to complete this task. It returns the eight bit CRCVal from the 
    calculation.    
    
  Precondition:
    None.

  Parameters:
    None.

  Returns
     uint8_t CRCVal
 
  Remarks
    None.
   
   Example:
    a_comm_crc = CalcCRCArray( 6, a_temp )   
 */
uint8_t Calc_CRC_Array(uint16_t Count, const uint8_t Bytes[ ] ) ;

/*!************************************************************************************* 
  Function:
    uint8_t Calc_CRC_Uplink(int16_t Count, const uint8_t Bytes[ ] )  

  Summary:
    Function to calculate the CRC from a received PerfSwitch message.

  Description:
    Function to calculate the CRC from a received PerfSwitch message. This function 
    makes use of the function CalcCRC() to perform the calculation.  The CRC result 
    is compared to the third byte of the returned Manchester message.
    
    
    
  Precondition:
    None.

  Parameters:
    int16_t Count: Acts as a flag.
    unsigned char Bytes[ ]: 

  Returns:
    uint8_t CRCVal
 
  Remarks:
    None.
   
  Example:
    crcans1 = Calc_CRC_Uplink( 3, MAN.MSG )   
 */
uint8_t Calc_CRC_Uplink(uint16_t Count, const uint8_t Bytes[ ] ) ;

/*!************************************************************************************* 
  Function:
    void Reset_CRC_Value( void ) 

  Summary:
    This function resets the CRC value so a new calculation can take place.

  Description:
    This function resets the CRC value so a new calculation can take place. It 
    resets the value to 0xFF. This allows for the proper bit manipulation during 
    the CRC calculation.
   
  Precondition:
    None.

  Parameters:
    None.

  Returns
    None.
 
  Remarks
    None.
   
   Example:
    Reset_CRC_Value()   
 */
void Reset_CRC_Value( void );

/*!************************************************************************************* 
  Function:
    uint8_t GetCRCValue( void )) 

  Summary:
    Function to return a previously calculated CRC value.

  Description:
    Function to return a previously calculated CRC value.  No calculations are done 
    here.
 
  Precondition:
    None.

  Parameters:
    None.

  Returns
    uint8_t CRCVal
 
  Remarks
    None.
   
   Example:
     FSK.crc = Get_CRC_Value( )   
 */
uint8_t Get_CRC_Value(void);

#ifdef __cplusplus                                                                      /* Provide C++ Compatibility.*/
}
#endif

#endif                                                                                  /* CRC_H */

/***************************************************************************************
 End of File
 */

