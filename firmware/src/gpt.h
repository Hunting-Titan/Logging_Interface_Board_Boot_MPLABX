/**************************************************************************************/
/** \file gpt.h

  Company:
    Hunting Titan

  File Name:
    gpt.h

  Summary:
    This header file provides prototypes and definitions for gpt.c.

  Description:
    This header file provides function prototypes and data type definitions for
    gpt.c.  Some of these are required by the system (such as the
    system_interrupt) and some of them are only used internally by the application 
    (such as the "GPT_STATES" definition).  
 */
/**************************************************************************************/

#ifndef GPT_H                                                                           /* Guard against multiple inclusion */
#define GPT_H

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

#include"../system_config.h"
#include"../system_definitions.h"    

typedef float float32_t;

/**************************************************************************************/
/**************************************************************************************/
/*  Section: Defines                                                                  */                                                      
/**************************************************************************************/
/**************************************************************************************/

/* Define the upper and lower bounds for GPT data, TMR2 tick = 10nS * 16 = 160nS. */    

//#define GptSyncUpper	1312U                                                           /*!< 0.20992 mS.*/ /* time div = 16*/
//#define GptSyncLower	1187U                                                           /*!< 0.1899 mS.*/

#define GptSyncUpper	690U                                                            /*!< 0.1104 mS.*/ /* time div = 16*/
//#define GptSyncLower	625U                                                            /*!< 0.10000 mS.*/
#define GptSyncLower	540U                                                             /*!< 0.0864 mS.*/

#define GptNullUpper	32500U                                                          /*!< 5.20 mS.*/
#define GptNullLower	32187U                                                          /*!< 5.15 mS.*/  

#define GptDataUpper	350U                                                            /*!< 0.056 mS.*/
//#define GptDataUpper	282U                                                            /*!< 0.045 mS.*/
#define GptDataLower	240U                                                            /*!< 0.0384 mS.*/ 

#define GptDataTimeLower 1219U                                                          /*!< 0.195mS.*/
#define GptDataTimeUpper 1237U                                                          /*!< 0.198mS.*/

#define NoGptBits		32U                                                             /*!< The number of bits in a valid Manchester response.*/

#define HalfBit  		0x12U
#define FullBit  		0x10U

#define	SizeOfBiasLUT   48U                                                             /*!< The size in bytes of the MAN_DAC Bias LUT.*/	

/**************************************************************************************/
/**************************************************************************************/
/* Section: Data Types                                                                */
/**************************************************************************************/
/**************************************************************************************/
 
/**************************************************************************************/
/* GPT states

  Summary:
    GPT states enumeration

  Description:
    This enumeration defines the valid GPT states.  These states
    determine the behavior of the GPT state machine at various times.
*/    

typedef enum                                                                            /*!< Enumerate the valid states for the GPT_STATE machine.*/
{
	GPT_STATE_INIT=0,                                                                   /*!< GPT Tasks state machine's initial state.*/ 
    GPT_STATE_WAIT,                                                                     /*!< Wait for an HVPS auto ramp command.*/ 
    GPT_STATE_CHECK,                                                                    /*!< Check to find a current spike.*/
    
            
    
    GPT_STATE_INIT_SPI_MAN,                                                             /*!< Inititialize the MAN Bias DAC SPI port and set DAC to initial value.*/
    GPT_STATE_IDLE,                                                                     /*!< Waiting for a manchester task to begin.*/
    GPT_STATE_RECEIVE_START,                                                            /*!< Process to begin receiving a response from a PerfSwitch.*/
    GPT_STATE_RECEIVE_WAIT,                                                             /*!< Wait for the data transmission from the PerfSwitch to complete.*/        
    GPT_STATE_PROCESS                                                                   /*!< Process the data from the PerfSwitch.*/        
 
} GPT_STATES;

/**************************************************************************************/
/* GPT_RX_STATES

  Summary:
    GPT_RX_STATES enumeration

  Description:
    This enumeration defines the valid GPT_RX_STATES.  These states determine the 
    behavior of the GPT_RX_STATES machine at various times. This machine receives 
    the data from a GPT tool.
*/  
    
