/*******************************************************************************
  MPLAB Harmony Application Source File
  NVM FAT Single Disk Demo Application
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.
    NVM FAT Single Disk Demo
  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call API
    routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware. However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any
    of the modules in the system or make any assumptions about when those
    functions are called. That is the responsibility of the
    configuration-specific system files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include <string.h>
#include "nvm_fs.h"
#include "switches.h"
#include "gamma.h"

/* This application showcases the File operations with NVM as the media. To
 * begin with the file system image contains a file called "FILE.TXT" with
 * 4-byte data "Data".
 * The application does the following:
 * 1. Mounts the file system present on the NVM media.
 * 2. Opens a file called "FILE.TXT" in READ PLUS mode.
 * 3. Retrieves the file stat information for the file.
 * 4. Gets the file size and compares it with the size information present in
 *    the file stat structure.
 * 5. Does a file seek to the end of the file.
 * 6. Checks if the EOF has reached.
 * 7. Sets the file pointer to the beginning of the file.
 * 8. Reads the 1 byte data and checks if the expected data is present in the
 *    file.
 * 9. Appends 1 byte of data to the file. Performs a file seek to the
 *    beginning of the appended data.
 * 10. Reads 1 byte and checks if the expected data is present in the file.
 * 11. If there is no error in any of the above steps then the application will
 *     go into Idle state.
 * 12. If there is an error then the application will go into Error state.
 * */

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************
/* This is the string that will written to the file */
//const uint8_t writeData[13] = "Hello World";


/* This string contains the original value of FILE.txt (before being written by
 * the demo */
//const uint8_t originalData[4] = "Data";
int32_t location = 0;


// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

NVM_FS_DATA nvmfsData;


// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void NVM_FS_Initialize ( void )
{
    /* Initialize the app state to wait for
     * media attach. */
    nvmfsData.state = NVM_FS_MOUNT_DISK;
//    writeData[0] = 0x01;
//    originalData[0] = 0x00;
//    appData.language_flag = false;
    SWITCH.STATUS_SW_flag = false;
    nvmfsData.data_saved_flag = false;
}

/******************************************************************************
  Function:
    void NVM_FS_Tasks ( void )

  Remarks:
    See prototype in nvm_fs.h.
 */

