/*******************************************************************************
  MEMORY Driver Local Data Structures

  Company:
    Microchip Technology Inc.

  File Name:
    drv_serialflash_local.h

  Summary:
    MEMORY driver local declarations and definitions

  Description:
    This file contains the MEMORY driver's local declarations and definitions.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2016 - 2017 released Microchip Technology Inc. All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
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
//DOM-IGNORE-END

#ifndef _DRV_MEMORY_LOCAL_H
#define _DRV_MEMORY_LOCAL_H

// *****************************************************************************
// *****************************************************************************
// Section: File includes
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "configuration.h"
#include "driver/memory/drv_memory.h"

// *****************************************************************************
// *****************************************************************************
// Section: Version Numbers
// *****************************************************************************
// *****************************************************************************
/* Version of the driver */

// *****************************************************************************
/* MEMORY Driver Version Macros

  Summary:
    MEMORY driver version

  Description:
    These constants provide MEMORY driver version information. The driver
    version is
    DRV_MEMORY_VERSION_MAJOR.DRV_MEMORY_VERSION_MINOR.DRV_MEMORY_VERSION_PATCH.
    It is represented in DRV_MEMORY_VERSION as
    MAJOR *10000 + MINOR * 100 + PATCH, so as to allow comparisons.
    It is also represented in string format in DRV_MEMORY_VERSION_STR.
    DRV_MEMORY_TYPE provides the type of the release when the release is alpha
    or beta. The interfaces DRV_MEMORY_VersionGet() and
    DRV_MEMORY_VersionStrGet() provide interfaces to the access the version
    and the version string.

  Remarks:
    Modify the return value of DRV_MEMORY_VersionStrGet and the
    DRV_MEMORY_VERSION_MAJOR, DRV_MEMORY_VERSION_MINOR,
    DRV_MEMORY_VERSION_PATCH and DRV_MEMORY_VERSION_TYPE
*/

#define _DRV_MEMORY_VERSION_MAJOR         0
#define _DRV_MEMORY_VERSION_MINOR         2
#define _DRV_MEMORY_VERSION_PATCH         0
#define _DRV_MEMORY_VERSION_TYPE          "Alpha"
#define _DRV_MEMORY_VERSION_STR           "0.2.0 Alpha"

// *****************************************************************************
// *****************************************************************************
// Section: Local Data Type Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* MEMORY Driver Buffer Handle Macros

  Summary:
    MEMORY driver Buffer Handle Macros

  Description:
    Buffer handle related utility macros. MEMORY driver buffer handle is a 
    combination of buffer token and the buffer object index. The buffertoken
    is a 16 bit number that is incremented for every new write or erase request
    and is used along with the buffer object index to generate a new buffer 
    handle for every request.

  Remarks:
    None
*/

#define DRV_MEMORY_BUF_TOKEN_MAX             (0xFFFF)
#define DRV_MEMORY_MAKE_HANDLE(token, index) ((token) << 16 | (index))
#define DRV_MEMORY_UPDATE_BUF_TOKEN(token) \
{ \
    (token)++; \
    (token) = ((token) == DRV_MEMORY_BUF_TOKEN_MAX) ? 0: (token); \
}


// *****************************************************************************
/* MEMORY Read/Write/Erase Region Index Numbers

  Summary:
    MEMORY Geometry Table Index definitions.

  Description:
    These constants provide MEMORY Geometry Table index definitions.

  Remarks:
    None
*/
#define DRV_MEMORY_GEOMETRY_TABLE_READ_ENTRY   (0)
#define DRV_MEMORY_GEOMETRY_TABLE_WRITE_ENTRY  (1)
#define DRV_MEMORY_GEOMETRY_TABLE_ERASE_ENTRY  (2)

// *****************************************************************************
/* MEMORY Driver operations.

  Summary:
    Enumeration listing the MEMORY driver operations.

  Description:
    This enumeration defines the possible MEMORY driver operations.

  Remarks:
    None
*/

