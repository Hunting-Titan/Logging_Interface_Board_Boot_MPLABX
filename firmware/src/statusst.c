/**************************************************************************************/
/** \file statusst.c
     
  Company:
    Hunting Titan
  
  File Name:
    statusst.c

  Summary:
    This file contains functions to manipulate the status register bits used in the 
    Protocol A and B commands.

  Description:
    This file contains functions to manipulate the status register bits used in the 
    Protocol A and B commands.  The bits are set or cleared based on switch actions 
    and command responses. 
*/
/**************************************************************************************/


/**************************************************************************************/
/**************************************************************************************/
/* Section: Included Files                                                            */
/**************************************************************************************/
/**************************************************************************************/

#include "statusst.h"
#include "crc.h"
#include "fifo.h"
#include "fsk.h"
#include "report.h"
#include <stdint.h>

/**************************************************************************************/
/**************************************************************************************/
/* Section: Defines                                                                   */
/**************************************************************************************/
/**************************************************************************************/

#define  	bitset( var, bitno )	 ( ( var ) |= 1UL << ( bitno ) )
#define  	bitclr( var, bitno )	 ( ( var ) &= ~ ( 1UL << ( bitno ) ) )

/**************************************************************************************/
/**************************************************************************************/
/* Section: Structure Data and Local Variables                                        */
/**************************************************************************************/
/**************************************************************************************/

/* Note use the qualifier of static after debugging*/
  static uint16_t  PIB_Status;

/**************************************************************************************/
/**************************************************************************************/
/* Section: Interface Functions                                                       */
/**************************************************************************************/
/**************************************************************************************/

/*!************************************************************************************* 
  Function:
    void Set_Status( uint8_t bitposn )

  Summary:
    Function to set a desired bit position to a one in the SurfaceStatus register.

  Remarks:
    Refer to the statusst.h interface header for function usage details.
 */

void Set_Status( uint8_t bitposn )
{
	bitset(PIB_Status, ( bitposn - 1U ));
}

/*!************************************************************************************* 
  Function:
    void Clear_Status( uint8_t bitposn )

  Summary:
    Function to clear a desired bit position to a 0 in the SurfaceStatus register.

  Remarks:
    Refer to the statusst.h interface header for function usage details.
 */

void Clear_Status( uint8_t bitposn )
{
	bitclr(PIB_Status, ( bitposn - 1U ));
}

/*!************************************************************************************* 
  Function:
    void Prepare_Return_A( uint8_t byte, uint16_t data2, uint16_t data1 )

  Summary:
    Function to prepare the protocol A response.

  Remarks:
    Refer to the statusst.h interface header for function usage details.
 */

void Prepare_Return_A( uint8_t byte, uint16_t data2, uint16_t data1 )
{
//	uint8_t a_temp[ 6 ];                                                                /*!< Temporary array to prepare protocol A response.*/ 
//	uint8_t a_comm_crc;                                                                 /*!< CRC result of Protocol A response.*/

	REPORT.data[8] = byte;                                                                 /* Put Command in Frame 0.*/                                                                                 
    REPORT.data[9] = ( uint8_t )((PIB_Status & 0xFF00U) >> 8);                             /* Move upper 8 bits of SurfaceStatus into Frame 1 & */
	REPORT.data[10] = ( uint8_t )(PIB_Status & 0x00FFU);                                    /* move lower 8 bits of SurfaceStatus into Frame 2.*/                                                                                        
                                                                                    
//    a_temp[ 3 ] = (uint8_t)((data2 & 0x0FF0U) >> 4);                                    /* Move upper 8 bits of data2 into Frame 3.*/
//    a_temp[ 4 ] = (uint8_t)((data2 & 0x000FU)) << 4;                                    /* Move lower 4 bits of data2 into upper 4 bits of Frame 4.*/
//    a_temp[ 4 ] = a_temp[ 4 ] | (uint8_t)(( data1 & 0x0F00U) >> 8);                     /* Move upper four bits of data1 into lower four bits of Frame 4.*/
//	a_temp[ 5 ] = (uint8_t) (data1 & 0x00FFU);                                          /* Move lower 8 bits of data1 into 8 bits of Frame 5.*/
//    
//	(void)Fifo_Put( &TX_FIFO, a_temp[ 0 ] );                                            /* Transfer array elements into TxFifo.*/
//	(void)Fifo_Put( &TX_FIFO, a_temp[ 1 ] );	
//	(void)Fifo_Put( &TX_FIFO, a_temp[ 2 ] );
//	(void)Fifo_Put( &TX_FIFO, a_temp[ 3 ] );
//	(void)Fifo_Put( &TX_FIFO, a_temp[ 4 ] );
//    (void)Fifo_Put( &TX_FIFO, a_temp[ 5 ] );
//    /*LDRA_INSPECTED 91 D*/    
//	a_comm_crc = Calc_CRC_Array( 6, a_temp );                                           /* Calculate the CRC of the array.*/
//	(void)Fifo_Put( &TX_FIFO, a_comm_crc );                                             /* Put the CRC result into the last byte of the TxFifo.*/                                
}

/***************************************************************************************
 End of File
 */
