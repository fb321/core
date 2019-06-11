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
// <editor-fold defaultstate="collapsed" desc="DRV_MX25L Initialization Data">

const DRV_MX25L_PLIB_INTERFACE drvMX25LPlibAPI = {
    .CommandWrite  = QSPI0_CommandWrite,
    .RegisterRead  = QSPI0_RegisterRead,
    .RegisterWrite = QSPI0_RegisterWrite,
    .MemoryRead    = QSPI0_MemoryRead,
    .MemoryWrite   = QSPI0_MemoryWrite
};

const DRV_MX25L_INIT drvMX25LInitData =
{
    .mx25lPlib         = &drvMX25LPlibAPI,
};

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="DRV_MEMORY Instance 1 Initialization Data">

static uint8_t gDrvMemory1EraseBuffer[DRV_AT25DF_ERASE_BUFFER_SIZE] CACHE_ALIGN;

static DRV_MEMORY_CLIENT_OBJECT gDrvMemory1ClientObject[DRV_MEMORY_CLIENTS_NUMBER_IDX1];

static DRV_MEMORY_BUFFER_OBJECT gDrvMemory1BufferObject[DRV_MEMORY_BUFFER_QUEUE_SIZE_IDX1];

const DRV_MEMORY_DEVICE_INTERFACE drvMemory1DeviceAPI = {
    .Open               = DRV_AT25DF_Open,
    .Close              = DRV_AT25DF_Close,
    .Status             = DRV_AT25DF_Status,
    .SectorErase        = DRV_AT25DF_SectorErase,
    .Read               = DRV_AT25DF_Read,
    .PageWrite          = DRV_AT25DF_PageWrite,
    .EventHandlerSet    = NULL,
    .GeometryGet        = (DRV_MEMORY_DEVICE_GEOMETRY_GET)DRV_AT25DF_GeometryGet,
    .TransferStatusGet  = (DRV_MEMORY_DEVICE_TRANSFER_STATUS_GET)DRV_AT25DF_TransferStatusGet
};

const DRV_MEMORY_INIT drvMemory1InitData =
{
    .memDevIndex                = DRV_AT25DF_INDEX,
    .memoryDevice               = &drvMemory1DeviceAPI,
    .isMemDevInterruptEnabled   = false,
    .isFsEnabled                = false,
    .ewBuffer                   = &gDrvMemory1EraseBuffer[0],
    .clientObjPool              = (uintptr_t)&gDrvMemory1ClientObject[0],
    .bufferObj                  = (uintptr_t)&gDrvMemory1BufferObject[0],
    .queueSize                  = DRV_MEMORY_BUFFER_QUEUE_SIZE_IDX1,
    .nClientsMax                = DRV_MEMORY_CLIENTS_NUMBER_IDX1
};

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="DRV_MEMORY Instance 0 Initialization Data">

static uint8_t gDrvMemory0EraseBuffer[DRV_MX25L_ERASE_BUFFER_SIZE] CACHE_ALIGN;

static DRV_MEMORY_CLIENT_OBJECT gDrvMemory0ClientObject[DRV_MEMORY_CLIENTS_NUMBER_IDX0];

static DRV_MEMORY_BUFFER_OBJECT gDrvMemory0BufferObject[DRV_MEMORY_BUFFER_QUEUE_SIZE_IDX0];

const DRV_MEMORY_DEVICE_INTERFACE drvMemory0DeviceAPI = {
    .Open               = DRV_MX25L_Open,
    .Close              = DRV_MX25L_Close,
    .Status             = DRV_MX25L_Status,
    .SectorErase        = DRV_MX25L_SectorErase,
    .Read               = DRV_MX25L_Read,
    .PageWrite          = DRV_MX25L_PageWrite,
    .EventHandlerSet    = NULL,
    .GeometryGet        = (DRV_MEMORY_DEVICE_GEOMETRY_GET)DRV_MX25L_GeometryGet,
    .TransferStatusGet  = (DRV_MEMORY_DEVICE_TRANSFER_STATUS_GET)DRV_MX25L_TransferStatusGet
};

const DRV_MEMORY_INIT drvMemory0InitData =
{
    .memDevIndex                = DRV_MX25L_INDEX,
    .memoryDevice               = &drvMemory0DeviceAPI,
    .isMemDevInterruptEnabled   = false,
    .isFsEnabled                = false,
    .ewBuffer                   = &gDrvMemory0EraseBuffer[0],
    .clientObjPool              = (uintptr_t)&gDrvMemory0ClientObject[0],
    .bufferObj                  = (uintptr_t)&gDrvMemory0BufferObject[0],
    .queueSize                  = DRV_MEMORY_BUFFER_QUEUE_SIZE_IDX0,
    .nClientsMax                = DRV_MEMORY_CLIENTS_NUMBER_IDX0
};

