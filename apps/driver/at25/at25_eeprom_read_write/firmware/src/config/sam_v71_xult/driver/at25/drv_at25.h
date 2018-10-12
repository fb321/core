/*******************************************************************************
  DRV_AT25 Driver Interface Definition

  Company:
    Microchip Technology Inc.

  File Name:
    drv_at25.h

  Summary:
    AT25 EEPROM Library Interface header.

  Description:
    The AT25 Driver Library provides a interface to access the AT25 external
    EEPROM.
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

#ifndef _DRV_AT25_H
#define _DRV_AT25_H

// *****************************************************************************
// *****************************************************************************
// Section: File includes
// *****************************************************************************
// *****************************************************************************

#include <stdio.h>
#include <stdbool.h>
#include "driver/driver.h"
#include "system/system.h"
#include "drv_at25_definitions.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
    extern "C" {
#endif

// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* DRV_AT25 Transfer Status

 Summary:
    Defines the data type for AT25 Driver transfer status.

 Description:
    This will be used to indicate the current transfer status of the
    AT25 EEPROM driver operations.

 Remarks:
    None.
*/

typedef enum
{
    /* Transfer is being processed */
    DRV_AT25_TRANSFER_STATUS_BUSY,

    /* Transfer is successfully completed*/
    DRV_AT25_TRANSFER_STATUS_COMPLETED,

    /* Transfer had error or first transfer request is not made */
    DRV_AT25_TRANSFER_STATUS_ERROR

} DRV_AT25_TRANSFER_STATUS;

// *****************************************************************************
/* DRV_AT25 Geometry data

 Summary:
    Defines the data type for AT25 EEPROM Geometry details.

 Description:
    This will be used to get the geometry details of the attached AT25 EEPROM
    device.

 Remarks:
    None.
*/

typedef struct
{
    uint32_t readBlockSize;
    uint32_t readNumBlocks;
    uint32_t readNumRegions;

    uint32_t writeBlockSize;
    uint32_t writeNumBlocks;
    uint32_t writeNumRegions;

    uint32_t eraseBlockSize;
    uint32_t eraseNumBlocks;
    uint32_t eraseNumRegions;

    uint32_t blockStartAddress;

} DRV_AT25_GEOMETRY;

