/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/
//DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
//DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include "definitions.h"
#include "user.h"
#include <string.h>         //included for memcpy(..)
// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************
#define AT24_EEPROM_MEM_ADDR             0x00
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

APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/
static void APP_EEPROM_EventHandler(DRV_AT24_TRANSFER_STATUS event, uintptr_t context)
{
    switch(event)
    {
        case DRV_AT24_TRANSFER_STATUS_COMPLETED:
            appData.isTransferDone = true;
            break;
        case DRV_AT24_TRANSFER_STATUS_ERROR:
        default:
            appData.isTransferDone = false;
            appData.state = APP_STATE_ERROR;
            break;
    }
}
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

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;

    appData.isTransferDone = false;

}

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
    uint32_t i;
    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:

            appData.drvHandle = DRV_AT24_Open(DRV_AT24_INDEX, DRV_IO_INTENT_READWRITE);

            if (appData.drvHandle != DRV_HANDLE_INVALID)
            {
                DRV_AT24_EventHandlerSet(appData.drvHandle, APP_EEPROM_EventHandler, 0);

                appData.state = APP_STATE_WRITE;
            }
            else
            {
                appData.state = APP_STATE_ERROR;
            }
            break;

        case APP_STATE_WRITE:

            /* Fill up the write buffer */
            for (i = 0; i < BUFFER_SIZE; i++)
            {
                appData.writeBuffer[i] = i;
            }

            /* Set the next state first as callback may be fired before the state 
             * is changed; potentially over-writing error state set from the callback */
            appData.state = APP_STATE_WAIT_WRITE_COMPLETE;

            if (DRV_AT24_Write(appData.drvHandle,
                    appData.writeBuffer,
                    BUFFER_SIZE,
                    AT24_EEPROM_MEM_ADDR) == false)
            {
                appData.state = APP_STATE_ERROR;
            }
            break;

        case APP_STATE_WAIT_WRITE_COMPLETE:

            if (appData.isTransferDone == true)
            {
                appData.isTransferDone = false;
                appData.state = APP_STATE_READ;
            }
            break;

        case APP_STATE_READ:

            appData.state = APP_STATE_WAIT_READ_COMPLETE;

            if (DRV_AT24_Read(appData.drvHandle,
                    appData.readBuffer,
                    BUFFER_SIZE,
                    AT24_EEPROM_MEM_ADDR) == false)
            {
                appData.state = APP_STATE_ERROR;
            }
            break;

        case APP_STATE_WAIT_READ_COMPLETE:

            if (appData.isTransferDone == true)
            {
                appData.isTransferDone = false;
                appData.state = APP_STATE_VERIFY;
            }
            break;

        case APP_STATE_VERIFY:

            if (memcmp(appData.writeBuffer, appData.readBuffer, BUFFER_SIZE ) == 0)
            {
                appData.state = APP_STATE_SUCCESS;
            }
            else
            {
                appData.state = APP_STATE_ERROR;
            }
            break;

        case APP_STATE_SUCCESS:
            /* Turn on the LED to indicate success */
            LED_ON();
            appData.state = APP_STATE_IDLE;
            break;                        

        case APP_STATE_ERROR:        
            LED_OFF();
            appData.state = APP_STATE_IDLE;
            break;
            
        case APP_STATE_IDLE:
        default:
            break;
    }
}


/*******************************************************************************
 End of File
 */
