<#--
/*******************************************************************************
  SDHC Driver Freemarker Template File

  Company:
    Microchip Technology Inc.

  File Name:
    drv_sdhc.h.ftl

  Summary:
    SDHC Driver Freemarker Template File

  Description:

*******************************************************************************/

/*******************************************************************************
Copyright (c) 2013-2015 released Microchip Technology Inc.  All rights reserved.

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
-->


/*** SDHC Driver Configuration ***/
<#-- Driver Instances -->
#define DRV_SDHC_CLIENTS_NUMBER ${DRV_SDHC_CLIENTS_NUMBER}
#define DRV_SDHC_BUFFER_OBJ_NUMBER ${DRV_SDHC_BUFFER_OBJECT_NUMBER}
#define DRV_SDHC_CARD_DETECT_ENABLE  ${DRV_SDHC_SDCDEN?c}
#define	DRV_SDHC_WRITE_PROTECT_ENABLE  ${DRV_SDHC_SDWPEN?c}

<#if HarmonyCore.SELECT_RTOS != "BareMetal">
    <#lt>/* SDHC Driver Instance RTOS Configurations*/
    <#lt>#define DRV_SDHC_STACK_SIZE           ${DRV_SDHC_RTOS_STACK_SIZE}
    <#lt>#define DRV_SDHC_PRIORITY             ${DRV_SDHC_RTOS_TASK_PRIORITY}
</#if>

<#--
/*******************************************************************************
 End of File
*/
-->