typedef enum 
{
    /* Request is read operation. */
    DRV_MEMORY_OPERATION_TYPE_READ = 0,

    /* Request is write operation. */
    DRV_MEMORY_OPERATION_TYPE_WRITE,

    /* Request is erase operation. */
    DRV_MEMORY_OPERATION_TYPE_ERASE,

    /* Request is erase write operation. */
    DRV_MEMORY_OPERATION_TYPE_ERASE_WRITE

} DRV_MEMORY_OPERATION_TYPE;

// *****************************************************************************
/* MEMORY Driver write states.

  Summary:
    Enumeration listing the MEMORY driver's write states.

  Description:
    This enumeration defines the possible MEMORY driver's write states.

  Remarks:
    None
*/

typedef enum
{
    /* Write init state */
    DRV_MEMORY_WRITE_INIT = 0,

    /* Write command state */
    DRV_MEMORY_WRITE_MEM,

    /* Write command status state */
    DRV_MEMORY_WRITE_MEM_STATUS

} DRV_MEMORY_WRITE_STATE;

// *****************************************************************************
/* MEMORY Driver erase states.

  Summary:
    Enumeration listing the MEMORY driver's erase states.

  Description:
    This enumeration defines the possible MEMORY driver's erase states.

  Remarks:
    None
*/
typedef enum
{
    /* Erase init state */
    DRV_MEMORY_ERASE_INIT = 0,

    /* Erase command state */
    DRV_MEMORY_ERASE_CMD,

    /* Erase command status state */
    DRV_MEMORY_ERASE_CMD_STATUS

} DRV_MEMORY_ERASE_STATE;

// *****************************************************************************
/* MEMORY Driver erasewrite states.

  Summary:
    Enumeration listing the MEMORY driver's erasewrite states.

  Description:
    This enumeration defines the possible MEMORY driver's erasewrite states.

  Remarks:
    None
*/

typedef enum
{
    /* Erase write init state. */
    DRV_MEMORY_EW_INIT = 0,
    
    /* Erase write read state */
    DRV_MEMORY_EW_READ_SECTOR,

    /* Erase write erase state */
    DRV_MEMORY_EW_ERASE_SECTOR,

    /* Erase write write state */
    DRV_MEMORY_EW_WRITE_SECTOR

} DRV_MEMORY_EW_STATE;

typedef enum
{
    /* Check if the SQI driver is ready. If ready open the SQI driver instance.
     * */
    DRV_MEMORY_INIT_DEVICE = 0,

    /* Read the SST flash ID */
    DRV_MEMORY_GEOMETRY_UPDATE,

    /* Perform a global unlock command. */
    DRV_MEMORY_UNLOCK_FLASH,

    /* Process the operations queued at the SST driver. */
    DRV_MEMORY_PROCESS_QUEUE,

    /* Perform the required transfer */
    DRV_MEMORY_TRANSFER,

    /* Idle state of the driver. */
    DRV_MEMORY_IDLE,

    /* Error state. */
    DRV_MEMORY_ERROR

} DRV_MEMORY_STATE;

/**************************************
 * MEMORY Driver Client 
 **************************************/
typedef struct DRV_MEMORY_CLIENT_OBJ_STRUCT
{
    /* The hardware instance object associate with the client */
    void * driverObj;

    /* Status of the client object */
    SYS_STATUS sysStatus;

    /* The intent with which the client was opened */
    DRV_IO_INTENT intent;

    /* Flag to indicate in use */
    bool inUse;

    /* Client specific event handler */
    DRV_MEMORY_TRANSFER_HANDLER transferHandler;

    /* Client specific context */
    uintptr_t context;

} DRV_MEMORY_CLIENT_OBJECT;

/*******************************************
 * MEMORY Driver Buffer Object that services
 * a driver request.
 ******************************************/