typedef enum                                                                            /*!< Enumerate the valid states for the GPT_RX_STATE machine.*/
{                                                                 
    GPT_RX_STATE_IDLE=0,                                                                /*!< Waiting for a response. Sent here by GPT_Task.*/
    GPT_RX_STATE_TRY,
    GPT_RX_STATE_DONE,
    GPT_RX_STATE_INIT,
    GPT_RX_STATE_SYNC,                                                                  /*!< Receive the sync portion of the response.*/
    GPT_RX_STATE_NULL,                                                                  /*!< Receive the null portion of the response.*/
    GPT_RX_STATE_SYNC_DATA,                                                             /*!< Receive the sync data portion of the response.*/
    GPT_RX_STATE_DATA,                                                                  /*!< Receive the data portion of the response.*/
    GPT_RX_STATE_SYNC_CRC,                                                              /*!< Receive the sync crc portion of the response.*/
    GPT_RX_STATE_CRC                                                                    /*!< Receive the crc portion of the response.*/       
    
}GPT_RX_STATES; 

/**************************************************************************************/
/* GPT_PROCESS_STATES

  Summary:
    GPT_PROCESS_STATES enumeration

  Description:
    This enumeration defines the valid GPT_PROCESS_STATES.  These states
    determine the behavior of the GPT_PROCESS_STATES machine at various times.
*/  

typedef enum                                                                            /*!< Enumerate the valid states for the GPT_PROCESS_STATE machine.*/
{                                                              
    GPT_PROCESS_STATE_IDLE=0,                                                           /*!< GPT_PROCESS_Tasks state machine's initial state.*/
    GPT_PROCESS_STATE_PARSE,                                                            /*!< Decode and package the GPT respone.*/
    GPT_PROCESS_STATE_TEST                                                              /*!< Test response and prepare for another response.*/
    
}GPT_PROCESS_STATES;

/**************************************************************************************/
/* GPT_DATA

  Summary:
    Holds GPT_DATA used for the GPT tasks.

  Description:
    Holds GPT_DATA used for the GPT tasks. The state machine and variables
    used to control GPT functions are stored here.

  Remarks:
    None
 */

