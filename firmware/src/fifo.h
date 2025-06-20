/**************************************************************************************/
/** \file fifo.h

  Company:
    Hunting Titan

  File Name:
    fifo.h

  Summary:
    This header file provides prototypes and definitions for fifo.c. 

  Description:
    This header file provides function prototypes and data type definitions for
    fifo.c.  These functions are used to manipulate the communication FIFOs.  Two 
    FIFOs are used. RxFifo holds data received from a host transmission. TxFifo holds 
    data to be sent to the host. 
 */
/**************************************************************************************/

#ifndef FIFO_H                                                                          /* Guard against multiple inclusion */
#define FIFO_H
                
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

/**************************************************************************************/
/**************************************************************************************/
/* Section: Defines                                                                   */
/**************************************************************************************/
/**************************************************************************************/

//#define FIFO_RX_SIZE	13                                                               /*!< The size of the RxFifo in bytes.*/
#define FIFO_RX_SIZE	1                                                               /*!< The size of the RxFifo in bytes.*/
#define FIFO_TX_SIZE	13                                                               /*!< The size of the TxFifo in bytes.*/  
    
                                                                                        /* FifoPut Return values.*/
#define FIFO_ADD_OK  	0                                                               /*!< Indicates that the FifoPut succeeded.*/
#define FIFO_FULL		1                                                               /*!< Indicates that the FifoPut failed because there is no room for more entries.*/

                                                                                        /* FifoGet Return Value.*/
#define FIFO_EMPTY		2U                                                              /*!< Indicates that FifoGet failed because the Fifo is empty.*/
    
/**************************************************************************************/
/**************************************************************************************/
/* Section: Data Types                                                                */
/**************************************************************************************/
/**************************************************************************************/

typedef  struct 
{
	uint8_t	length;                                                                     /*!< Buffer length.*/
	uint8_t *ptr_buffer;                                                                /*!< Pointer to the buffer storage.*/
    
                                                                                        /* Filled in by the FIFO functions.*/
    
	uint8_t	head;                                                                       /*!< Index to where new data goes.*/
	uint8_t	tail;                                                                       /*!< Index to where oldest data comes from.*/
	uint8_t	num_records;                                                                /*!< Number of items (records) in buffer.*/
	uint8_t	put_error;                                                                  /*!< Error counter for attempting to put data into full Fifo.*/
	uint8_t	get_error;                                                                  /*!< Error counter for attempting to get data from a empty Fifo.*/
	bool	fEmpty;                                                                     /*!< true if the FIFO is empty.*/
	bool	fFull;                                                                      /*!< true if the FIFO is full.*/
 
} TFifo;

extern TFifo RX_FIFO;                                                                    /* This structure is used for both the RxFifo and TxFifo.*/
extern TFifo TX_FIFO;


/**************************************************************************************/
/**************************************************************************************/
/* Section: Local Functions                                                           */
/**************************************************************************************/
/**************************************************************************************/

/*!*************************************************************************************
  Function:
    static void Fifo_Init( TFifo *ptrFifo, unsigned char *ptrBuffer, int Length )

  Summary:
    This function initializes a given Fifo.  

  Description:
    This function initializes the communication Fifo.  It is used to initialize both 
    the transmit and receive Fifo's.      
    
  Precondition:
    None.

  Parameters:
    None.

  Returns
    None.
 
  Remarks: 
    None.
 
  Example:
    Fifo_Init( &RX_FIFO, FifoRxBuffer, FIFO_RX_SIZE ) 
 */
static void Fifo_Init( TFifo *ptrFifo, uint8_t *ptrBuffer, uint16_t Length );

/**************************************************************************************/
/**************************************************************************************/
/* Section: Interface Functions                                                       */
/**************************************************************************************/
/**************************************************************************************/

/*!*************************************************************************************
  Function:
     void Init_Fifo(void)

  Summary:
    This function calls the function Fifo_Init to initialize the RxFifo and TxFifo.  

  Description:
    This function calls the function Fifo_Init to initialize the RxFifo and TxFifo.  
    This function is called in APP_Initialize in app.c
    
    
  Precondition:
    None.

  Parameters:
    None.

  Returns
    None.
 
  Remarks:
    None.
 
  Example:
    Init_Fifo()
 */
void Init_Fifo(void);

/*!*************************************************************************************
  Function:
    uint8_t  Fifo_Put( TFifo *ptrFifo, uint8_t Data )

  Summary:
     Function to add an entry (byte)to a Fifo. 

  Description:
    Function to add an entry (byte)to a Fifo. If the Fifo is full then the function 
    returns FIFO_FULL, otherwise the function adds the entry to the FifoBuffer, 
    increments FifoHead and returns FIFO_ADD_OK. 
    
  Precondition:
    None.

  Parameters:
    uint8_t Data: The byte of data to be added.
    TFifo *ptrFifo: The pointer to the Fifo that is being manipulated.

  Returns
    integer value. Fifo_Full or FIFO_ADD_OK
 
  Remarks:
    None.
 
  Example:
    Fifo_Put( &TX_FIFO, b_comm_crc )  
 */

uint8_t  Fifo_Put( TFifo *ptrFifo, uint8_t Data );

/*!*************************************************************************************
  Function:
     uint8_t Fifo_Get( TFifo *ptrFifo )

  Summary:
    Function to retrieve an entry from Fifo.  

  Description:
    Function to retrieve an entry from Fifo. If Fifo is empty then function returns 
    FIFO_EMPTY. Otherwise, the function returns the oldest entry in FifoBuffer and 
    increments FifoTail.
    
  Precondition:
    None.

  Parameters:
    TFifo *ptrFifo

  Returns
    uint8_t Contents of Fifo buffer.
 
  Remarks:
    None.
 
  Example:
    temp = Fifo_Get( &RX_FIFO )  
 */
uint8_t Fifo_Get( TFifo *ptrFifo );

/*!*************************************************************************************
  Function:
    uint8_t  Fifo_Length( TFifo *ptrFifo )

  Summary:
    Function to find the length of the buffer.  

  Description:
    Function to find the length of the buffer.  
    
  Precondition:
    None.

  Parameters:
     TFifo *ptrFifo: The pointer to the Fifo.

  Returns
    uint8_t. Length of the fifo buffer.
 
  Remarks:
    None.
 
  Example:
    if( Fifo_Length( &RX_FIFO ) == CMD.cmd_size )  
 */

uint8_t Fifo_Length( TFifo *ptrFifo );
          
#ifdef __cplusplus                                                                      /* Provide C++ Compatibility.*/
}
#endif

#endif                                                                                  /* FIFO_H */

/***************************************************************************************
 End of File
 */