typedef struct _DRV_MEMORY_BUFFER_OBJECT
{
    /* Buffer Object array index */
    uint32_t index;

    /* Client that owns this buffer */
    DRV_MEMORY_CLIENT_OBJECT *hClient;

    /* Present status of this command */
    DRV_MEMORY_COMMAND_STATUS status;

    /* Current command handle of this buffer object */
    DRV_MEMORY_COMMAND_HANDLE commandHandle;

    /* Pointer to the source/destination buffer */
    uint8_t *buffer;

    /* Start address of the operation. */
    uint32_t blockStart;

    /* Number of blocks */
    uint32_t nBlocks;

    /* Operation type - read/write/erase/erasewrite */
    DRV_MEMORY_OPERATION_TYPE opType;

    /* Pointer to the next buffer in the queue */
    struct _DRV_MEMORY_BUFFER_OBJECT *next;

} DRV_MEMORY_BUFFER_OBJECT;

/**************************************
 * MEMORY Driver Hardware Instance Object
 **************************************/
typedef struct
{
    /* The status of the driver */
    SYS_STATUS status;

    /* Erase state */
    DRV_MEMORY_ERASE_STATE eraseState;

    /* Write state */
    DRV_MEMORY_WRITE_STATE writeState;

    /* Erase write state */
    DRV_MEMORY_EW_STATE ewState;

    /* MEMORY main task routine's states */
    DRV_MEMORY_STATE state;

    /* Flag to indicate in use  */
    bool inUse;
    
    /* Flag to indicate that the driver is used in exclusive access mode */
    bool isExclusive;

    /* Pointer to the Erase Write buffer */
    uint8_t *ewBuffer;

    /* This instances flash start address */
    uint32_t blockStartAddress;

    /* Tracks the current block address for the write operation. */
    uint32_t blockAddress;

    /* Tracks the current number of blocks of the write operation. */
    uint32_t nBlocks;

    /* erase write sector number */
    uint32_t sectorNumber;

    /* Block offset within the current sector. */
    uint32_t blockOffsetInSector;

    /* Number of blocks to write. */
    uint32_t nBlocksToWrite;

    /* Pointer to user write buffer */
    uint8_t *writePtr;
    
    /* Write Block size */
    uint32_t writeBlockSize;

    /* Erase Block size */
    uint32_t eraseBlockSize;

    /* Interrupt mode for attached device */
    bool inInterruptMode;

    /* Interrupt Source of Attached device */
    INT_SOURCE interruptSource;

    /* Interrupt status flag*/
    bool intStatus;

    /* Flash Device functions */
    const MEMORY_DEVICE_API *memoryDevice;

    /* Pointer to Buffer Objects array */
    DRV_MEMORY_BUFFER_OBJECT *buffObjArr;

    /* Pointer to free list of Buffer Objects */
    DRV_MEMORY_BUFFER_OBJECT *buffObjFree;

    /* The Buffer Q head pointer */
    DRV_MEMORY_BUFFER_OBJECT *queueHead;

    /* The Buffer Q tail pointer */
    DRV_MEMORY_BUFFER_OBJECT *queueTail;
    
    /* Pointer to the current buffer object */
    DRV_MEMORY_BUFFER_OBJECT *currentBufObj;
    
    /* Memory pool for Client Objects */
    DRV_MEMORY_CLIENT_OBJECT *clientObjPool;

    /* Buffer Queue Size */
    size_t queueSize;

    /* Number of clients connected to the hardware instance */
    uint8_t numClients;

    /* Maximum number of clients */
    size_t nClientsMax;

    /* MEMORY driver geometry object */
    DRV_MEMORY_GEOMETRY mediaGeometryObj;

    /* MEMORY driver media geometry table. */
    DRV_MEMORY_REGION_GEOMETRY mediaGeometryTable[3];
    
} DRV_MEMORY_OBJECT;

typedef MEMORY_DEVICE_TRANSFER_STATUS (*DRV_MEMORY_TransferOperation)(
    DRV_MEMORY_OBJECT *dObj,
    uint8_t *data,
    uint32_t blockStart,
    uint32_t nBlocks
);

#endif //#ifndef _DRV_MEMORY_LOCAL_H

/*******************************************************************************
 End of File
*/

