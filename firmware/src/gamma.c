/**************************************************************************************/
/** \file gamma.c
     
  Company:
    Hunting Titan
  
  File Name:
    gamma.c

  Summary:
    This file contains the state machine code for the GAMMA operation.

  Description:
    This file contains the state machine code for the GAMMA operation.  Once started, 
    the GAMMA detects a change in the gamma detector line.  The count is incremented 
    and the amount updated once per second. Each second starts a new count.
*/
/**************************************************************************************/

/**************************************************************************************/
/**************************************************************************************/
/* Section: Included Files                                                            */
/**************************************************************************************/
/**************************************************************************************/

#include "gamma.h"
#include "report.h"
#include "switches.h"
#include "nvm_fs.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <math.h>

#include <xc.h>
#include "system_config.h"
#include "system_definitions.h"


/**************************************************************************************/
/**************************************************************************************/
/* Section: Structure Data and Local Variables                                        */
/**************************************************************************************/
/**************************************************************************************/

/**************************************************************************************/
/* GAMMA Data

  Summary:
    These structures hold the required states and variables to perform the 
    GAMMA tasks.

  Description:
    These structures hold the required states and variables to perform the GAMMA 
    tasks. These are here to link these structures for use by the local functions.
 
  Remarks: 
    These are defined in gamma.h
*/

GAMMA_DATA GAM;
//DACQ_REPORT REPORT;

/**************************************************************************************/ 
/**************************************************************************************/ 
/* Section: SPI Callback Functions                                                    */ 
/**************************************************************************************/ 
/**************************************************************************************/ 

static void SPI_2_EventHandler (DRV_SPI_BUFFER_EVENT event,
        DRV_SPI_BUFFER_HANDLE bufferHandle, void * context )
{
    if (event == DRV_SPI_BUFFER_EVENT_COMPLETE )
    {
        GAM.spi_write_complete_flag = true;
    }
}

/**************************************************************************************/
/**************************************************************************************/
/* Section: State Machine Functions                                                   */
/**************************************************************************************/
/**************************************************************************************/

/*************************************************************************************** 
  Function:
    void GAM_Tasks ( void )

  Summary:
    This routine is the GAM_Tasks function.  It defines the (GAM) state machine 
    and core logic. This task monitors the GAM counts.

  Remarks:
    Refer to the gamma.h interface header for function usage details.
 */

void GAMMA_Tasks(void)
{
    switch ( GAM.state )                                                                /* Check the machines current state.*/                                                                        
    {
        case GAM_STATE_INIT:                                                            /* The machines initial state.*/
        {
            GAMMA_Init();                                                               /* Initialize parameters.*/
            GAM.state =  GAM_STATE_INIT_SPI_GAM;                                        /* Move on to open the SPI port and initialize the GAMMA gain.*/
        }
        break;
        
        case GAM_STATE_INIT_SPI_GAM:                                                    /* Open the SPI control pot port and initialize WL_CPS to minimum voltage.*/
        {
            if(GAM.spi_cont_pot == DRV_HANDLE_INVALID)                                  /* If the SPI port for the WL_CPS control pot had not been opened,*/
            {
                GAM.spi_cont_pot = DRV_SPI_Open( DRV_SPI_INDEX_0,                       /* open the port.*/
                    DRV_IO_INTENT_WRITE );
            }
            if(GAM.spi_cont_pot != DRV_HANDLE_INVALID)                                  /* If the SPI port for the WL_CPS control pot has been opened,*/
            {
                GAMMA_Gain();                                                           /* Set the GAMMA to minimum.*/
                GAM.state =  GAM_STATE_SPI_WRITE_WAIT;                                  /* Move on to wait for SPI write to complete.*/               
            }
        }
        break;
        
        case GAM_STATE_GAIN_ADJ:
        {
            if((GAM.spi_cont_pot != DRV_HANDLE_INVALID) &&                              /* If the SPI port for the GAMMA control pot has been opened,*/
                    (SWITCH.STATUS_SW_flag == true))                                    /* and the gain value has changed,*/    
            {                                                                           
                GAMMA_Gain();                                                           /* Set the GAMMA gain to the new value.*/
                GAM.state =  GAM_STATE_SPI_WRITE_WAIT;                                  /* Move on to wait for SPI write to complete.*/               
            }
            else
            {
                
            }
        }
        break;
        
        case GAM_STATE_SPI_WRITE_WAIT:
        {
            if(GAM.spi_write_complete_flag == true)                                     /* If the SPI port write has completed,*/
            {
                GAM.spi_write_complete_flag = false;                                    /* reset the flag and*/
                GAM.state =  GAM_STATE_IDLE;                                            /* move on to idle this machine.*/    
                SWITCH.gain_change_complete_flag = true;
            }
        }
        break;
        
        case GAM_STATE_IDLE:
        {
            
        }
        break;
        
        default:
        {
            
        }
        break;
    }    
}
/**************************************************************************************/
/**************************************************************************************/
/* Section: Interface Functions                                                       */
/**************************************************************************************/
/**************************************************************************************/