// *****************************************************************************
// *****************************************************************************
// Section: DRV_AT25 Driver Module Interface Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* AT25 Driver Transfer Event Handler Function Pointer

   Summary
    Pointer to a AT25 Driver Event handler function

   Description
    This data type defines the required function signature for the AT25 driver
    event handling callback function. A client must register a pointer
    using the event handling function whose function signature (parameter
    and return value types) match the types specified by this function pointer
    in order to receive transfer related event calls back from the driver.

    The parameters and return values are described here and
    a partial example implementation is provided.

  Parameters:
    event - Identifies the type of event   

    context - Value identifying the context of the application that 
    registered the event handling function.

  Returns:
    None.

  Example:
    <code>
    void APP_MyTransferEventHandler( DRV_AT25_TRANSFER_STATUS event,
                                   uintptr_t context )
    {
        MY_APP_DATA_STRUCT pAppData = (MY_APP_DATA_STRUCT) context;

        switch(event)
        {
            case DRV_AT25_TRANSFER_STATUS_COMPLETED:

                // Handle the transfer complete event.
                break;

            case DRV_AT25_TRANSFER_STATUS_ERROR:
            default:

                // Handle error.
                break;
        }
    }
    </code>

  Remarks:
    If the event is DRV_AT25_TRANSFER_STATUS_COMPLETED, it means that the data was
    transferred successfully.

    If the event is DRV_AT25_TRANSFER_STATUS_ERROR, it means that the data was not
    transferred successfully.   

    The context parameter contains the a handle to the client context,
    provided at the time the event handling function was registered using the
    DRV_AT25_EventHandlerSet function.  This context handle value is
    passed back to the client as the "context" parameter.  It can be any value
    necessary to identify the client context or instance (such as a pointer to
    the client's data) instance of the client that made the buffer add request.

    The event handler function executes in the driver's interrupt
    context. It is recommended of the application to not perform process 
    intensive or blocking operations with in this function.

    The DRV_AT25_Read, DRV_AT25_Write and DRV_AT25_PageWrite functions can be 
    called in the event handler to submit a request to the driver. 
*/

typedef void ( *DRV_AT25_EVENT_HANDLER )( DRV_AT25_TRANSFER_STATUS event, uintptr_t context );
// *****************************************************************************
/* Function:
    void DRV_AT25_Initialize( void );

  Summary:
    Initializes the AT25 EEPROM device

  Description:
    This routine initializes the AT25 EEPROM device driver making it ready for
    clients to open and use. The initialization data is specified by the init
    parameter. It is a single instance driver, so this API should be called
    only once.

  Precondition:
    None.

  Parameters:
    index - Identifier for the instance to be initialized

    init  - Pointer to the init data structure containing any data necessary to
            initialize the driver.

  Returns:
    If successful, returns a valid handle to a driver instance object.
    Otherwise, returns SYS_MODULE_OBJ_INVALID.

  Example:
    <code>
    SYS_MODULE_OBJ   sysObjDrvAT250;

    DRV_AT25_PLIB_INTERFACE drvAT250PlibAPI = {
        .writeRead = (DRV_AT25_WRITEREAD)SPI0_WriteRead,
        .write = (DRV_AT25_WRITE)SPI0_Write,
        .read = (DRV_AT25_READ)SPI0_Read,
        .isBusy = (DRV_AT25_IS_BUSY)SPI0_IsBusy,
        .callbackRegister = (DRV_AT25_CALLBACK_REGISTER)SPI0_CallbackRegister,
    };

    DRV_AT25_INIT drvAT250InitData =
    {
        .spiPlib = &drvAT250PlibAPI,
        .numClients = DRV_AT25_CLIENTS_NUMBER_IDX,
        .pageSize = DRV_AT25_EEPROM_PAGE_SIZE,
        .flashSize = DRV_AT25_EEPROM_FLASH_SIZE,
        .blockStartAddress =    0x0,
        .chipSelectPin = SYS_PORT_PIN_PA5,
        .holdPin = SYS_PORT_PIN_PA0,
        .writeProtectPin = SYS_PORT_PIN_PD11,
    };

    sysObjDrvAT250 = DRV_AT25_Initialize(DRV_AT25_INDEX_0, (SYS_MODULE_INIT *)&drvAT250InitData);

    </code>

  Remarks:
    This routine must be called before any other DRV_AT25 routine is called.
    This routine should only be called once during system initialization.
    This routine will block for hardware access.
*/

SYS_MODULE_OBJ DRV_AT25_Initialize( const SYS_MODULE_INDEX drvIndex, const SYS_MODULE_INIT * const init);

// *************************************************************************
/* Function:
    SYS_STATUS DRV_AT25_Status( const SYS_MODULE_INDEX drvIndex );

  Summary:
    Gets the current status of the AT25 driver module.

  Description:
    This routine provides the current status of the AT25 driver module.

  Preconditions:
    Function DRV_AT25_Initialize should have been called before calling
    this function.

  Parameters:
    drvIndex   -  Identifier for the instance used to initialize driver

  Returns:
    SYS_STATUS_READY - Indicates that the driver is ready and accept
                       requests for new operations.

    SYS_STATUS_UNINITIALIZED - Indicates the driver is not initialized.

  Example:
    <code>
    SYS_STATUS          Status;

    Status = DRV_AT25_Status(DRV_AT25_INDEX);
    </code>

  Remarks:
    This routine will NEVER block waiting for hardware.
*/

SYS_STATUS DRV_AT25_Status( const SYS_MODULE_INDEX drvIndex );

// *****************************************************************************
/* Function:
    DRV_HANDLE DRV_AT25_Open
    (
        const SYS_MODULE_INDEX drvIndex,
        const DRV_IO_INTENT ioIntent
    )

  Summary:
    Opens the specified AT25 driver instance and returns a handle to it.

  Description:
    This routine opens the specified AT25 driver instance and provides a
    handle that must be provided to all other client-level operations to
    identify the caller and the instance of the driver. The ioIntent
    parameter defines how the client interacts with this driver instance.

    This driver is a single client driver, so DRV_AT25_Open API should be
    called only once until driver is closed.

  Precondition:
    Function DRV_AT25_Initialize must have been called before calling this
    function.

  Parameters:
    drvIndex  - Identifier for the object instance to be opened

    intent -    Zero or more of the values from the enumeration DRV_IO_INTENT
                "ORed" together to indicate the intended use of the driver.

  Returns:
    If successful, the routine returns a valid open-instance handle (a number
    identifying both the caller and the module instance).

    If an error occurs, the return value is DRV_HANDLE_INVALID. Error can occur
    - if the  driver has been already opened once and in use.
    - if the driver peripheral instance being opened is not initialized or is
      invalid.

  Example:
    <code>
    DRV_HANDLE handle;

    handle = DRV_AT25_Open(DRV_AT25_INDEX_0, DRV_IO_INTENT_READWRITE);
    if (handle == DRV_HANDLE_INVALID)
    {
        // Unable to open the driver
        // May be the driver is not initialized
    }
    </code>

  Remarks:
    The handle returned is valid until the DRV_AT25_Close routine is called.
    This routine will NEVER block waiting for hardware.
*/
DRV_HANDLE DRV_AT25_Open(const SYS_MODULE_INDEX drvIndex, const DRV_IO_INTENT ioIntent);

// *****************************************************************************
/* Function:
    void DRV_AT25_Close( DRV_Handle handle )

  Summary:
    Closes opened-instance of the AT25 driver.

  Description:
    This routine closes opened-instance of the AT25 driver, invalidating the
    handle. A new handle must be obtained by calling DRV_AT25_Open
    before the caller may use the driver again.

  Precondition:
    DRV_AT25_Open must have been called to obtain a valid opened device handle.

  Parameters:
    handle -    A valid open-instance handle, returned from the driver's
                open routine

  Returns:
    None.

  Example:
    <code>
    // 'handle', returned from the DRV_AT25_Open

    DRV_AT25_Close(handle);

    </code>

  Remarks:
    None.
*/
void DRV_AT25_Close(const DRV_HANDLE handle);

// *****************************************************************************
/* Function:
    bool DRV_AT25_Read(const DRV_HANDLE handle, void *rxData, uint32_t rxDataLength, uint32_t address );

  Summary:
    Reads 'n' bytes of data from the specified start address of EEPROM.

  Description:
    This function schedules a non-blocking read operation for requested number
    of data bytes from given address of EEPROM.

    The requesting client should call DRV_AT25_TransferStatusGet() API to know
    the current status of the request.

  Precondition:
    DRV_AT25_Open must have been called to obtain a valid opened device handle.

  Parameters:
    handle         - A valid open-instance handle, returned from the driver's
                      open routine
    *rxData        - Buffer pointer into which the data read from the DRV_AT25
                      Flash memory will be placed.

    rxDataLength   - Total number of bytes to be read.

    address        - Read memory start address from where the data should be
                      read.

  Returns:
    false
    - if handle is invalid
    - if the pointer to the receive buffer is NULL or number of bytes to read is 0
    - if the driver is busy handling another transfer request

    true
    - if the read request is accepted.

  Example:
    <code>

    #define BUFFER_SIZE  1024
    #define MEM_ADDRESS  0x0

    uint8_t readBuffer[BUFFER_SIZE];

    // myHandle is the handle returned from DRV_AT25_Open API.
    if (true != DRV_AT25_Read(myHandle, readBuffer, BUFFER_SIZE, MEM_ADDRESS))
    {
        // Error handling here
    }

    </code>

  Remarks:
    None.
*/

bool DRV_AT25_Read(const DRV_HANDLE handle, void *rxData, uint32_t rxDataLength, uint32_t address );

// *****************************************************************************
/* Function:
    bool DRV_AT25_Write(const DRV_HANDLE handle, uint32_t *txData, uint32_t txDataLength, uint32_t address);

  Summary:
    Writes 'n' bytes of data starting at the specified address.

  Description:
    This function schedules a non-blocking write operation for writing
    txDataLength bytes of data starting from given address of EEPROM.

    The requesting client should call DRV_AT25_TransferStatusGet() API to know
    the current status of the request.

  Preconditions:
    DRV_AT25_Open must have been called to obtain a valid opened device handle.

  Parameters:
    handle         - A valid open-instance handle, returned from the driver's
                      open routine
    *txData        - The source buffer containing data to be programmed into AT25
                      EEPROM

    txDataLength   - Total number of bytes to be written.

    address        - Write memory start address from where the data should be
                      written

  Returns:
    false
    - if handle is invalid
    - if the pointer to transmit buffer is NULL or number of bytes to write is 0
    - if the driver is busy handling another transfer request

    true
    - if the write request is successfully accepted.

  Example:
    <code>

    #define PAGE_SIZE    256
    #define BUFFER_SIZE  1024
    #define MEM_ADDRESS  0x0

    uint8_t writeBuffer[BUFFER_SIZE];

    // myHandle is the handle returned from DRV_AT25_Open API.

    if (true != DRV_AT25_Write(myHandle, writeBuffer, BUFFER_SIZE, MEM_ADDRESS))
    {
        // Error handling here
    }
    else
    {
        // Wait for write to be completed
        while(DRV_AT25_TRANSFER_STATUS_BUSY == DRV_AT25_TransferStatusGet(myHandle));
    }
    </code>

  Remarks:
    None.
*/

bool DRV_AT25_Write(const DRV_HANDLE handle, void *txData, uint32_t txDataLength, uint32_t address );

// *****************************************************************************
/* Function:
    bool DRV_AT25_PageWrite(const DRV_HANDLE handle, uint32_t *txData, uint32_t address);

  Summary:
    Writes one page of data starting at the specified address.

  Description:
    This function schedules a non-blocking write operation for writing
    one page of data starting from given address of EEPROM.

    The requesting client should call DRV_AT25_TransferStatusGet() API to know
    the current status of the request.

  Preconditions:
    DRV_AT25_Open must have been called to obtain a valid opened device handle.

    "address" provided must be page boundary aligned in order to avoid
    overwriting the data in the beginning of the page.

  Parameters:
    handle         - A valid open-instance handle, returned from the driver's
                      open routine
    *txData        - The source buffer containing data to be written to the AT25
                      EEPROM
    address        - Write memory start address from where the data should be
                      written.
                     It must be page boundary aligned in order to avoid overwriting
                      the data in the beginning of the page.

  Returns:
    false
    - if handle is invalid
    - if the pointer to the transmit data is NULL
    - if the driver is busy handling another transfer request

    true
    - if the write request is successfully accepted.

  Example:
    <code>

    #define PAGE_SIZE  256
    #define MEM_ADDRESS  0x0

    uint8_t writeBuffer[PAGE_SIZE];

    // myHandle is the handle returned from DRV_AT25_Open API.

    if (true != DRV_AT25_PageWrite(myHandle, writeBuffer, MEM_ADDRESS))
    {
        // Error handling here
    }
    else
    {
        // Wait for write to be completed
        while(DRV_AT25_TRANSFER_STATUS_BUSY == DRV_AT25_TransferStatusGet(myHandle));
    }
    </code>

  Remarks:
    None.
*/

bool DRV_AT25_PageWrite(const DRV_HANDLE handle, void *txData, uint32_t address );

// *****************************************************************************
/* Function:
    DRV_AT25_TRANSFER_STATUS DRV_AT25_TransferStatusGet(const DRV_HANDLE handle);

  Summary:
    Gets the current status of the transfer request.

  Description:
    This routine gets the current status of the transfer request.

  Preconditions:
    DRV_AT25_PageWrite or DRV_AT25_Read must have been called to obtain the
    status of transfer.

  Parameters:
    handle      - A valid open-instance handle, returned from the driver's
                   open routine

  Returns:
    One of the status element from the enum DRV_AT25_TRANSFER_STATUS.

  Example:
    <code>
    // myHandle is the handle returned from DRV_AT25_Open API.

    if (DRV_AT25_TRANSFER_STATUS_COMPLETED == DRV_AT25_TransferStatusGet(myHandle))
    {
        // Operation Done
    }
    </code>

  Remarks:
    None.
*/

DRV_AT25_TRANSFER_STATUS DRV_AT25_TransferStatusGet(const DRV_HANDLE handle);

// *****************************************************************************
/* Function:
    bool DRV_AT25_GeometryGet(const DRV_HANDLE handle, DRV_AT25_GEOMETRY *geometry);

  Summary:
    Returns the geometry of the device.

  Description:
    This API gives the following geometrical details of the DRV_AT25 Flash:
    - Number of Read/Write/Erase Blocks and their size in each region of the device

  Precondition:
    DRV_AT25_Open must have been called to obtain a valid opened device handle.

  Parameters:
    handle      - A valid open-instance handle, returned from the driver's
                   open routine
    *geometry   - pointer to flash device geometry table instance

  Returns:
    false
    - if handle is invalid

    true
    - if able to get the geometry details of the flash

  Example:
    <code>

    DRV_AT25_GEOMETRY eepromGeometry;
    uint32_t readBlockSize, writeBlockSize, eraseBlockSize;
    uint32_t nReadBlocks, nReadRegions, totalFlashSize;

    // myHandle is the handle returned from DRV_AT25_Open API.

    DRV_AT25_GeometryGet(myHandle, &eepromGeometry);

    readBlockSize  = eepromGeometry.readBlockSize;
    nReadBlocks = eepromGeometry.readNumBlocks;
    nReadRegions = eepromGeometry.readNumRegions;

    writeBlockSize  = eepromGeometry.writeBlockSize;
    eraseBlockSize  = eepromGeometry.eraseBlockSize;

    totalFlashSize = readBlockSize * nReadBlocks * nReadRegions;

    </code>

  Remarks:
    None.
*/

bool DRV_AT25_GeometryGet(const DRV_HANDLE handle, DRV_AT25_GEOMETRY *geometry);

// *****************************************************************************
/* Function:
    void DRV_AT25_EventHandlerSet( 
        const DRV_HANDLE handle, 
        const DRV_AT25_EVENT_HANDLER eventHandler, 
        const uintptr_t context 
    )

  Summary:
    Allows a client to identify a transfer event handling function for the driver
    to call back when the requested transfer has finished.

  Description:
    This function allows a client to register a transfer event handling function
    with the driver to call back when the requested transfer has finished.    

    The event handler should be set before the client submits any transfer
    requests that could generate events. The event handler once set, persists
    until the client closes the driver or sets another event handler (which
    could be a "NULL" pointer to indicate no callback).

  Precondition:
    DRV_AT25_Open must have been called to obtain a valid opened device handle.

  Parameters:
    handle - A valid open-instance handle, returned from the driver's open 
	routine.

    eventHandler - Pointer to the event handler function.

    context - The value of parameter will be passed back to the client
    unchanged, when the eventHandler function is called.  It can be used to 
	identify any client specific data object that identifies the instance of the 
	client module (for example, it may be a pointer to the client module's state 
	structure).

  Returns:
    None.

  Example:
    <code>
    
    #define BUFFER_SIZE  256
    #define MEM_ADDRESS  0x0
    
    // myAppObj is an application specific state data object.
    MY_APP_OBJ myAppObj;

    uint8_t myBuffer[BUFFER_SIZE];    

    // myHandle is the handle returned from DRV_AT25_Open API.

    // Client registers an event handler with driver. This is done once

    DRV_AT25_EventHandlerSet( myHandle, APP_AT25TransferEventHandler,
                                     (uintptr_t)&myAppObj );

    if (DRV_AT25_Read(myHandle, myBuffer, BUFFER_SIZE, MEM_ADDRESS) == false)   
    {
        // Error handling here
    }

    // Event is received when the buffer is processed.

    void APP_AT25TransferEventHandler(DRV_AT25_TRANSFER_STATUS event, uintptr_t context)
    {
        // The context handle was set to an application specific
        // object. It is now retrievable easily in the event handler.
        MY_APP_OBJ myAppObj = (MY_APP_OBJ *) context;

        switch(event)
        {
            case DRV_AT25_TRANSFER_STATUS_COMPLETED:
                // This means the data was transferred.
                break;

            case DRV_AT25_TRANSFER_STATUS_ERROR:
                // Error handling here.
                break;

            default:
                break;
        }
    }
    </code>

  Remarks:
    If the client does not want to be notified when the queued buffer transfer
    has completed, it does not need to register a callback. This function is
    thread safe when called in a RTOS application.
*/

void DRV_AT25_EventHandlerSet( 
    const DRV_HANDLE handle, 
    const DRV_AT25_EVENT_HANDLER eventHandler, 
    const uintptr_t context 
);

#ifdef __cplusplus
}
#endif

#include "driver/at25/src/drv_at25_local.h"

#endif // #ifndef _DRV_AT25_H
/*******************************************************************************
 End of File
*/