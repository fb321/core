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
#include "device.h"



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
// <editor-fold defaultstate="collapsed" desc="DRV_USART Instance 1 Initialization Data">

static DRV_USART_CLIENT_OBJ drvUSART1ClientObjPool[DRV_USART_CLIENTS_NUMBER_IDX1];


const DRV_USART_PLIB_INTERFACE drvUsart1PlibAPI = {
    .readCallbackRegister = (DRV_USART_PLIB_READ_CALLBACK_REG)DBGU_ReadCallbackRegister,
    .read = (DRV_USART_PLIB_READ)DBGU_Read,
    .readIsBusy = (DRV_USART_PLIB_READ_IS_BUSY)DBGU_ReadIsBusy,
    .readCountGet = (DRV_USART_PLIB_READ_COUNT_GET)DBGU_ReadCountGet,
    .writeCallbackRegister = (DRV_USART_PLIB_WRITE_CALLBACK_REG)DBGU_WriteCallbackRegister,
    .write = (DRV_USART_PLIB_WRITE)DBGU_Write,
    .writeIsBusy = (DRV_USART_PLIB_WRITE_IS_BUSY)DBGU_WriteIsBusy,
    .writeCountGet = (DRV_USART_PLIB_WRITE_COUNT_GET)DBGU_WriteCountGet,
    .errorGet = (DRV_USART_PLIB_ERROR_GET)DBGU_ErrorGet,
    .serialSetup = (DRV_USART_PLIB_SERIAL_SETUP)DBGU_SerialSetup
};

const uint32_t drvUsart1remapDataWidth[] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0xFFFFFFFF };
const uint32_t drvUsart1remapParity[] = { 0x800, 0x0, 0x200, 0x600, 0x400, 0xFFFFFFFF };
const uint32_t drvUsart1remapStopBits[] = { 0x0, 0xFFFFFFFF, 0xFFFFFFFF };
const uint32_t drvUsart1remapError[] = { 0x20, 0x80, 0x40 };

const DRV_USART_INIT drvUsart1InitData =
{
    .usartPlib = &drvUsart1PlibAPI,

    /* USART Number of clients */
    .numClients = DRV_USART_CLIENTS_NUMBER_IDX1,

    /* USART Client Objects Pool */
    .clientObjPool = (uintptr_t)&drvUSART1ClientObjPool[0],

    .dmaChannelTransmit = SYS_DMA_CHANNEL_NONE,

    .dmaChannelReceive = SYS_DMA_CHANNEL_NONE,


    .remapDataWidth = drvUsart1remapDataWidth,

    .remapParity = drvUsart1remapParity,

    .remapStopBits = drvUsart1remapStopBits,

    .remapError = drvUsart1remapError,
};

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="DRV_USART Instance 0 Initialization Data">

static DRV_USART_CLIENT_OBJ drvUSART0ClientObjPool[DRV_USART_CLIENTS_NUMBER_IDX0];


const DRV_USART_PLIB_INTERFACE drvUsart0PlibAPI = {
    .readCallbackRegister = (DRV_USART_PLIB_READ_CALLBACK_REG)FLEXCOM5_USART_ReadCallbackRegister,
    .read = (DRV_USART_PLIB_READ)FLEXCOM5_USART_Read,
    .readIsBusy = (DRV_USART_PLIB_READ_IS_BUSY)FLEXCOM5_USART_ReadIsBusy,
    .readCountGet = (DRV_USART_PLIB_READ_COUNT_GET)FLEXCOM5_USART_ReadCountGet,
    .writeCallbackRegister = (DRV_USART_PLIB_WRITE_CALLBACK_REG)FLEXCOM5_USART_WriteCallbackRegister,
    .write = (DRV_USART_PLIB_WRITE)FLEXCOM5_USART_Write,
    .writeIsBusy = (DRV_USART_PLIB_WRITE_IS_BUSY)FLEXCOM5_USART_WriteIsBusy,
    .writeCountGet = (DRV_USART_PLIB_WRITE_COUNT_GET)FLEXCOM5_USART_WriteCountGet,
    .errorGet = (DRV_USART_PLIB_ERROR_GET)FLEXCOM5_USART_ErrorGet,
    .serialSetup = (DRV_USART_PLIB_SERIAL_SETUP)FLEXCOM5_USART_SerialSetup
};

const uint32_t drvUsart0remapDataWidth[] = { 0x0, 0x40, 0x80, 0xC0, 0x20000 };
const uint32_t drvUsart0remapParity[] = { 0x800, 0x0, 0x200, 0x600, 0x400, 0xC00 };
const uint32_t drvUsart0remapStopBits[] = { 0x0, 0x1000, 0x2000 };
const uint32_t drvUsart0remapError[] = { 0x20, 0x80, 0x40 };

const DRV_USART_INIT drvUsart0InitData =
{
    .usartPlib = &drvUsart0PlibAPI,

    /* USART Number of clients */
    .numClients = DRV_USART_CLIENTS_NUMBER_IDX0,

    /* USART Client Objects Pool */
    .clientObjPool = (uintptr_t)&drvUSART0ClientObjPool[0],

    .dmaChannelTransmit = DRV_USART_XMIT_DMA_CH_IDX0,

    .usartTransmitAddress = (void *)&(FLEXCOM5_REGS->FLEX_US_THR),

    .dmaChannelReceive = DRV_USART_RCV_DMA_CH_IDX0,

    .usartReceiveAddress = (void *)&(FLEXCOM5_REGS->FLEX_US_RHR),


    .remapDataWidth = drvUsart0remapDataWidth,

    .remapParity = drvUsart0remapParity,

    .remapStopBits = drvUsart0remapStopBits,

    .remapError = drvUsart0remapError,
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
  
    CLK_Initialize();

	PIO_Initialize();

	BSP_Initialize();
	PIT_TimerInitialize();

MMU_Initialize();

    INT_Initialize();
    XDMAC_Initialize();

    FLEXCOM5_USART_Initialize();

    DBGU_Initialize();


    sysObj.drvUsart1 = DRV_USART_Initialize(DRV_USART_INDEX_1, (SYS_MODULE_INIT *)&drvUsart1InitData);

    sysObj.drvUsart0 = DRV_USART_Initialize(DRV_USART_INDEX_0, (SYS_MODULE_INIT *)&drvUsart0InitData);




    APP_USART_USB_CLICK_BOARD_Initialize();
    APP_USART_USB_DEBUG_PORT_Initialize();



}


/*******************************************************************************
 End of File
*/
