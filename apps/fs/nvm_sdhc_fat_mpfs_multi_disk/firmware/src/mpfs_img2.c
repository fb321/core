/***************************************************************
 * FileName:    mpfs_img2.c
 * Description: Defines an MPFS2 image to be stored in program memory.
 * Processor:   PIC32
 * Compiler:    Microchip C32,XC32
 *
 * NOT FOR HAND MODIFICATION
 * This file is automatically generated by the MPFS2 Utility
 * ALL MODIFICATIONS WILL BE OVERWRITTEN BY THE MPFS2 GENERATOR
 */

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

#include <stdint.h>
#include "definitions.h"

/**************************************
 * MPFS2 Image Data
 **************************************/ 

#define KEEP              __attribute__((space(prog),address(DRV_MEMORY_DEVICE_START_ADDRESS))) __attribute__ ((keep))


const uint8_t KEEP NVM_MEDIA_DATA[DRV_MEMORY_DEVICE_MEDIA_SIZE] = { \
	0x4d,0x50,0x46,0x53,0x02,0x01,0x01,0x00,0xa8,0x5e,0x20,0x00,0x00,0x00,0x28,0x00, /* MPFS.....^ ...(. */ \
	0x00,0x00,0x0d,0x00,0x00,0x00,0xb5,0x99,0xd8,0x53,0x00,0x00,0x00,0x00,0x00,0x00, /* .........S...... */ \
	0x61,0x62,0x63,0x2e,0x74,0x78,0x74,0x00,0x48,0x65,0x6c,0x6c,0x6f,0x20,0x57,0x6f, /* abc.txt.Hello Wo */ \
	0x72,0x6c,0x64,0x20,0x21                                                         /* rld !            */


};

/**************************************
 * MPFS2 C linkable symbols
 **************************************/
// The entire data array is defined as a single variable to 
// ensure that the linker does not reorder the data chunks in Flash when compiler 
// optimizations are turned on.
struct MEDIA_STORAGE_PARTITION_INFO
{
	const char*     partName;           // name that identifies the partition
										// valid names: "mpfs2", "tcpip_storage";
	unsigned long   partStartOffset;    // the absolute starting offset on that media 
	unsigned long   partSize;           // size of the partition, in bytes
} MPFS_IMAGE_PARTITION_INFO = 
{
	"mpfs2",
	(unsigned long)NVM_MEDIA_DATA,
	sizeof(NVM_MEDIA_DATA),
};

/**************************************************************
 * End of MPFS
 **************************************************************/
