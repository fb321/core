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
// <editor-fold defaultstate="collapsed" desc="DRV_SPI Instance 0 Initialization Data">

/* SPI Client Objects Pool */
DRV_SPI_CLIENT_OBJ drvSPI0ClientObjPool[DRV_SPI_CLIENTS_NUMBER_IDX0] = {0};

/* SPI Transfer Objects Pool */
DRV_SPI_TRANSFER_OBJ drvSPI0TransferObjPool[DRV_SPI_QUEUE_SIZE_IDX0] = {0};

/* SPI PLIB Interface Initialization */
DRV_SPI_PLIB_INTERFACE drvSPI0PlibAPI = {

    /* SPI PLIB Setup */
    .setup = (DRV_SETUP)SERCOM1_SPI_TransferSetup,

    /* SPI PLIB WriteRead function */
    .writeRead = (DRV_WRITEREAD)SERCOM1_SPI_WriteRead,

    /* SPI PLIB Transfer Status function */
    .isBusy = (DRV_IS_BUSY)SERCOM1_SPI_IsBusy,

    /* SPI PLIB Callback Register */
    .callbackRegister = (DRV_CALLBACK_REGISTER)SERCOM1_SPI_CallbackRegister,
};



uint32_t drvSPI0remapDataBits[]= { 0x0, 0x1, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
uint32_t drvSPI0remapClockPolarity[] = { 0x0, 0x20000000 };
uint32_t drvSPI0remapClockPhase[] = { 0x10000000, 0x0 };

/* SPI Driver Initialization Data */
DRV_SPI_INIT drvSPI0InitData =
{
    /* SPI PLIB API */
    .spiPlib = &drvSPI0PlibAPI,

    .remapDataBits = drvSPI0remapDataBits,
    .remapClockPolarity = drvSPI0remapClockPolarity,
    .remapClockPhase = drvSPI0remapClockPhase,


    /* SPI Number of clients */
    .numClients = DRV_SPI_CLIENTS_NUMBER_IDX0,

    /* SPI Client Objects Pool */
    .clientObjPool = (uintptr_t)&drvSPI0ClientObjPool[0],

    /* DMA Channel for Transmit */
    .dmaChannelTransmit = DRV_SPI_XMIT_DMA_CH_IDX0,

    /* DMA Channel for Receive */
    .dmaChannelReceive  = DRV_SPI_RCV_DMA_CH_IDX0,

    /* SPI Transmit Register */
    .spiTransmitAddress =  (void *)&(SERCOM1_REGS->SPI.DATA),

    /* SPI Receive Register */
    .spiReceiveAddress  = (void *)&(SERCOM1_REGS->SPI.DATA),

    /* Interrupt source is DMA */
 
   .interruptSource = DMAC_IRQn,
 

    /* SPI Queue Size */
    .queueSize = DRV_SPI_QUEUE_SIZE_IDX0,

    /* SPI Transfer Objects Pool */
    .transferObjPool = (uintptr_t)&drvSPI0TransferObjPool[0],
};

// </editor-fold>
// <editor-fold defaultstate="collapsed" desc="DRV_SPI Instance 1 Initialization Data">

/* SPI Client Objects Pool */
DRV_SPI_CLIENT_OBJ drvSPI1ClientObjPool[DRV_SPI_CLIENTS_NUMBER_IDX1] = {0};

/* SPI Transfer Objects Pool */
DRV_SPI_TRANSFER_OBJ drvSPI1TransferObjPool[DRV_SPI_QUEUE_SIZE_IDX1] = {0};

/* SPI PLIB Interface Initialization */
DRV_SPI_PLIB_INTERFACE drvSPI1PlibAPI = {

    /* SPI PLIB Setup */
    .setup = (DRV_SETUP)SERCOM5_SPI_TransferSetup,

    /* SPI PLIB WriteRead function */
    .writeRead = (DRV_WRITEREAD)SERCOM5_SPI_WriteRead,

    /* SPI PLIB Transfer Status function */
    .isBusy = (DRV_IS_BUSY)SERCOM5_SPI_IsBusy,

    /* SPI PLIB Callback Register */
    .callbackRegister = (DRV_CALLBACK_REGISTER)SERCOM5_SPI_CallbackRegister,
};



uint32_t drvSPI1remapDataBits[]= { 0x0, 0x1, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
uint32_t drvSPI1remapClockPolarity[] = { 0x0, 0x20000000 };
uint32_t drvSPI1remapClockPhase[] = { 0x10000000, 0x0 };

/* SPI Driver Initialization Data */
DRV_SPI_INIT drvSPI1InitData =
{
    /* SPI PLIB API */
    .spiPlib = &drvSPI1PlibAPI,

    .remapDataBits = drvSPI1remapDataBits,
    .remapClockPolarity = drvSPI1remapClockPolarity,
    .remapClockPhase = drvSPI1remapClockPhase,


    /* SPI Number of clients */
    .numClients = DRV_SPI_CLIENTS_NUMBER_IDX1,

    /* SPI Client Objects Pool */
    .clientObjPool = (uintptr_t)&drvSPI1ClientObjPool[0],

    /* DMA Channel for Transmit */
    .dmaChannelTransmit = DRV_SPI_XMIT_DMA_CH_IDX1,

    /* DMA Channel for Receive */
    .dmaChannelReceive  = DRV_SPI_RCV_DMA_CH_IDX1,

    /* SPI Transmit Register */
    .spiTransmitAddress =  (void *)&(SERCOM5_REGS->SPI.DATA),

    /* SPI Receive Register */
    .spiReceiveAddress  = (void *)&(SERCOM5_REGS->SPI.DATA),

    /* Interrupt source is DMA */
 
   .interruptSource = DMAC_IRQn,
 

    /* SPI Queue Size */
    .queueSize = DRV_SPI_QUEUE_SIZE_IDX1,

    /* SPI Transfer Objects Pool */
    .transferObjPool = (uintptr_t)&drvSPI1TransferObjPool[0],
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
	SYSTICK_TimerInitialize();
    DMAC_Initialize();

	BSP_Initialize();
    EVSYS_Initialize();

    SERCOM1_SPI_Initialize();

    SERCOM5_SPI_Initialize();


    /* Initialize SPI0 Driver Instance */
    sysObj.drvSPI0 = DRV_SPI_Initialize(DRV_SPI_INDEX_0, (SYS_MODULE_INIT *)&drvSPI0InitData);
    /* Initialize SPI1 Driver Instance */
    sysObj.drvSPI1 = DRV_SPI_Initialize(DRV_SPI_INDEX_1, (SYS_MODULE_INIT *)&drvSPI1InitData);



    APP_MONITOR_Initialize();
    APP_INSTANCE1_Initialize();
    APP_INSTANCE2_Initialize();


}


/*******************************************************************************
 End of File
*/
