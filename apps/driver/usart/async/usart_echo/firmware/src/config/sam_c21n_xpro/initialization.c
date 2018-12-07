/*******************************************************************************
  System Initialization File

  File Name:
    initialization.c

  Summary:
    This file contains source code necessary to initialize the system.

  Description:
    This file contains source code necessary to initialize the system.  It
    implements the "SYS_Initialize" function, defines the configuration bits,
    and allocates any necessary global system resources,
 *******************************************************************************/

// DOM-IGNORE-BEGIN
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
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "configuration.h"
#include "definitions.h"


// ****************************************************************************
// ****************************************************************************
// Section: Configuration Bits
// ****************************************************************************
// ****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************
// <editor-fold defaultstate="collapsed" desc="DRV_USART Instance 0 Initialization Data">

const DRV_USART_PLIB_INTERFACE drvUsart0PlibAPI = {
        .readCallbackRegister = (DRV_USART_PLIB_READ_CALLBACK_REG)SERCOM4_USART_ReadCallbackRegister,
        .read = (DRV_USART_PLIB_READ)SERCOM4_USART_Read,
        .readIsBusy = (DRV_USART_PLIB_READ_IS_BUSY)SERCOM4_USART_ReadIsBusy,
        .readCountGet = (DRV_USART_PLIB_READ_COUNT_GET)SERCOM4_USART_ReadCountGet,
        .writeCallbackRegister = (DRV_USART_PLIB_WRITE_CALLBACK_REG)SERCOM4_USART_WriteCallbackRegister,
        .write = (DRV_USART_PLIB_WRITE)SERCOM4_USART_Write,
        .writeIsBusy = (DRV_USART_PLIB_WRITE_IS_BUSY)SERCOM4_USART_WriteIsBusy,
        .writeCountGet = (DRV_USART_PLIB_WRITE_COUNT_GET)SERCOM4_USART_WriteCountGet,
        .errorGet = (DRV_USART_PLIB_ERROR_GET)SERCOM4_USART_ErrorGet,
        .serialSetup = (DRV_USART_PLIB_SERIAL_SETUP)SERCOM4_USART_SerialSetup
};

const uint32_t drvUsart0remapDataWidth[] = { 0x5, 0x6, 0x7, 0x0, 0x1 };
const uint32_t drvUsart0remapParity[] = { 0x2, 0x80000, 0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
const uint32_t drvUsart0remapStopBits[] = { 0x0, 0xFFFFFFFF, 0x40 };
const uint32_t drvUsart0remapError[] = { 0x4, 0x0, 0x2 };
const DRV_USART_INIT drvUsart0InitData =
{
    .usartPlib = &drvUsart0PlibAPI,

    .remapDataWidth = drvUsart0remapDataWidth,

    .remapParity = drvUsart0remapParity,

    .remapStopBits = drvUsart0remapStopBits,

    .remapError = drvUsart0remapError,

    .dmaChannelTransmit = SYS_DMA_CHANNEL_NONE,

    .dmaChannelReceive = SYS_DMA_CHANNEL_NONE,


    .queueSizeTransmit = DRV_USART_XMIT_QUEUE_SIZE_IDX0,

    .queueSizeReceive = DRV_USART_RCV_QUEUE_SIZE_IDX0,

    .interruptUSART = SERCOM4_IRQn,

    .interruptDMA = DMAC_IRQn,


};

// </editor-fold>


// *****************************************************************************
// *****************************************************************************
// Section: System Data
// *****************************************************************************
// *****************************************************************************
/* Structure to hold the object handles for the modules in the system. */
SYSTEM_OBJECTS sysObj;
// *****************************************************************************
// *****************************************************************************
// Section: Library/Stack Initialization Data
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: System Initialization
// *****************************************************************************
// *****************************************************************************


/*******************************************************************************
  Function:
    void SYS_Initialize ( void *data )

  Summary:
    Initializes the board, services, drivers, application and other modules.

  Remarks:
 */

void SYS_Initialize ( void* data )
{
    PORT_Initialize();

    CLOCK_Initialize();



    NVIC_Initialize();
    SERCOM4_USART_Initialize();

	BSP_Initialize();

    sysObj.drvUsart0 = DRV_USART_Initialize(DRV_USART_INDEX_0, (SYS_MODULE_INIT *)&drvUsart0InitData);




    APP_Initialize();


}


/*******************************************************************************
 End of File
*/

