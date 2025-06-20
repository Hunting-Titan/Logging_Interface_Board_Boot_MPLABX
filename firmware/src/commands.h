/**************************************************************************************/
/** \file commands.h

  Company:
    Hunting Titan

  File Name:
    commands.h

  Summary:
    This header file provides prototypes and definitions for commands.c.

  Description:
    This header file provides function prototypes and data type definitions for
    commands.c.  Some of these are required by the system (such as the
    "APP_Initialize" and "APP_Tasks" prototypes) and some of them are only used
    internally by the application (such as the "COMMAND_TASKS" definition).  
 */
/**************************************************************************************/

#ifndef COMMANDS_H                                                                      /* Guard against multiple inclusion.*/
#define COMMANDS_H

#ifdef __cplusplus                                                                      /* Provide C++ Compatibility. */
extern "C"
{
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
/* Section: Global Variables                                                          */
/**************************************************************************************/
/**************************************************************************************/



/**************************************************************************************/
/**************************************************************************************/
/* Section: Type Definition                                                           */
/**************************************************************************************/
/**************************************************************************************/
        
typedef unsigned char uchar8_t;

/**************************************************************************************/
/**************************************************************************************/
/* Section: Data Types                                                                */
/**************************************************************************************/
/**************************************************************************************/

/**************************************************************************************/
  
typedef enum                                                                            /*!< Enumerate the valid states for the CMD state machine.*/                                                                           
{                                                                                        	
	COMMAND_STATE_INIT=0,                                                               /*!< COMMAND_TASKS state machine's initial state. */
    COMMAND_STATE_WAIT,                                                                 /*!< Machine waits here for next command to process.*/      
	COMMAND_STATE_CRC_CHECK,                                                            /*!< Check that the CRC calculation matches transmitted value.*/
    COMMAND_STATE_EXECUTE_CMD,                                                          /*!< Execute the transmitted comaand and prepare the return message.*/

} COMMAND_STATES;

typedef struct                                                                          /* This structure collects the variables and states required for these*/ 
{                                                                                       /* functions to operate.*/   
    COMMAND_STATES state;                                                               /* The COMMAND_TASKS machine current state.*/

    uint16_t crc;                                                                       /*!< The calculated CRC for a valid command.*/
    uint8_t cmd_size;                                                                   /*!< Size in bytes for a valid command.*/
    uint8_t command[7];                                                                 /*!< Array to hold a valid command from the host.*/

    bool process_complete_flag;                                                         /*!< Flag to indicate when processing a command is completed.*/
    bool b_command_complete_flag;                                                       /*!< Flag to show that a protocol B command is completed.*/

} COMMAND_DATA;

extern COMMAND_DATA CMD;
/**************************************************************************************/
/**************************************************************************************/
/* Section: Interface Functions                                                       */
/**************************************************************************************/
/**************************************************************************************/

/*!*************************************************************************************
  Function:
     void COMMAND_Tasks( void )

  Summary:
    This function executes the commands from the host.  

  Description:
    This function executes the commands from the host. It does this by first ensuring 
    the CRC of the received command is correct.  If the CRC check matches, it goes on
    to execute the command.  The commands are divided up into three types; Protocol A,
    Protocol B and System.  Protocol A commands control the function of the Panel
    Interface Board.  Protocol B commands are for a PerfSwitch or other down hole tool. 
    System commands control the panel operation while it is being used for shooting. 
    An example would be showing the depth status.
    
  Precondition:
    None.

  Parameters:
    None.

  Returns
    None.
 
  Remarks:
    None.
 
  Example:
    void COMMAND_Tasks()  
 */
void COMMAND_Tasks( void );

/**************************************************************************************/
/**************************************************************************************/
/* Section: Local Functions                                                           */
/**************************************************************************************/
/**************************************************************************************/

/*!************************************************************************************* 
  Function:
    bool Valid_Command( uchar8_t msg ) 

  Summary:
    This function compares the received command(first byte)and compares it to a list
    of correct commands.  

  Description:
    This function compares the received command(first byte)and compares it to a list
    of correct commands.  If there is a match, the rest of the transmission is 
    received for processing.  Used in the ValidateComm function in commmodule.c    
    
  Precondition:
    None.

  Parameters:
    uchar8_t msg - The one byte command to compare.

  Returns
    bool ans - true if command is valid.
 
  Remarks
    None.
   
   Example:
     Valid_Command( command )  
 */
bool Valid_Command( uchar8_t msg );

/*!************************************************************************************* 
  Function:
    static void Execute_Auto_Protocol_A (void) 

  Summary:
    This function executes the Auto Protocol A commands. 

  Description:
    This function executes the Auto Protocol A commands.  These are commands that 
    control the panel.  The commands are listed as case statements.  Once the action is 
    completed, a response is generated and sent back to the host.     
    
  Precondition:
    None.

  Parameters:
    None.

  Returns
    None.
 
  Remarks
    None.
   
   Example:
    Execute_Auto_Protocol_A ()  
 */

static void Execute_Auto_Protocol_A (void);

/*!************************************************************************************* 
  Function:
    static void Execute_Protocol_A (void) 

  Summary:
    This function executes the Protocol A commands. 

  Description:
    This function executes the Protocol A commands.  These are commands that control
    the panel.  The commands are listed as case statements.  Once the action is 
    completed, a response is generated and sent back to the host.     
    
  Precondition:
    None.

  Parameters:
    None.

  Returns
    None.
 
  Remarks
    None.
   
   Example:
    ExecuteProtocolA ()  
 */

static void Execute_Protocol_A (void);

#ifdef __cplusplus                                                                      /* Provide C++ Compatibility.*/
}
#endif

#endif                                                                                  /* COMMANDS_H */

/***************************************************************************************
 End of File
 */