/*!************************************************************************************* 
  Function:
    void GAMMA_Init(void)

  Summary:
    This function initializes the gamma variables.    

  Remarks:
    Refer to the gamma.h interface header for function usage details.
 */

void GAMMA_Init(void)
{
    GAM.count = 0U;                                                                     /* Initialize variables.*/
    GAM.f_count = 0.0;
    GAM.count_flag = false;
    GAM.spi_cont_pot = DRV_HANDLE_INVALID;                                              /* Set to invalid to show SPI port is not open.*/
    GAM.spi_write_complete_flag = false;                                                /* Initialize the SPI write complete flag.*/
//    GAM.spi_sent_flag = false;                                                          /* Initialize flag to show we sent data to the SPI port.*/ 
    GAM.count_reset_flag = true;                                                        /* Initialize the flag to reset the gamma count value.*/
    GAM.count_reset_tick = false;                                                       /* initialize the counter rest flag.*/
    GAM.reset_count = 0U;
    GAIN_RESET_On();                                                                    /* Enable the gain pot.*/
    
    
}

/*!************************************************************************************* 
  Function:
    void GAMMA_Counts (void) 

  Summary:
    Track the gamma counts as the wire-line tool travels in the well.

  Remarks:
    Refer to the gamma.h interface header for function usage details.
 */

void GAMMA_Counts (void)
{
    if(SWITCH.command_setting == 2U)
    {
        REPORT.data[12] = ((GAM.count & 0xFF000000U)>> 24);                             /* Transfer GAMMA.counts to the required position*/
        REPORT.data[13] = ((GAM.count & 0x00FF0000U)>> 16);                             /* in the REPORT array for later transmission to the host.*/
        REPORT.data[14] = ((GAM.count & 0x0000FF00U)>> 8);
        REPORT.data[15] = GAM.count & 0x000000FFU;
    
        if((GAM.count_reset_tick == true) && (GAM.reset_count >= 2U))                   /* If the 1 second reset timer tick is true and 2 seconds has gone by*/
        {                                                                               /* with no gamma pulses,*/
            GAM.count = 0U;                                                             /* reset the gamma count.*/
            GAM.reset_count = 0U;                                                       /* Reset the variables.*/
            GAM.count_reset_tick = false;
            Set_Status( 8 );
        }
        if((GAM.count_reset_tick == true) && (GAM.count_reset_flag == true))            /* If the 1 second reset timer tick is true and we have not received*/
        {                                                                               /* any gamma pulses,*/
            GAM.reset_count = GAM.reset_count + 1U;                                     /* increment the reset counter and*/
            GAM.count_reset_tick == false;                                              /* reset the timer tick.*/
        }
        else if((GAM.count_reset_tick == true) && (GAM.count_reset_flag == false))      /* If the 1 second reset timer tick is true and we have received*/
        {                                                                               /* gamma pulses,*/
            GAM.reset_count = 0U;                                                       /* Reset the counter.*/                               
            GAM.count_reset_flag = true;                                                /* Reset the flags.*/
            GAM.count_reset_tick = false;
            Clear_Status( 8 );
        }
    }

}

/*!************************************************************************************* 
  Function:
    void GAMMA_Gain (void) 

  Summary:
    Function to adjust the gain settings for the gamma detector first stage.

  Remarks:
    Refer to the gamma.h interface header for function usage details.
*/

void GAMMA_Gain (void)
{     
    const int8_t Counts[] = {12,24,36,48,60,72,84,96,108,120};                          /* 10 settings for GAMMA pot settings.*/
    uint8_t pot_value = 0U;

    pot_value = SWITCH.STATUS_SW_count;                                                 /* Saved pot value.*/
    SWITCH.STATUS_SW_flag = false;                                                      /* Reset the flag.*/  
    GAM.v_adj[0] = Counts[pot_value];                                                   /* The Counts table provides predetermined pot settings for desired gain.*/   

    GAM.bufferHandle = DRV_SPI_BufferAddWrite2(GAM.spi_cont_pot, &GAM.v_adj,            /* Send the pot setting to the gain pot.*/
        sizeof(GAM.v_adj), SPI_2_EventHandler, NULL, &GAM.bufferHandle2 ); 
//    GAM.spi_sent_flag = true;                                                           /* Initialize flag to show we sent data to the SPI port.*/ 
}


/***************************************************************************************
 End of File
 */
