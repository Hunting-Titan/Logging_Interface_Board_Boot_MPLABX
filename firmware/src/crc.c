/**************************************************************************************/
/** \file crc.c
  
  Company:
    Hunting Titan
  
  File Name:
    crc.c

  Summary:
    These files calculate the CRC for the different communication functions.

  Description:
    These files calculate the CRC for the different communication functions. No 
    state machine is used here.  These functions are called directly as needed.
    
*/ 
/**************************************************************************************/

/* Acknowledgment Tom,Woods for the CalcCRC Function. */

/**************************************************************************************/
/* ************************************************************************************/
/* Section: Included Files                                                            */
/**************************************************************************************/
/**************************************************************************************/

#include	 "crc.h"

/**************************************************************************************/
/**************************************************************************************/
/* Section: Local Variables                                                           */
/**************************************************************************************/
/**************************************************************************************/

static	uint8_t CRCVal;

/**************************************************************************************/
/**************************************************************************************/
/*       Interface Functions                                                          */
/**************************************************************************************/
/**************************************************************************************/

/*!************************************************************************************* 
  Function:
    void CalcCRC( uint16_t nbits, uint8_t thebits )

  Summary:
   Function to calculate the CRC for a number of data bits.

  Remarks:
    Refer to the crc.h interface header for function usage details.
 */

void Calc_CRC( uint16_t nbits, uint8_t thebits )
{
	uint16_t i;                                                                         /* Bit counter.*/
	uint8_t flagbit;                                                                    /* Flag to determine how to complete CRC calculation.*/
    uint8_t bits;
    
    bits = thebits;

	for( i = 0U; i < nbits; i++ )
	{
		flagbit = ( CRCVal ^ bits ) & 0x01U;                                            /* Form the flagbit.*/
		CRCVal	>>= 1U;                                                                  /* Do the right-shift.*/
		bits >>= 1U;
		if( flagbit != 0x00U )
		{
			CRCVal ^= 0x0CU;                                                            /* EXOR a 1 into bits 2,3 of CRCVal.*/
			CRCVal |= 0x80U;                                                            /* Set the high bit of CRCVal.*/
		}
		else                                                                            /* Otherwise,*/
		{
			CRCVal &= 0x7FU;                                                            /* clear the high bit of CRCVal.*/
		}
	}
}

/*!************************************************************************************* 
  Function:
    uint8_t Calc_CRC__Array( uint16_t Count, uint8_t Bytes[ ] )

  Summary:
    Function to calculate the CRC of an array of bytes. This function uses the function
    CalcCRC to complete this task.

  Remarks:
    Refer to the crc.h interface header for function usage details.
 */

uint8_t Calc_CRC_Array( uint16_t Count, const uint8_t Bytes[ ] )
{
	uint16_t i;

	Reset_CRC_Value( );                                                                 /* Reset the CRC result.*/
	for( i = 0U; i < Count; i++ )                                                       /* Calculate the CRC for the array of bytes.*/
	{
		Calc_CRC( 8, Bytes[ i ] );
	}

	return ( CRCVal );                                                                  /* The CRC result is an 8 bit value.*/
}

/*!************************************************************************************* 
  Function:
    uint8_t Calc_CRC_Uplink( uint16_t Count, uint8_t Bytes[ ] )

  Summary:
   Function to calculate the CRC from a received PerfSwitch message.

  Remarks:
    Refer to the crc.h interface header for function usage details.
 */

uint8_t Calc_CRC_Uplink( uint16_t Count, const uint8_t Bytes[ ] )
{
	if( Count == 0x03U )
	{
		Reset_CRC_Value( );                                                             /* Reset the CRC value.*/
		Calc_CRC( 4, ( Bytes[ 0 ]>>4 ) );                                               /* Calculate the CRC for the upper four bits of byte 0 and then */
		Calc_CRC( 4, Bytes[ 0 ] );                                                      /* calculate the CRC for the lower four bits of byte 0 using the previous CRC value.*/
		Calc_CRC( 8, Bytes[ 1 ] );
		Calc_CRC( 8, Bytes[ 2 ] );
	}

	return ( CRCVal );                                                                  /* The CRC result is an 8 bit value.*/
}

/*!************************************************************************************* 
  Function:
   void Reset_CRC_Value( void )

  Summary:
   Function to reset the calculate CRC value (CRCVal).

  Remarks:
    Refer to the crc.h interface header for function usage details.
 */

void Reset_CRC_Value( void )
{
	CRCVal = 0xFFU;                                                                      
}

/*!************************************************************************************* 
  Function:
    uint8_t Get_CRC_Value( void )

  Summary:
   Function to return a previously calculated CRC value.

  Remarks:
    Refer to the crc.h interface header for function usage details.
 */

uint8_t Get_CRC_Value( void )
{
	return CRCVal;
}

/***************************************************************************************
 End of File
 */
