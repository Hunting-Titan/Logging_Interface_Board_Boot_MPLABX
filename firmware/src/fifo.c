/**************************************************************************************/
/** \file fifo.c
  
  Company:
    Hunting Titan
  
  File Name:
   fifo.c

  Summary:
    This file contains the functions to initialize a FIFO buffer or add/retrieve an 
    entry from the buffer. 
    
  Description:
    This file contains the functions to initialize a FIFO buffer or add/retrieve an 
    entry from the buffer. No state machine is used here.  These functions are 
    called directly as needed.
 **************************************************************************************/

/**************************************************************************************/
/**************************************************************************************/
/*  Section: Included Files                                                           */                                                      
/**************************************************************************************/
/**************************************************************************************/

#include	 "fifo.h"

typedef unsigned char uchar8_t;

/**************************************************************************************/
/**************************************************************************************/
/* Section: Structure Data and Local Variables                                        */
/**************************************************************************************/
/**************************************************************************************/
/* Structure Data

  Summary:
    These structures hold required data.

  Description:
    These structures hold required data. These are here to link these 
    structures for use by the local functions.
 
  Remarks: 
    These are defined in fifo.h
*/
TFifo RX_FIFO;
TFifo TX_FIFO;

static	uint8_t FifoRxBuffer[ FIFO_RX_SIZE ];
static	uint8_t FifoTxBuffer[ FIFO_TX_SIZE ];

/**************************************************************************************/
/**************************************************************************************/
/* Section: Local Functions                                                           */
/**************************************************************************************/
/**************************************************************************************/

/*!************************************************************************************* 
  Function:
    void Fifo_Init( TFifo *ptrFifo, uint8_t *ptrBuffer, uint16_t Length )

  Summary:
   Function to initialize a Fifo.

  Remarks:
    Refer to the fifo.h interface header for function usage details.
 */

static void Fifo_Init( TFifo *ptrFifo, uint8_t *ptrBuffer, uint16_t Length )
{
	ptrFifo->length  	= (uint8_t) Length;
	ptrFifo->ptr_buffer	= ptrBuffer;

	ptrFifo->head		= 0U;
	ptrFifo->tail		= 0U;
	ptrFifo->num_records = 0U;
	ptrFifo->put_error	= 0U;
	ptrFifo->get_error	= 0U;
	ptrFifo->fEmpty  	= true;
	ptrFifo->fFull		= false;
}

/**************************************************************************************/
/**************************************************************************************/
/* Section: Interface Functions                                                       */
/**************************************************************************************/
/**************************************************************************************/

/*!************************************************************************************* 
  Function:
   void Init_Fifo(void)

  Summary:
   Function to initialize the Tx and Rx FIFOs. 

  Remarks:
    Refer to the fifo.h interface header for function usage details.
 */
void Init_Fifo(void)
{
    Fifo_Init( &RX_FIFO, FifoRxBuffer, FIFO_RX_SIZE );                                  /* Initialize the Tx and Rx FIFOs.*/
	Fifo_Init( &TX_FIFO, FifoTxBuffer, FIFO_TX_SIZE );
}

/*!************************************************************************************* 
  Function:
   uint8_t Fifo_Put( TFifo *ptrFifo, uint8_t Data )

  Summary:
   Function to put a byte of data into a Fifo. It also provides a check for a full Fifo.

  Remarks:
    Refer to the fifo.h interface header for function usage details.
 */

uint8_t Fifo_Put( TFifo *ptrFifo, uint8_t Data )
{
	if( ptrFifo->fFull == true )                                                        /* If the FIFO is full, that's an error.*/
	{
        /*LDRA_INSPECTED 567 S*/
        /*LDRA_INSPECTED 87 S*/                                                         /* Pointer results stay within data range.*/
		ptrFifo->put_error++;                                                           /* Increment error count.*/
		return FIFO_FULL;
	}
    /*LDRA_INSPECTED 567 S*/
    /*LDRA_INSPECTED 87 S*/                                                             /* Pointer results stay within data range.*/
	*( ptrFifo->ptr_buffer + ptrFifo->head ) = Data;                                    /* save the data in the FIFO.*/
	ptrFifo->num_records++;                                                             /* one more record (item) in the buffer.*/
	ptrFifo->fEmpty = false;                                                            /* not empty, now.*/
	++( ptrFifo->head );                                                                /* increment the head pointer in a circular.*/
                                                                                        /* fashion.*/

	if( ptrFifo->head >= ptrFifo->length )                                              /* If the Head counter is greater than the FIFO length,*/
	{
		ptrFifo->head = 0U;                                                             /* reset the count.*/
	}

	if( ptrFifo->head == ptrFifo->tail )                                                /* See if the FIFO is now full.*/
	{
		ptrFifo->fFull = true;
        ptrFifo->fEmpty = false;
	}
    
	return FIFO_ADD_OK;
}

/*!************************************************************************************* 
  Function:
   uint8_t Fifo_Get( TFifo *ptrFifo )

  Summary:
   Function to retrieve the oldest entry from a Fifo. It also provides a check for an 
    empty Fifo.

  Remarks:
    Refer to the fifo.h interface header for function usage details.
 */

uint8_t Fifo_Get( TFifo *ptrFifo )
{
	uchar8_t Data;

	if( ptrFifo->fEmpty == true )                                                       /* If the FIFO's empty, nothing to retrieve.*/
	{
        /*LDRA_INSPECTED 567 S*/
        /*LDRA_INSPECTED 87 S*/                                                         /* Pointer results stay within data range.*/
		++ptrFifo->get_error;
		return FIFO_EMPTY;
	}
    /*LDRA_INSPECTED 567 S*/
    /*LDRA_INSPECTED 87 S*/                                                             /* Pointer results stay within data range.*/
	Data = *( ptrFifo->ptr_buffer + ptrFifo->tail );                                    /* Get the data from the FIFO buffer*/
	ptrFifo->num_records--;                                                             /* One less record (item) in the buffer*/
	++( ptrFifo->tail );                                                                /* Increment the tail pointer in a circular*/
                                                                                        /* fashion.*/

	if( ptrFifo->tail >= ptrFifo->length )
	{
		ptrFifo->tail = 0U;
	}

	if( ptrFifo->head == ptrFifo->tail )                                                /* See if the FIFO is now empty.*/
	{
		ptrFifo->fEmpty = true;
        ptrFifo->fFull = false;
	}

	return Data;
}
/*!************************************************************************************* 
  Function:
   uint8_t Fifo_Length( TFifo *ptrFifo )

  Summary:
   Function to find the length of the buffer.

  Remarks:
    Refer to the fifo.h interface header for function usage details.
*/

uint8_t Fifo_Length( TFifo *ptrFifo )
{
	return ( uint8_t )( ptrFifo->num_records );
}

/***************************************************************************************
 End of File
 */
