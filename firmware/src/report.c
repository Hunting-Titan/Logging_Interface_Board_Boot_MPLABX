/**************************************************************************************/  
/** \file report.c

  Company:
    Hunting Titan

  File Name:
    report.c

  Summary:
    To populate data array for transmission back to host.

  Description:
    This function is used to populate and 24 byte data array.  The bytes contain the 
    firmware version, number of transmission counts, the encoder count, the tension
    transducer current in uA and the CCL voltage in mV.  The variables use four bytes 
    each.    
*/ 
/**************************************************************************************/

/**************************************************************************************/ 
/**************************************************************************************/ 
/* Section: Included Files                                                            */ 
/**************************************************************************************/ 
/**************************************************************************************/

#include "report.h"
#include "hid.h"
#include "../system_definitions.h"

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
    These are defined in report.h and hid.h
*/

DACQ_REPORT REPORT;
APP_DATA appData;

/**************************************************************************************/
/**************************************************************************************/
/* Section: Interface Functions                                                       */
/**************************************************************************************/
/**************************************************************************************/

/*!************************************************************************************* 
  Function:
    void DACQ_ReportCreate(void)

  Summary:
    This function creates the data array for transmission to the host.    

  Remarks:
    Refer to the report.h interface header for function usage details.
 */

void DACQ_ReportCreate( void )
{    
    appData.transmitDataBuffer[0] = 0x35;                                               /* Sanity check.  Two bytes. Constant values.*/ 
    appData.transmitDataBuffer[1] = 0xE6;
    appData.transmitDataBuffer[2] = 0x00;                                               /* Message format version.*/
    appData.transmitDataBuffer[3] = 0xC8;                                               /* The firmware revision number.*/
                                                                                        /* The two most significant bits represents the controller memory.*/
                                                                                        /* 1 equals 512, 2 equals 1024, 3 equals 2048. The remaining*/
                                                                                        /* six bits represent the code revision level.*/
    appData.transmitDataBuffer[4] = REPORT.data[4];                                     /* Transmission Count. Four bytes long.*/                                     
    appData.transmitDataBuffer[5] = REPORT.data[5];                                     
    appData.transmitDataBuffer[6] = REPORT.data[6];
    appData.transmitDataBuffer[7] = REPORT.data[7];                                     
    appData.transmitDataBuffer[8] = REPORT.data[8];                                     /* Command received from PC host.*/                                    
    appData.transmitDataBuffer[9] = REPORT.data[9];                                     /* Logging Panel status bits.*/                                     
    appData.transmitDataBuffer[10] = REPORT.data[10];                                   /* Number of data bytes for a given tool or command.*/
    appData.transmitDataBuffer[11] = REPORT.data[11];                                   /* GAMMA counts for Gamma/CCL; Ch.1 CCL for GPT; Frame ID for HS.*/
    appData.transmitDataBuffer[12] = REPORT.data[12];                                   
    appData.transmitDataBuffer[13] = REPORT.data[13];                                   /* Ch.2 Gamma Ray for GPT; Tool ID or Line V for HS.*/
    appData.transmitDataBuffer[14] = REPORT.data[14];
    appData.transmitDataBuffer[15] = REPORT.data[15];                                   /* Gamma gain for Gamma/CCL; Ch.3 Temp. for GPT; FW Ver. or Int. Temp. for HS.*/
    appData.transmitDataBuffer[16] = REPORT.data[16];                                   
    appData.transmitDataBuffer[17] = REPORT.data[17];                                   
    appData.transmitDataBuffer[18] = REPORT.data[18];                                   
    appData.transmitDataBuffer[19] = REPORT.data[19];                                   /*  */
    appData.transmitDataBuffer[20] = REPORT.data[20];                                   
    appData.transmitDataBuffer[21] = REPORT.data[21];                                   
    appData.transmitDataBuffer[22] = REPORT.data[22];                                   
    appData.transmitDataBuffer[23] = REPORT.data[23];                                   /* */
    appData.transmitDataBuffer[24] = REPORT.data[24];                                   
    appData.transmitDataBuffer[25] = REPORT.data[25];
    appData.transmitDataBuffer[26] = REPORT.data[26];
    appData.transmitDataBuffer[27] = REPORT.data[27];
    appData.transmitDataBuffer[28] = REPORT.data[28];                                   
    appData.transmitDataBuffer[29] = REPORT.data[29];
    appData.transmitDataBuffer[30] = REPORT.data[30];
    appData.transmitDataBuffer[31] = REPORT.data[31];
    appData.transmitDataBuffer[32] = REPORT.data[32];                                   
    appData.transmitDataBuffer[33] = REPORT.data[33];
    appData.transmitDataBuffer[34] = REPORT.data[34];
    appData.transmitDataBuffer[35] = REPORT.data[35];                                  
    appData.transmitDataBuffer[36] = REPORT.data[36];                                   
    appData.transmitDataBuffer[37] = REPORT.data[37];
    appData.transmitDataBuffer[38] = REPORT.data[38];
    appData.transmitDataBuffer[39] = REPORT.data[39];
    appData.transmitDataBuffer[40] = REPORT.data[40];
    appData.transmitDataBuffer[41] = REPORT.data[41];
    appData.transmitDataBuffer[42] = REPORT.data[42];    
    appData.transmitDataBuffer[43] = REPORT.data[43];
    appData.transmitDataBuffer[44] = REPORT.data[44];
    appData.transmitDataBuffer[45] = REPORT.data[45];
    appData.transmitDataBuffer[46] = REPORT.data[46];
    appData.transmitDataBuffer[47] = REPORT.data[47];
    appData.transmitDataBuffer[48] = REPORT.data[48];
    appData.transmitDataBuffer[49] = REPORT.data[49];
    appData.transmitDataBuffer[50] = REPORT.data[50];
    appData.transmitDataBuffer[51] = REPORT.data[51];
    appData.transmitDataBuffer[52] = REPORT.data[52];
    appData.transmitDataBuffer[53] = REPORT.data[53];
    appData.transmitDataBuffer[54] = REPORT.data[54];
    appData.transmitDataBuffer[55] = REPORT.data[55];
    
    
	return;	
}
/***************************************************************************************
 End of File
 */