void NVM_FS_Tasks ( void )
{
    switch(nvmfsData.state)                                                             /* The application task state machine */
    {
        case NVM_FS_MOUNT_DISK:
            {
                if(SYS_FS_Mount("/dev/nvma1", "/mnt/myDrive", FAT, 0, NULL) != 0)
                {    
                    nvmfsData.state = NVM_FS_MOUNT_DISK;                                /* The disk could not be mounted. Try mounting again until*/
                }                                                                       /* mount is successful. */
                else
                {                    
                    nvmfsData.state = NVM_FS_OPEN_FILE;                                 /* Mount was successful. Open a file. */
                }
                break;
            }

        case NVM_FS_OPEN_FILE:
            {
                nvmfsData.fileHandle = SYS_FS_FileOpen("/mnt/myDrive/FILE.TXT", 
                                                        SYS_FS_FILE_OPEN_WRITE_PLUS);
                if(nvmfsData.fileHandle == SYS_FS_HANDLE_INVALID)
                {                   
                    nvmfsData.state = NVM_FS_ERROR;                                     /* Failed to open the file. */
                }
                else
                {                    
                    nvmfsData.state = NVM_FS_READ_FILE_STAT;                            /* Opened file successfully. Read the file stat. */
                }
                break;
            }

        case NVM_FS_READ_FILE_STAT:
            {
                if(SYS_FS_FileStat("/mnt/myDrive/FILE.TXT", &nvmfsData.fileStatus) == SYS_FS_RES_FAILURE)
                {                    
                    nvmfsData.state = NVM_FS_ERROR;                                     /* Failed to read the file stat. */
                }
                else
                {                    
                    nvmfsData.state = NVM_FS_READ_FILE_SIZE;                            /* Now find the size of the file using FileSize API. */
                }
                break;
            }

        case NVM_FS_READ_FILE_SIZE:
            {
                nvmfsData.fileSize = SYS_FS_FileSize(nvmfsData.fileHandle);
                if(nvmfsData.fileSize == -1)
                {                    
                    nvmfsData.state = NVM_FS_ERROR;                                     /* Failed to read the file size. */
                }
                else
                {
                    if(nvmfsData.fileSize == nvmfsData.fileStatus.fsize)
                    {
                        nvmfsData.state = NVM_FS_DO_FILE_SEEK;
                    }
                    else
                    {
                        nvmfsData.state = NVM_FS_ERROR;
                    }
                }
                break;
            }

        case NVM_FS_DO_FILE_SEEK:
            {
                if(SYS_FS_FileSeek(nvmfsData.fileHandle, nvmfsData.fileSize, 
                                                            SYS_FS_SEEK_SET) == -1)
                {                    
                    nvmfsData.state = NVM_FS_ERROR;                                     /* File seek caused an error */
                }
                else
                {                    
                    nvmfsData.state = NVM_FS_CHECK_EOF;                                 /* Check for End of file */
                }
                break;
            }

        case NVM_FS_CHECK_EOF:
            {
                if(SYS_FS_FileEOF(nvmfsData.fileHandle) == false )
                {                    
                    nvmfsData.state = NVM_FS_ERROR;                                     /* Either, EOF is not reached or there was an error. */
                }
                else
                {
                    nvmfsData.state = NVM_FS_DO_ANOTHER_FILE_SEEK;
                }
                break;
            }

        case NVM_FS_DO_ANOTHER_FILE_SEEK:
            {                
                if(SYS_FS_FileSeek(nvmfsData.fileHandle, 0, SYS_FS_SEEK_SET) == -1)     /* Move file pointer to beginning of the file. */
                {                    
                    nvmfsData.state = NVM_FS_ERROR;                                     /* File seek caused an error */
                }
                else
                {                    
                    nvmfsData.state = NVM_FS_READ_ORIGINAL_FILE_CONTENT;                /* Check for original file content */
                }
                break;
            }

        case NVM_FS_READ_ORIGINAL_FILE_CONTENT:
            {
                if(SYS_FS_FileRead(nvmfsData.fileHandle, (void *)nvmfsData.data, 1) == -1)
                {                    
                    SYS_FS_FileClose(nvmfsData.fileHandle);                             /* There was an error while reading the file. Close the*/
                    nvmfsData.state = NVM_FS_ERROR;                                     /* file and error out.*/
                }
                else
                {
                    SWITCH.NVM_SW_count = nvmfsData.data[0];                            /* Assign the NVM switch count the NVM data value.*/
                    if(SWITCH.NVM_SW_count != SWITCH.STATUS_SW_count)                   /* If the two switch counts are not the same,*/
                    {
                        SWITCH.STATUS_SW_count = nvmfsData.data[0];                     /* make the STATUS switch count the same as the NVM switch count.*/ 
                        SWITCH.STATUS_SW_flag = true;
                        GAM.state =  GAM_STATE_GAIN_ADJ;                                /* Set the GAMMA state to adjust the gain based on the switch setting.*/
                    }
                    
//                    if(memcmp(appData.data, originalData, 4) != 0)
//                    if(memcmp(nvmfsData.data, originalData, 1) != 0)
                    if(SWITCH.STATUS_SW_count > 9)                                      /* If the switch count is more than 9,*/
                    {
                        SWITCH.STATUS_SW_count =  0;                                    /* reset the value to 0.*/
                        /* The written and the read data don't match. */
                        nvmfsData.state = NVM_FS_ERROR;
                    }
                    else
                    {   
                        nvmfsData.state = NVM_FS_FINAL_FILE_SEEK;                       /* The test was successful. Move the file pointer to*/
                    }                                                                   /* the beginning of the file. */
                }
                break;
            }

        case NVM_FS_FINAL_FILE_SEEK:
            {
                location = SYS_FS_FileTell(nvmfsData.fileHandle);                       /* Move file pointer to beginning of file. */
                location = location;
                
//                if (SYS_FS_FileSeek(appData.fileHandle, 4, SYS_FS_SEEK_SET) == -1)
                if (SYS_FS_FileSeek(nvmfsData.fileHandle, 0, SYS_FS_SEEK_SET) == -1)    
                {                    
                    nvmfsData.state = NVM_FS_ERROR;                                     /* File seek caused an error */
                }
                else
                {
                    /* Do a file write now */
//                    nvmfsData.state = NVM_FS_WRITE_TO_FILE;
                    nvmfsData.state = NVM_FS_IDLE;
                }
                break;
            }

        case NVM_FS_WRITE_TO_FILE:
            {
                writeData[0] = SWITCH.STATUS_SW_count;
//                if(SYS_FS_FileWrite(appData.fileHandle, (const void *)writeData, 13) == -1)
                if(SYS_FS_FileWrite(nvmfsData.fileHandle, (const void *)writeData, 1) == -1)
                {
                    /* Write was not successful. Close the file and error
                     * out. */
                    SYS_FS_FileClose(nvmfsData.fileHandle);
                    nvmfsData.state = NVM_FS_ERROR;
                }
                else
                {
                    /* Flush the data to NVM. */
                    SYS_FS_FileSync(nvmfsData.fileHandle);
                    /* Write was successful. Read the file content. */
                    nvmfsData.state = NVM_FS_SEEK_TO_START;
                }
                break;
            }

        case NVM_FS_SEEK_TO_START:
            {
                location = SYS_FS_FileTell(nvmfsData.fileHandle);
                location = location;
//                if(SYS_FS_FileSeek(appData.fileHandle, 4, SYS_FS_SEEK_SET) == -1)
                if(SYS_FS_FileSeek(nvmfsData.fileHandle, 0, SYS_FS_SEEK_SET) == -1)
                {
                    /* Could not seek the file. Error out*/
                    nvmfsData.state = NVM_FS_ERROR;
                }
                else
                {
                    /* Read the file content */
                    nvmfsData.state = NVM_FS_READ_VERIFY_FILE;
                    location = SYS_FS_FileTell(nvmfsData.fileHandle);
                    location = location;
                }
                break;
            }

        case NVM_FS_READ_VERIFY_FILE:
            {
//                if(SYS_FS_FileRead(appData.fileHandle, (void *)appData.data, 13) == -1)
                if(SYS_FS_FileRead(nvmfsData.fileHandle, (void *)nvmfsData.data, 1) == -1)    
                {
                    /* There was an error while reading the file.
                     * Close the file and error out. */

                    SYS_FS_FileClose(nvmfsData.fileHandle);
                    nvmfsData.state = NVM_FS_ERROR;
                }
                else
                {
                    if(strcmp((const char *)nvmfsData.data, (const char *)writeData) != 0)
                    {
                        /* The written and the read data don't match. */
                        nvmfsData.state = NVM_FS_ERROR;
                    }
                    else
                    {
                        /* The test was successful. Lets idle. */
                        nvmfsData.state = NVM_FS_IDLE;
                        location = SYS_FS_FileTell(nvmfsData.fileHandle);
                        location = location;
                    }

//                    SYS_FS_FileClose(nvmfsData.fileHandle);
                }
                break;
            }

        case NVM_FS_IDLE:
            {
                if(SWITCH.STATUS_SW_count != nvmfsData.data[0])
                {
                    location = SYS_FS_FileTell(nvmfsData.fileHandle);
                    location = location;
                    if (SYS_FS_FileSeek(nvmfsData.fileHandle, 0, SYS_FS_SEEK_SET) == -1)
                    {
                        /* File seek caused an error */
                        nvmfsData.state = NVM_FS_ERROR;
                    }
                    else
                    {
                        /* Do a file write now */
                        nvmfsData.state = NVM_FS_WRITE_TO_FILE;
                        
                    }                
                }
                /* The application comes here when the demo has completed
                 * successfully. */
//                BSP_LEDOn(APP_SUCCESS_LED);
                break;
            }
        
        case NVS_FS_CLOSE:
        {
           if( SYS_FS_FileClose(nvmfsData.fileHandle) != SYS_FS_RES_SUCCESS)
           {
               nvmfsData.state = NVS_FS_CLOSE;
           }
           else
          
           {
               nvmfsData.state = NVS_FS_UNMOUNT;
           }
        }
        break;
        
        case NVS_FS_UNMOUNT:
        {
            if(SYS_FS_Unmount("/mnt/myDrive") !=  SYS_FS_RES_SUCCESS)                   /* Unmount the NVM disk.*/
            {
                nvmfsData.state = NVS_FS_UNMOUNT;
            }
            else
            {
                nvmfsData.data_saved_flag = true;
            }
            
        }
        break;

        case NVM_FS_ERROR:
        {
            /* The application comes here when the demo has failed. */
//                BSP_LEDOn(APP_FAILURE_LED);
            break;
        }

        default:
        {
            break;
        }
    }

} //End of APP_Tasks


/*******************************************************************************
 End of File
 */

