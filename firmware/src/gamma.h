/**************************************************************************************/
/** \file gamma.h

  Company:
    Hunting Titan

  File Name:
    gamma.h

  Summary:
    This header file provides prototypes and definitions for gamma.c.

  Description:
    This header file provides function prototypes and data type definitions for
    gamma.c.  These are required by the system to track the gamma counts. 
     
 */
/**************************************************************************************/

#ifndef GAMMA_H                                                                         /* Guard against multiple inclusion */
#define GAMMA_H

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
#include"../system_definitions.h"    

/**************************************************************************************/
/**************************************************************************************/
/* Section: Data Types                                                                */
/**************************************************************************************/
/**************************************************************************************/

typedef float float32_t;
    
/**************************************************************************************/
/* GAM_STATES 

  Summary:
    GAM_STATES enumeration

  Description:
    This enumeration defines the valid GAM states.  These states
    determine the behavior of the GAM state machine at various times.
*/    
typedef enum                                                                            /*!< Enumerate the valid states for the WL_CPS_STATE machine.*/
{
	GAM_STATE_INIT=0,                                                                   /*!< Application's state machine's initial state.*/            
    GAM_STATE_INIT_SPI_GAM,                                                             /*!< Open SPI port for GAM gain pot and initialize GAM to minimum gain.*/ 
    GAM_STATE_GAIN_ADJ,                                                                 /*!< Adjust gamma gain per the switch setting.*/            
    GAM_STATE_SPI_WRITE_WAIT,                                                           /*!< Wait until the SPI write has completed.*/
    GAM_STATE_IDLE                                                                      /*!< Move the state machine to idle.*/
 
} GAM_STATES;    
    
/**************************************************************************************/
/* GAM_DATA

  Summary:
    Holds GAM_DATA used for the GAM functions.

  Description:
    Holds GAM_DATA used for the GAM functions. The variables used to track the gamma
    counts are stored here along with variables for the gain setting.

  Remarks:
    None
 */
      
typedef struct
{ 
    GAM_STATES state;                                                                   /*!< The application's current state.*/
    
    DRV_HANDLE spi_cont_pot;                                                            /*!< Name for the SPI port to adjust GAMMA gain.*/
    DRV_SPI_BUFFER_HANDLE bufferHandle;
    DRV_SPI_BUFFER_HANDLE bufferHandle2; 
    
    int8_t v_adj[1];                                                                    /*!< The value sent to the GAM_GAIN_DATA.*/ 
    uint8_t index;                                                                      /*!< Table index for GAM_GAIN adjust.*/
    
    uint32_t count;                                                                      /*!< The integer number of counts recorded from the gamma count.*/ 
    double f_count;                                                                     /*!< Float version of count to allow for two counts per gamma pulse.*/
    bool count_flag;                                                                    /*!< Flag to indicate that the gamma count needs to be updated.*/
    bool spi_write_complete_flag;                                                       /*!< Flag to show if the SPI write has completed. Set true in call back.*/
    bool spi_sent_flag;                                                                 /*!< Flag to indicate if we have sent the SPI data.*/
    bool count_reset_flag;                                                              /*!< Flag to reset the gamma count if no pulses are received.*/
    bool count_reset_tick;                                                              /*!< Flag to indicate when teh gamma count needs to be reset.*/
    uint8_t reset_count;
    bool gamma_enable_flag;                                                             /*!< Flag to show gamma operation has been enabled.*/
    bool wireline_enable_flag;                                                          /*!< Flag to show wireline supply is on for gamma operation.*/

} GAMMA_DATA;

extern GAMMA_DATA GAM;

/**************************************************************************************/
/**************************************************************************************/
/*       Interface Functions                                                          */
/**************************************************************************************/
/**************************************************************************************/

/*!*************************************************************************************
  Function:
   void GAMMA_Init(void) 

  Summary:
    Function to initialize the gamma variables.

  Description:
    Function to initialize the gamma variables. These variables are used to track
    the gamma counts.
    
  Precondition:
    None.

  Parameters:
    None.

  Returns
    None.
 
  Remarks
    None.
   
   Example:
    GAMMA_Init()
*/  
void GAMMA_Init(void);

/*!************************************************************************************* 
  Function:
   void GAMMA_Counts(void) 

  Summary:
    Function to track the counts from the gamma detector.

  Description:
    Function to track the counts from the gamma detector. When a transition from the 
    gamma detector is detected, a flag is set in system interrupt.  One gamma count 
    causes two interrupts.  This is accounted for. The count is then transferred to 
    the REPORT array for later transmission to the host.
    
  Precondition:
    None.

  Parameters:
    None.

  Returns
    None.
 
  Remarks
    None.
   
   Example:
    GAMMA_Counts() 
 */   
void GAMMA_Counts(void);

/*!************************************************************************************* 
  Function:
   void GAMMA_Gain(void) 

  Summary:
    Function to track the gain setting for the gamma detector first stage.

  Description:
    Function to track the gain setting for the gamma detector. When the STATUS_LED    
    button is pressed, it will toggle through ten different gain settings.  The gain
    of the first stage is adjusted. The gain setting is sent to the host PC for display.
    
    
  Precondition:
    None.

  Parameters:
    None.

  Returns
    None.
 
  Remarks
    None.
   
   Example:
    GAMMA_Gain() 
 */   
void GAMMA_Gain(void);

/**************************************************************************************/
/**************************************************************************************/
/*       State Machine Functions                                                      */
/**************************************************************************************/
/**************************************************************************************/

/*!*************************************************************************************
  Function:
 * 
    void GAMMA_Tasks(void)

  Summary:
    GAMMA_Tasks function

  Description:
    This routine is the GAMMA_Tasks function.  It defines the GAMMA_Tasks state 
    machine and core logic. This machine is used to monitor the gamma counts. 
      

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
    GAMMA_Tasks()   
 */

void GAMMA_Tasks(void);
    
#ifdef __cplusplus                                                                      /* Provide C++ Compatibility */
}
#endif

#endif                                                                                  /* GAMMA_H */

/***************************************************************************************
 End of File
 */
