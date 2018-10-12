/*******************************************************************************
  System Configuration Header

  File Name:
    configuration.h

  Summary:
    Build-time configuration header for the system defined by this project.

  Description:
    An MPLAB Project may have multiple configurations.  This file defines the
    build-time options for a single configuration.

  Remarks:
    This configuration header must not define any prototypes or data
    definitions (or include any files that do).  It only provides macro
    definitions for build-time configuration options

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

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section Includes other configuration headers necessary to completely
    define this configuration.
*/

#include "user.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: System Configuration
// *****************************************************************************
// *****************************************************************************
#define DCACHE_CLEAN_BY_ADDR(data, size)       SCB_CleanDCache_by_Addr((uint32_t *)data, size)
#define DCACHE_INVALIDATE_BY_ADDR(data, size)  SCB_InvalidateDCache_by_Addr((uint32_t *)data, size)

#define DATA_CACHE_ENABLED                     true

// *****************************************************************************
// *****************************************************************************
// Section: System Service Configuration
// *****************************************************************************
// *****************************************************************************

/* File System Service Configuration */

#define SYS_FS_MEDIA_NUMBER               2

#define SYS_FS_VOLUME_NUMBER              (1 + 1)

#define SYS_FS_AUTOMOUNT_ENABLE           true
#define SYS_FS_CLIENT_NUMBER              1
#define SYS_FS_MAX_FILES                  2
#define SYS_FS_MAX_FILE_SYSTEM_TYPE       2
#define SYS_FS_MEDIA_MAX_BLOCK_SIZE       512
#define SYS_FS_MEDIA_MANAGER_BUFFER_SIZE  2048
#define SYS_FS_FILE_NAME_LEN              255
#define SYS_FS_CWD_STRING_LEN             1024




#define SYS_FS_MEDIA_TYPE_IDX0 				SYS_FS_MEDIA_TYPE_SD_CARD
#define SYS_FS_TYPE_IDX0 					FAT
					
#define SYS_FS_MEDIA_IDX0_MOUNT_NAME_VOLUME_IDX0 			"/mnt/myDrive1"
#define SYS_FS_MEDIA_IDX0_DEVICE_NAME_VOLUME_IDX0			"/dev/mmcblka1"
								
#define SYS_FS_MEDIA_TYPE_IDX1 				SYS_FS_MEDIA_TYPE_NVM
#define SYS_FS_TYPE_IDX1 					MPFS2
					
#define SYS_FS_MEDIA_IDX1_MOUNT_NAME_VOLUME_IDX0 			"/mnt/myDrive2"
#define SYS_FS_MEDIA_IDX1_DEVICE_NAME_VOLUME_IDX0			"/dev/nvma1"
								

/* TIME System Service Configuration Options */
#define SYS_TIME_INDEX_0                     0
#define SYS_TIME_MAX_TIMERS                  10
#define SYS_TIME_HW_COUNTER_WIDTH            16
#define SYS_TIME_HW_COUNTER_PERIOD           0xFFFF
#define SYS_TIME_HW_COUNTER_HALF_PERIOD		 (SYS_TIME_HW_COUNTER_PERIOD>>1)
#define SYS_TIME_CPU_CLOCK_FREQUENCY         300000000


// *****************************************************************************
// *****************************************************************************
// Section: Driver Configuration
// *****************************************************************************
// *****************************************************************************
/* Memory Driver Global Configuration Options */
#define DRV_MEMORY_INSTANCES_NUMBER          1

/* Memory Driver Instance 0 Configuration */
#define DRV_MEMORY_INDEX_0                   0
#define DRV_MEMORY_CLIENTS_NUMBER_IDX0       1
#define DRV_MEMORY_BUFFER_QUEUE_SIZE_IDX0    1
#define DRV_MEMORY_DEVICE_START_ADDRESS      0x500000
#define DRV_MEMORY_DEVICE_MEDIA_SIZE         1024UL
#define DRV_MEMORY_DEVICE_PROGRAM_SIZE       512
#define DRV_MEMORY_DEVICE_ERASE_SIZE         8192


/* SDHC Driver Global Configuration Options */
#define DRV_SDHC_INSTANCES_NUMBER 1


/*** SDHC Driver Configuration ***/
#define DRV_SDHC_CLIENTS_NUMBER 1
#define DRV_SDHC_BUFFER_OBJ_NUMBER 1
#define DRV_SDHC_CARD_DETECT_ENABLE  false
#define	DRV_SDHC_WRITE_PROTECT_ENABLE  false





// *****************************************************************************
// *****************************************************************************
// Section: Middleware & Other Library Configuration
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Application Configuration
// *****************************************************************************
// *****************************************************************************


//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

#endif // CONFIGURATION_H
/*******************************************************************************
 End of File
*/