typedef struct                                                                          /* This structure collects the variables and states required for these*/ 
{                                                                                       /* functions to operate.*/ 
    
    GPT_STATES state;                                                                   /*!< The GPT tasks current state.*/
    GPT_RX_STATES Rx_state;                                                             /*!< The GPT_RX tasks current state.*/
    GPT_PROCESS_STATES Process_state;                                                   /*!< The GPT_PROCESS tasks current state.*/ 
  
    uint16_t sync[ 275 ];                                                               /*!< Stores the sync half wave timing.*/
	uint16_t data_sync[ 275 ];                                                          /*!< Stores the timing for the data_sync GPT waveform.*/                                                                                        
	uint16_t data[ 275 ];                                                               /*!< Stores the level for the received GPT waveform.*/                                                                                        
	uint8_t ans[ NoGptBits + 2 ];                                                       /*!< Stores the answer of the decoded GPT.*/
    uint8_t msg[4];                                                                     /*!< Stores a packaged GPT respone.*/

    uint8_t cnt_sync;                                                                   /*!< GPT sync index counter.*/
    uint8_t cnt_data;                                                                   /*!< GPT data index counter.*/
    uint8_t trynumber;                                                                  /*!< Variable used to track whether its the 1st,2nd or 3rd try to communicate.*/
    bool process_complete_flag;                                                         /*!< Flag to show GPT processing is complete.*/
//    bool spi_write_complete_flag;                                                       /*!< Flag to show if the SPI write has completed. Set true in call back.*/    
//    bool spi_sent_flag;                                                                 /*!< Flag to indicate if we have sent the SPI data.*/
    uint32_t timer_count;                                                               /*!< Counter for GPT reception timer.*/
//    uint8_t timer_complete;                                                             /*!< The number of timer counts needed to complete the GPT message reception.*/
    bool tick;                                                                          /*!< Timer tick to increment TIMER_COUNT.*/
    bool error;                                                                         /*!< Flag to show if a GPT error has occurred.*/
//    bool manual_bias_flag;                                                              /*!< Flag to indicate if the manual DAC bias setting is used.*/  
    uint8_t crc;                                                                        /*!< The calculated CRC of the GPT response.*/    
    uint32_t sync_timer_value;                                                          /*!< Sync timer count when a change was detected on GPT sync pin.*/
    uint32_t null_timer_value;                                                          /*!< Null timer count when a change was detected on GPT sync pin.*/
    uint32_t data_timer_value;                                                          /*!< Data timer count when a change was detected on GPT data pin.*/
    uint32_t sync_data_timer_value;                                                     /*!< Data timer count when a change was detected on GPT data pin.*/
    bool sync_received_flag;                                                            /*!< Flag to show a valid sync bit was received.*/
    bool data_received_flag;                                                            /*!< Flag to show a valid 'one' data bit was received.*/                                                           
    bool data_sync_received_flag;                                                       /*!< Flag to show a valid data sync bit was received.*/
    bool sync_timer_started_flag;                                                       /*!< Flag to indicate the rising edge of sync bit was received.*/
//    uint32_t sync_data_start;
//    uint32_t sync_data_stop;
    uint8_t data_count;                                                                 /*!< For troubleshooting.  Count the number of 'one' data bits received.*/
    uint8_t sync_bit_count;                                                             /*!< for troubleshooting. Count the number of sync bits received.*/
    uint8_t int_count;                                                                  /*!< For troubleshooting.  Count the number of 200uS intervals.*/

    bool sync_data_timer_started_flag;                                                  /*!< Flag to indicate the rising edge of the data sync bit was received.*/
//    uint32_t data_start;
//    uint32_t data_stop;
    bool data_timer_started_flag;                                                       /*!< Flag to indicate the timer to test a data bit width has started.*/
    bool data_bit;                                                                      /*!< Flag to indicate what type of bit was received during 200uS window.*/
    uint8_t data_bit_count;                                                             /*!< Array counter a channels' bit data.*/
    uint8_t data_ch_count;                                                              /*!< Array counter for channel data.*/
    uint16_t ch_data[22];                                                               /*!< The twenty one data channels plus the CRC/version data.*/
    uint16_t crc_data[1];                                                               /*!< The CRC value received to compared to the checksum value.*/
    uint16_t rev_data[1];                                                               /*!< The tool revision value.*/
    uint16_t ch_bit_data[12];                                                           /*!< Array to hold a channels' data bits. The bits are LSB first.*/
    uint16_t ch_rev_bit_data[12];                                                       /*!< Array to hold a channels' data bits in reverse order.  The bits are MSB first.*/
    uint8_t reverse_count;                                                              /*!< Counter to transfer the channels data bits to the reverse data array.*/
    
    uint16_t data_sum;
    uint8_t data_sum_low;
    uint8_t data_sum_high;
    uint8_t checksum;
    bool data_good_flag;
    bool null_timer_complete;                                                           /*!< Flag to show the null timer has completed.*/
    bool tmrIntTriggered;                                                               /*!< Flag to show the 200uS timer for a bit check has expired.*/
    uint8_t version;
    uint16_t CRC;
    uint32_t first_sum;                                                                 /*!< The sum of the twenty data channels.  Keep the lower 16 bits.*/
    uint16_t first_sum_MSB;                                                             /*!< The upper 8 bits of the 16 bit first sum result.*/
    uint16_t first_sum_LSB;                                                             /*!< The lower 8 bits of the 16 bit first sum result.*/
    uint8_t second_sum;                                                                 /*!< The sum of the MSB and LSB of the first sum.  This is compared the the CRC value.*/      
    
    uint8_t inter_count;
    bool inter_timer_tick;
    
    DRV_HANDLE  tmrHandle;

    
    
} GPT_DATA;

extern GPT_DATA GPT;





/**************************************************************************************/
/**************************************************************************************/
/*       Local Functions                                                              */
/**************************************************************************************/
/**************************************************************************************/

