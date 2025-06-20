/**************************************************************************************/
/** \file fsk.h

  Company:
    Hunting Titan

  File Name:
    fsk.h

  Summary:
    This header file provides prototypes and definitions for fsk.c.

  Description:
    This header file provides function prototypes and data type definitions for
    fsk.c.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "FSK_Tasks" definition).  
 */
/**************************************************************************************/

#ifndef FSK_H                                                                           /* Guard against multiple inclusion */
#define FSK_H
                
#ifdef __cplusplus                                                                      /* Provide C++ Compatibility */
extern "C" {
#endif
    
/**************************************************************************************/
/**************************************************************************************/
/* Section: Included Files                                                            */
/**************************************************************************************/
/**************************************************************************************/

#include"../system_config.h"
#include"../system_definitions.h"

/**************************************************************************************/
/**************************************************************************************/
/* Section: Data Types                                                                */
/**************************************************************************************/
/**************************************************************************************/    
 typedef float float32_t; 
/**************************************************************************************/
/*FSK states

  Summary:
    FSK states enumeration

  Description:
    This enumeration defines the valid FSK states.  These states
    determine the behavior of the FSK state machine at various times.
*/    
typedef enum                                                                            /*!< Enumerate the valid states for the FSK_STATE machine.*/
{
	FSK_STATE_INIT=0,                                                                   /*!< Application's state machine's initial state.*/            
    FSK_STATE_CHECK_MESSAGE_READY,                                                      /*!< Wait here until a message is ready to send to a PerfSwitch.*/
    FSK_STATE_PREP_MESSAGE,                                                             /*!< Wait for the conversion to complete.*/ 
    FSK_STATE_SEND_MESSAGE,                                                             /*!< Send the message to the PerfSwitch.*/
    FSK_STATE_WAIT,                                                                     /*!< Wait here while Manchester response is operating.*/
    FSK_STATE_COMPLETE_MESSAGE,                                                         /*!< Complete the message to the PerfSwitch.*/
 
} FSK_STATES;

/**************************************************************************************/
/* FSK_DATA

  Summary:
    Holds FSK_DATA used for the FSK tasks.

  Description:
    Holds FSK_DATA used for the FSK tasks. The state machine and variables
    used to control FSK functions are stored here.

  Remarks:
    None
 */

typedef struct
{
    FSK_STATES state;                                                                   /*!< The FSK tasks current state.*/

    uint8_t crc;                                                                        /*!< The calculated CRC.*/
    uint8_t null_count;                                                                 /*!< Count for generating a null value during FSK transmission.*/                                               
    bool send_message_complete_flag;                                                    /*!< Flag to show we have completed sending an FSK message.*/
    bool tick;                                                                          /*!< 100uS timer tick used to generate the 2.5mS null time in the preamble.*/                                                                     
    float32_t baud;                                                                     /*!< FSK baud rate in Hertz.*/
    float32_t fsk_timer_freq;                                                           /*!< Timer frequency used for FSK and MAN calculations.  10nS * 16.*/
    float32_t mark_count;                                                               /*!< Number of timer counts between a FSK DAC update for a 'Mark'.*/
    float32_t space_count;                                                              /*!< Number of timer counts between a FSK DAC update for a 'Space'.*/
    
    float32_t init_mark_count;                                                          /*!< Original number of timer counts between a FSK DAC update for a 'Mark'.*/
    float32_t init_space_count;                                                         /*!< Original number of timer counts between a FSK DAC update for a 'Space'.*/
     
    float32_t TABLE_MOD[50];                                                            /*!< Table to track FSK frequency scaling values for testing only.*/
    uint8_t table_count;                                                                /*!< Counter for FSK scaling array.*/
    
} FSK_DATA;

extern FSK_DATA FSK;

/**************************************************************************************/
typedef  union                                                                          /* Union defining the PerfSwitch message component lengths.*/
	{
		uint32_t    dword;                                                              /*!< Used for a 4 byte command.*/
		uint16_t    word;                                                               /*!< Used for a 2 byte command.*/                                                              
		uint8_t     byte[ 4 ];
	} TMultiValue;
    
extern TMultiValue MESSAGE;
/**************************************************************************************/
 
/**************************************************************************************/
/* DOWN_MSG Data

  Summary:
    Holds DOWN_MSG data used for the FSK tasks.

  Description:
    Holds DOWN_MSG data used for the FSK tasks. The variables used to control FSK 
    message are stored here.

  Remarks:
    None
 */

typedef struct                                                                          /* Structure defining the components of the FSK message to a PerfSwitch.*/
{	
	uint8_t identifier;                                                                 /*!< The StateID needed for a command.*/
	uint8_t command;                                                                    /*!< The command byte in the message.*/
	uint8_t msg_length;                                                                 /*!< The length in bits of the message to be transmitted.*/
	uint8_t xmit_ready_flag;                                                            /*!< Flag to show the message is ready to be transmitted.*/
    
} DOWN_MSG;

extern DOWN_MSG DWNMSG;

/**************************************************************************************/
/*MSG states

  Summary:
    MSG states enumeration

  Description:
    This enumeration defines the valid MSG states.  These states
    determine the behavior of the MSG state machine at various times. This machine 
    also controls access to the PRE_MSG state machine.
*/    
typedef enum                                                                            /*!< Enumerate the valid states for the MSG_STATE machine.*/
{
    MSG_STATE_IDLE=0,                                                                   /*!< MSG's state machine's initial state.*/            
	MSG_STATE_CAL_MAN_BIAS_1,                                                           /*!< Perform any necesary Manchester Bias adjustments.*/
    MSG_STATE_SEND_PREAMBLE,                                                            /*!< Send the Preamble of the FSK message.*/
    MSG_STATE_SEND_MESSAGE,                                                             /*!< Send the FSK message.*/
    MSG_STATE_NULL,                                                                     /*!< Send a null time(2.5mS).*/ 
            
} MSG_STATES;


/**************************************************************************************/
/* MSG_DATA

  Summary:
    Holds MSG_DATA used for the MSG tasks.

  Description:
    Holds MSG_DATA used for the MSG tasks. The state machine and variables
    used to control MSG functions are stored here.

  Remarks:
    None
 */

typedef struct
{
    MSG_STATES state;                                                                   /*!< The MSG tasks current state.*/
    uint32_t command;                                                                   /*!< The command to send to the PerfSwitch.*/
    uint8_t length;                                                                     /*!< The length in bits of the message to send to the PerSwitch.*/
    
} MSG_DATA;

extern MSG_DATA MSG;

/**************************************************************************************/
/*PREAMBLE states

  Summary:
    PRE_MSG states enumeration

  Description:
    This enumeration defines the valid PREAMBLE states.  These states
    determine the behavior of the PREAMBLE state machine at various times. This is 
    accessed from the MSG_STATE machine.
*/    
typedef enum                                                                            /*!< Enumerate the valid states for the PREAMBLE_STATE machine.*/
{
	PREAMBLE_STATE_SEND_TICKLE=0,                                                       /*!< Application's state machine's initial state. Send a mark tickle bit.*/
    PREAMBLE_STATE_NULL,                                                                /*!< Wait for the null period. 2.5mS.*/
    PREAMBLE_STATE_SEND_MARK_1,                                                         /*!< Send the first mark.*/
    PREAMBLE_STATE_SEND_MARK_2,                                                         /*!< Send the second mark.*/ 
    PREAMBLE_STATE_SEND_SPACE,                                                          /*!< Send a space.*/  
    PREAMBLE_STATE_IDLE                                                                 /*!< Come here when preamble is complete.*/
 
} PREAMBLE_STATES;


/**************************************************************************************/
/* PRE_DATA

  Summary:
    Holds PRE_MSG_DATA used for the PRE_MSG tasks.

  Description:
    Holds PRE_MSG_DATA used for the PRE_MSG tasks. The state machine and variables
    used to control PRE_MSG functions are stored here.

  Remarks:
    None
 */

typedef struct
{
    PREAMBLE_STATES state;                                                              /*!< The Preamble tasks current state.*/
    
} PRE_DATA;

extern PRE_DATA PRE_MSG;


static const uint8_t Xmit11[312] =                                                      /* Array for the FSK frequency generation for a 'Mark'.*/
{ 0x7FU, 0x99U, 0xB1U, 0xC6U, 0xD6U, 0xE0U, 0xE3U, 0xE0U, 0xD6U, 0xC6U, 0xB1U, 0x99U,   /* 13 cycles of 5200Hz represents a 'Mark'.*/
0x80U, 0x66U, 0x4EU, 0x39U, 0x29U, 0x1FU, 0x1BU, 0x1EU, 0x28U, 0x38U, 0x4CU, 0x65U,
0x7FU, 0x99U, 0xB1U, 0xC6U, 0xD6U, 0xE0U, 0xE3U, 0xE0U, 0xD6U, 0xC6U, 0xB1U, 0x99U,
0x80U, 0x66U, 0x4EU, 0x39U, 0x29U, 0x1FU, 0x1BU, 0x1EU, 0x28U, 0x38U, 0x4CU, 0x65U,
0x7FU, 0x99U, 0xB1U, 0xC6U, 0xD6U, 0xE0U, 0xE3U, 0xE0U, 0xD6U, 0xC6U, 0xB1U, 0x99U,
0x80U, 0x66U, 0x4EU, 0x39U, 0x29U, 0x1FU, 0x1BU, 0x1EU, 0x28U, 0x38U, 0x4CU, 0x65U,
0x7FU, 0x99U, 0xB1U, 0xC6U, 0xD6U, 0xE0U, 0xE3U, 0xE0U, 0xD6U, 0xC6U, 0xB1U, 0x99U,
0x80U, 0x66U, 0x4EU, 0x39U, 0x29U, 0x1FU, 0x1BU, 0x1EU, 0x28U, 0x38U, 0x4CU, 0x65U,
0x7FU, 0x99U, 0xB1U, 0xC6U, 0xD6U, 0xE0U, 0xE3U, 0xE0U, 0xD6U, 0xC6U, 0xB1U, 0x99U,
0x80U, 0x66U, 0x4EU, 0x39U, 0x29U, 0x1FU, 0x1BU, 0x1EU, 0x28U, 0x38U, 0x4CU, 0x65U,
0x7FU, 0x99U, 0xB1U, 0xC6U, 0xD6U, 0xE0U, 0xE3U, 0xE0U, 0xD6U, 0xC6U, 0xB1U, 0x99U,
0x80U, 0x66U, 0x4EU, 0x39U, 0x29U, 0x1FU, 0x1BU, 0x1EU, 0x28U, 0x38U, 0x4CU, 0x65U,
0x7FU, 0x99U, 0xB1U, 0xC6U, 0xD6U, 0xE0U, 0xE3U, 0xE0U, 0xD6U, 0xC6U, 0xB1U, 0x99U,
0x80U, 0x66U, 0x4EU, 0x39U, 0x29U, 0x1FU, 0x1BU, 0x1EU, 0x28U, 0x38U, 0x4CU, 0x65U,
0x7FU, 0x99U, 0xB1U, 0xC6U, 0xD6U, 0xE0U, 0xE3U, 0xE0U, 0xD6U, 0xC6U, 0xB1U, 0x99U,
0x80U, 0x66U, 0x4EU, 0x39U, 0x29U, 0x1FU, 0x1BU, 0x1EU, 0x28U, 0x38U, 0x4CU, 0x65U,
0x7FU, 0x99U, 0xB1U, 0xC6U, 0xD6U, 0xE0U, 0xE3U, 0xE0U, 0xD6U, 0xC6U, 0xB1U, 0x99U,
0x80U, 0x66U, 0x4EU, 0x39U, 0x29U, 0x1FU, 0x1BU, 0x1EU, 0x28U, 0x38U, 0x4CU, 0x65U,
0x7FU, 0x99U, 0xB1U, 0xC6U, 0xD6U, 0xE0U, 0xE3U, 0xE0U, 0xD6U, 0xC6U, 0xB1U, 0x99U,
0x80U, 0x66U, 0x4EU, 0x39U, 0x29U, 0x1FU, 0x1BU, 0x1EU, 0x28U, 0x38U, 0x4CU, 0x65U,
0x7FU, 0x99U, 0xB1U, 0xC6U, 0xD6U, 0xE0U, 0xE3U, 0xE0U, 0xD6U, 0xC6U, 0xB1U, 0x99U,
0x80U, 0x66U, 0x4EU, 0x39U, 0x29U, 0x1FU, 0x1BU, 0x1EU, 0x28U, 0x38U, 0x4CU, 0x65U,
0x7FU, 0x99U, 0xB1U, 0xC6U, 0xD6U, 0xE0U, 0xE3U, 0xE0U, 0xD6U, 0xC6U, 0xB1U, 0x99U,
0x80U, 0x66U, 0x4EU, 0x39U, 0x29U, 0x1FU, 0x1BU, 0x1EU, 0x28U, 0x38U, 0x4CU, 0x65U,
0x7FU, 0x99U, 0xB1U, 0xC6U, 0xD6U, 0xE0U, 0xE3U, 0xE0U, 0xD6U, 0xC6U, 0xB1U, 0x99U,
0x80U, 0x66U, 0x4EU, 0x39U, 0x29U, 0x1FU, 0x1BU, 0x1EU, 0x28U, 0x38U, 0x4CU, 0x65U};

static const uint8_t Xmit00[168] =                                                      /* Array for the FSK frequency generation for a 'Space'.*/
{ 0x7FU, 0x99U, 0xB1U, 0xC6U, 0xD6U, 0xE0U, 0xE3U, 0xE0U, 0xD6U, 0xC6U, 0xB1U, 0x99U,   /* 7 cycles of 2800 Hz represents a 'Space'.*/
0x80U, 0x66U, 0x4EU, 0x39U, 0x29U, 0x1FU, 0x1BU, 0x1EU, 0x28U, 0x38U, 0x4CU, 0x65U,
0x7FU, 0x99U, 0xB1U, 0xC6U, 0xD6U, 0xE0U, 0xE3U, 0xE0U, 0xD6U, 0xC6U, 0xB1U, 0x99U,
0x80U, 0x66U, 0x4EU, 0x39U, 0x29U, 0x1FU, 0x1BU, 0x1EU, 0x28U, 0x38U, 0x4CU, 0x65U,
0x7FU, 0x99U, 0xB1U, 0xC6U, 0xD6U, 0xE0U, 0xE3U, 0xE0U, 0xD6U, 0xC6U, 0xB1U, 0x99U,
0x80U, 0x66U, 0x4EU, 0x39U, 0x29U, 0x1FU, 0x1BU, 0x1EU, 0x28U, 0x38U, 0x4CU, 0x65U,
0x7FU, 0x99U, 0xB1U, 0xC6U, 0xD6U, 0xE0U, 0xE3U, 0xE0U, 0xD6U, 0xC6U, 0xB1U, 0x99U,
0x80U, 0x66U, 0x4EU, 0x39U, 0x29U, 0x1FU, 0x1BU, 0x1EU, 0x28U, 0x38U, 0x4CU, 0x65U,
0x7FU, 0x99U, 0xB1U, 0xC6U, 0xD6U, 0xE0U, 0xE3U, 0xE0U, 0xD6U, 0xC6U, 0xB1U, 0x99U,
0x80U, 0x66U, 0x4EU, 0x39U, 0x29U, 0x1FU, 0x1BU, 0x1EU, 0x28U, 0x38U, 0x4CU, 0x65U,
0x7FU, 0x99U, 0xB1U, 0xC6U, 0xD6U, 0xE0U, 0xE3U, 0xE0U, 0xD6U, 0xC6U, 0xB1U, 0x99U,
0x80U, 0x66U, 0x4EU, 0x39U, 0x29U, 0x1FU, 0x1BU, 0x1EU, 0x28U, 0x38U, 0x4CU, 0x65U,
0x7FU, 0x99U, 0xB1U, 0xC6U, 0xD6U, 0xE0U, 0xE3U, 0xE0U, 0xD6U, 0xC6U, 0xB1U, 0x99U,
0x80U, 0x66U, 0x4EU, 0x39U, 0x29U, 0x1FU, 0x1BU, 0x1EU, 0x28U, 0x38U, 0x4CU, 0x65U};

/**************************************************************************************/
/**************************************************************************************/
/*       External Functions                                                           */
/**************************************************************************************/
/**************************************************************************************/

/*!************************************************************************************* 
  Function:
    void Prepare_Dwn_Msg( uint8_t Identifier, uint8_t Cmd, uint8_t Msg_Length )

  Summary:
    Receives information from the command parser and stores it into the DwnMsg (FSK)
    structure for transmission by FSK.

  Description:
    Receives information from the command parser and stores it into the DwnMsg (FSK)
    structure for transmission by FSK. No other action is performed on the data here. 
    The DwnMsg (FSK) elements can be manipulated prior to the FSK transmission to 
    create the final MESSAGE array for longer commands.
    
  Precondition:
    None.

  Parameters:
    uint8_t Identifier:  The lower 3 bits of Frame 4 from the Protocol B command. 
    uint8_t Cmd: Frame 0 from the Protocol B command.
    uint8_t msgLength: The FSK message length in bits.

  Returns
    None.
 
  Remarks
    None.
   
   Example:
     Prepare_Dwn_Msg(ident,cmd, 20)   
 */
void Prepare_Dwn_Msg( uint8_t Identifier, uint8_t Cmd, uint8_t Msg_Length );


/*!************************************************************************************* 
  Function:
    void Generate_Sine_Wave_Data( float32_t NoOfTicks )

  Summary:
    This function stores sine wave inter step time values into two arrays at 
    initialization and if the FSK frequency needs to be adjusted. These values 
    represent the amount of time between updates of the sine wave data DAC used to 
    generate a 1 or 0.

  Description:
    This function stores sine wave inter step time values into two arrays at 
    initialization and if the FSK frequency needs to be adjusted. The TimeMark array 
    is for the time between a 'MARK' update and the TimeSpace array is for the time 
    between a 'SPACE' update. Changing the time between the updates will effectively 
    change the transmitted frequency for a 'MARK' or 'SPACE'. This occurs if there 
    are errors during the data transmission to a PerfSwitch. This can occur as the 
    PerfSwitch gets hot when it is down hole.
    
  Precondition:
    None.

  Parameters:
    float32_t NoOfTicks: This is an error factor used to correct the inter step 
    time values.

  Returns
    None.
 
  Remarks
    None.
   
   Example:
     void GenerateSineWaveData( float32_t NoOfTicks )   
 */
void Generate_Sine_Wave_Data( float32_t NoOfTicks );

/**************************************************************************************/
/**************************************************************************************/
/*       Local Functions                                                              */
/**************************************************************************************/
/**************************************************************************************/

/*!************************************************************************************* 
  Function:
    static void Init_FSK( void )  

  Summary:
    Function to initialize the FSK parameters.     

  Description:
    Function to initialize the FSK parameters. All of the flags and table data are 
    set to their initial condition.  Timer 2 is also started.  It is set to 160nS and
    is used to count the time between the Manchester transitions.
     
  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.
 
  Remarks:
    None.
   
  Example:
    Init_FSK()   
 */
static void Init_FSK( void );

/*!************************************************************************************* 
  Function:
   static	void Send_Space( void )

  Summary:
    This function sends a FSK 0 or 'SPACE'. 

  Description:
    This function sends a FSK 0 or 'SPACE'. It is called from the SendMessage 
    function. sendSpace reads the Xmit00 array and sends the data to the FSK DAC. 
    The time between the updates is controlled by a timer matching the corresponding
    value of the TimeSpace array.  An FSK 'zero' is approximately 2800 Hz with 
    7 cycles lasting approximately 2.5 ms.    
    
  Precondition:
    None.

  Parameters:
    None.

  Returns
    None.
 
  Remarks
    None.
   
   Example:
    SendSpace()   
 */
static	void Send_Space( void );

/*!************************************************************************************* 
  Function:
    static	void Send_Mark( void )

  Summary:
    This function sends a FSK 1 or 'MARK'.

  Description:
    This function sends a FSK 1 or 'MARK'. It is called from the Send_Message_Task 
    function. Send_Mark reads the Xmit11 array and sends the data to the FSK DAC. 
    The time between the updates is controlled by a timer matching the corresponding
    value of the TimeMark array.  An FSK 'one' is approximately 5200 Hz with 
    13 cycles lasting approximately 2.5 ms.
    
  Precondition:
    None.

  Parameters:
    None.

  Returns
    None.
 
  Remarks
    None.
   
   Example:
     sendMark()   
 */
static	void Send_Mark( void );

/**************************************************************************************/
/**************************************************************************************/
/*       State Machine Functions                                                      */
/**************************************************************************************/
/**************************************************************************************/

/*!*************************************************************************************
  Function:
    void FSK_Tasks(void)

  Summary:
    FSK_Tasks function

  Description:
    This routine is the FSK_Tasks function.  It defines the FSK_Tasks state 
    machine and core logic. This machine is used to send an FSK message to a 
    PerfSwitch. It checks to see if there is a message for Tx and decides if it is a 
    short or a long message. For a long message, it calculates the CRC and appends 
    it to the Message and calls Send_Message_Tasks. If a good Manchester response is 
    received, it resets all flags and prepares to send another message.  Otherwise, 
    it prepares to resend the previous message at a corrected frequency. 
 
  Precondition:
    The system ("SYS_Initialize") and application ("APP_Initialize")initialization 
    should be called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Remarks:
    This routine must be called from the APP_Tasks() routine.

  Example:
    FSK_Tasks()   
 */
void FSK_Tasks( void );

/*!*************************************************************************************
  Function:
    static void Send_Message_Tasks(void)

  Summary:
    Send_Message_Tasks function

  Description:
    This routine is the Send_Message_Tasks function.  It defines the Send_Message_Tasks 
    state machine and core logic. This machine is used to send an FSK message to a 
    PerfSwitch. It can control the Manchester bias DAC. It then controls the PREAMBLE
    (PRE_MSG) state machine to send the preamble(1,Null,1,1,0. Then the actual 
    message is sent.

  Precondition:
    The system ("SYS_Initialize") and application ("APP_Initialize")initialization 
    should be called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Remarks:
    This routine must be called from the FSK_Tasks() routine.

  Example:
    Send_Message_Tasks()   
 */

static void Send_Message_Tasks(void);

#ifdef __cplusplus                                                                      /* Provide C++ Compatibility.*/
}
#endif

#endif                                                                                  /* FSK_H */

/***************************************************************************************
 End of File
 */