// </editor-fold>
/* SPI PLIB Interface Initialization for AT25DF Driver */
const DRV_AT25DF_PLIB_INTERFACE drvAT25DFPlibAPI = {

    /* SPI PLIB WriteRead function */
    .writeRead = (DRV_AT25DF_PLIB_WRITE_READ)SPI0_WriteRead,

    /* SPI PLIB Write function */
    .write = (DRV_AT25DF_PLIB_WRITE)SPI0_Write,

    /* SPI PLIB Read function */
    .read = (DRV_AT25DF_PLIB_READ)SPI0_Read,

    /* SPI PLIB Transfer Status function */
    .isBusy = (DRV_AT25DF_PLIB_IS_BUSY)SPI0_IsBusy,

    /* SPI PLIB Callback Register */
    .callbackRegister = (DRV_AT25DF_PLIB_CALLBACK_REGISTER)SPI0_CallbackRegister,
};

/* AT25DF Driver Initialization Data */
const DRV_AT25DF_INIT drvAT25DFInitData =
{
    /* SPI PLIB API  interface*/
    .spiPlib = &drvAT25DFPlibAPI,

    /* AT25DF Number of clients */
    .numClients = DRV_AT25DF_CLIENTS_NUMBER_IDX,

    /* FLASH Page Size in bytes */
    .pageSize = DRV_AT25DF_PAGE_SIZE,

    /* Total size of the FLASH in bytes */
    .flashSize = DRV_AT25DF_FLASH_SIZE,

    .blockStartAddress = 0x0,

    .chipSelectPin = DRV_AT25DF_CHIP_SELECT_PIN_IDX
};



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
// <editor-fold defaultstate="collapsed" desc="SYS_TIME Initialization Data">

const SYS_TIME_PLIB_INTERFACE sysTimePlibAPI = {
    .timerCallbackSet = (SYS_TIME_PLIB_CALLBACK_REGISTER)TC0_CH0_TimerCallbackRegister,
    .timerCounterGet = (SYS_TIME_PLIB_COUNTER_GET)TC0_CH0_TimerCounterGet,
    .timerPeriodSet = (SYS_TIME_PLIB_PERIOD_SET)TC0_CH0_TimerPeriodSet,
    .timerFrequencyGet = (SYS_TIME_PLIB_FREQUENCY_GET)TC0_CH0_TimerFrequencyGet,
    .timerCompareSet = (SYS_TIME_PLIB_COMPARE_SET)TC0_CH0_TimerCompareSet,
    .timerStart = (SYS_TIME_PLIB_START)TC0_CH0_TimerStart,
    .timerStop = (SYS_TIME_PLIB_STOP)TC0_CH0_TimerStop 
};

const SYS_TIME_INIT sysTimeInitData =
{
    .timePlib = &sysTimePlibAPI,
    .hwTimerIntNum = TC0_IRQn,
};

// </editor-fold>



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

	PIT_TimerInitialize();

    MMU_Initialize();
    Matrix_Initialize();

    INT_Initialize();
	WDT_REGS->WDT_MR = WDT_MR_WDDIS_Msk; 		// Disable WDT 

  

 
    TC0_CH0_TimerInitialize(); 
     
    
	BSP_Initialize();
    QSPI0_Initialize();

	SPI0_Initialize();


    sysObj.drvMX25L = DRV_MX25L_Initialize((SYS_MODULE_INDEX)DRV_MX25L_INDEX, (SYS_MODULE_INIT *)&drvMX25LInitData);

    sysObj.drvMemory1 = DRV_MEMORY_Initialize((SYS_MODULE_INDEX)DRV_MEMORY_INDEX_1, (SYS_MODULE_INIT *)&drvMemory1InitData);

    sysObj.drvMemory0 = DRV_MEMORY_Initialize((SYS_MODULE_INDEX)DRV_MEMORY_INDEX_0, (SYS_MODULE_INIT *)&drvMemory0InitData);

    sysObj.drvAT25DF = DRV_AT25DF_Initialize(DRV_AT25DF_INDEX, (SYS_MODULE_INIT *)&drvAT25DFInitData);


    sysObj.sysTime = SYS_TIME_Initialize(SYS_TIME_INDEX_0, (SYS_MODULE_INIT *)&sysTimeInitData);


    APP_MX25L_Initialize();
    APP_AT25DF_Initialize();
    APP_MONITOR_Initialize();



}


/*******************************************************************************
 End of File
*/