/*!************************************************************************************* 
  Function:
    static void Alarm_GPT( void )  

  Summary:
    Function to initialize the GPT parameters.

  Description:
    Function to initialize the GPT parameters. 
     
  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.
 
  Remarks:
    None.
   
  Example:
    Alarm_GPT()   
 */
void Alarm_GPT( void );
/*!************************************************************************************* 
  Function:
    static void Init_GPT( void )  

  Summary:
    Function to initialize the GPT parameters.

  Description:
    Function to initialize the GPT parameters. 
     
  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.
 
  Remarks:
    None.
   
  Example:
    Init_GPT()   
 */
void Init_GPT( void );
/*!************************************************************************************* 
  Function:
    static bool Check_GPT( void )

  Summary:
    This routine checks for valid GPT response. 

  Description:
    This routine checks for valid GPT response. The first two bytes are
    checked.  If both are zero, then we did not receive a valid response. This is 
    used in the function Test_GPT. 
    
  Precondition:
    None.

  Parameters:
    None.

  Returns:
    bool ans
 
  Remarks:
    None.
   
  Example:
    if( Check_GPT( ) == true )   
 */
static void Check_GPT( void );

/*!************************************************************************************* 
  Function:
    static void Decode_GPT( void )  

  Summary:
    Function to decode the response from a GPT.

  Description:
    Function to decode the response from a GPT.  The GPT.level 
    and GPT.time arrays are used to generate the GPT.ANS array.
    GPT.level[] - level of the incoming data.
    GPT.time[] - time of corresponding wave timer ticks.
 
	The last 1 of the preamble is always in the data so we have a fixed starting point.
 
  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.
 
  Remarks:
    None.
   
  Example:
    Decode_GPT()   
 */
static void Decode_GPT( void );

/*!************************************************************************************* 
  Function:
    static void Package_GPT( void )  

  Summary:
    Function to prepare GPT response for further processing.

  Description:
    Function to prepare GPT response for further processing. The GPT 
    response is decoded and the 1 X 32 answer array is packed into a 4 X 8 bit 
    message array.
 
  Precondition:
    None.

  Parameters:
    None. 

  Returns:
    None.
 
  Remarks:
    None.
   
  Example:
    Package_GPT()   
 */
static void Package_GPT( void );

/*!************************************************************************************* 
  Function:
    static void Test_GPT (void)  

  Summary:
    Function to test the returned GPT message.

  Description:
    Function to test the returned GPT message. The first two bytes are checked 
    to make sure they are not both 0. 
    
  Precondition:
    None.

  Parameters:
    None. 

  Returns:
    None.
 
  Remarks:
    None.
   
  Example:
    Test_GPT ()   
 */
//static void Test_GPT (void);

/*!************************************************************************************* 
  Function:
    static void Flush_Buffer_GPT( void )  

  Summary:
    Function to reset GPT.level[], GPT.time[], GPT.msg[] and GPT.preamble[] buffers.

  Description:
    Function to reset GPT.level[], GPT.time[], GPT.msg[] and GPT.preamble[] buffers. 
    These are flushed after every reception.
 
  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.
 
  Remarks:
    None.
   
  Example:
     Flush_Buffer_GPT()   
 */
static void Flush_Buffer_GPT( void );

/**************************************************************************************/
/**************************************************************************************/
/*       State Machine Functions                                                      */
/**************************************************************************************/
/**************************************************************************************/

/*!*************************************************************************************
  Function:
    void GPT_Tasks(void)

  Summary:
    GPT tasks function

  Description:
    This routine is the GPT tasks function.  It defines the GPT's state machine 
    and core logic. This machine tracks the wire line current when an HVPS auto ramp 
    command is given and indicates when a current spike is detected.

  Precondition:
    The system ("SYS_Initialize") and application ("APP_Initialize")initialization 
    should be called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Example:
    GPT_Tasks()
  
  Remarks:
    This routine must be called from the APP_Tasks() routine.
 */

void GPT_Tasks(void);

void GPT_RX_Tasks(void);



    
#ifdef __cplusplus                                                                      /* Provide C++ Compatibility */
}
#endif

#endif                                                                                  /*GPT_H */

/***************************************************************************************
 End of File
 */
