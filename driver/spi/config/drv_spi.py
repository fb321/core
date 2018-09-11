def instantiateComponent(spiComponent, index):
    global drvSpiInstanceSpace
    drvSpiInstanceSpace = "drv_spi_" + str(index)

    # Enable "Generate Harmony Driver Common Files" option in MHC
    Database.setSymbolValue("HarmonyCore", "ENABLE_DRV_COMMON", True, 1)

    # Enable "Generate Harmony System Service Common Files" option in MHC
    Database.setSymbolValue("HarmonyCore", "ENABLE_SYS_COMMON", True, 1)

    # Enable "Enable System Ports" option in MHC
    Database.setSymbolValue("HarmonyCore", "ENABLE_SYS_PORTS", True, 1)

    # Enable "Enable System DMA" option in MHC
    Database.setSymbolValue("HarmonyCore", "ENABLE_SYS_DMA", True, 1)

    spiSymIndex = spiComponent.createIntegerSymbol("INDEX", None)
    spiSymIndex.setVisible(False)
    spiSymIndex.setDefaultValue(index)

    spiSymPLIB = spiComponent.createStringSymbol("DRV_SPI_PLIB", None)
    spiSymPLIB.setLabel("PLIB Used")
    spiSymPLIB.setReadOnly(True)
    spiSymPLIB.setDefaultValue("SPI0")

    global spiSymPLIBConnection
    spiSymPLIBConnection = spiComponent.createBooleanSymbol("DRV_SPI_PLIB_CONNECTION", None)
    spiSymPLIBConnection.setDefaultValue(False)
    spiSymPLIBConnection.setVisible(False)

    spiGlobalMode = spiComponent.createBooleanSymbol("DRV_SPI_MODE", None)
    spiGlobalMode.setLabel("**** Driver Mode Update ****")
    spiGlobalMode.setValue(Database.getSymbolValue("drv_spi", "DRV_SPI_COMMON_MODE"), 1)
    spiGlobalMode.setVisible(False)
    spiGlobalMode.setDependencies(spiDriverMode, ["drv_spi.DRV_SPI_COMMON_MODE"])

    spiSymNumClients = spiComponent.createIntegerSymbol("DRV_SPI_NUM_CLIENTS", None)
    spiSymNumClients.setLabel("Number of Clients")
    spiSymNumClients.setMin(1)
    spiSymNumClients.setMax(10)
    spiSymNumClients.setDefaultValue(1)

    spiSymQueueSize = spiComponent.createIntegerSymbol("DRV_SPI_QUEUE_SIZE", None)
    spiSymQueueSize.setLabel("Transfer Queue Size")
    spiSymQueueSize.setMin(1)
    spiSymQueueSize.setMax(250)
    spiSymQueueSize.setDefaultValue(4)
    spiSymQueueSize.setDependencies(asyncModeOptions, ["DRV_SPI_MODE"])

    global spiTXRXDMA
    spiTXRXDMA = spiComponent.createBooleanSymbol("DRV_SPI_TX_RX_DMA", None)
    spiTXRXDMA.setLabel("Use DMA for Transmit and Receive?")
    spiTXRXDMA.setDefaultValue(False)

    global spiTXDMAChannel
    spiTXDMAChannel = spiComponent.createIntegerSymbol("DRV_SPI_TX_DMA_CHANNEL", None)
    spiTXDMAChannel.setLabel("DMA Channel For Transmit")
    spiTXDMAChannel.setDefaultValue(0)
    spiTXDMAChannel.setVisible(False)
    spiTXDMAChannel.setReadOnly(True)
    spiTXDMAChannel.setDependencies(requestAndAssignDMAChannel, ["DRV_SPI_TX_RX_DMA"])

    spiTXDMAChannelComment = spiComponent.createCommentSymbol("DRV_SPI_TX_DMA_CH_COMMENT", None)
    spiTXDMAChannelComment.setLabel("Warning!!! Couldn't Allocate DMA Channel for Transmit. Check DMA manager.")
    spiTXDMAChannelComment.setVisible(False)
    spiTXDMAChannelComment.setDependencies(requestDMAComment, ["DRV_SPI_TX_DMA_CHANNEL"])

    global spiRXDMAChannel
    spiRXDMAChannel = spiComponent.createIntegerSymbol("DRV_SPI_RX_DMA_CHANNEL", None)
    spiRXDMAChannel.setLabel("DMA Channel For Receive")
    spiRXDMAChannel.setDefaultValue(1)
    spiRXDMAChannel.setVisible(False)
    spiRXDMAChannel.setReadOnly(True)
    spiRXDMAChannel.setDependencies(requestAndAssignDMAChannel, ["DRV_SPI_TX_RX_DMA"])

    spiRXDMAChannelComment = spiComponent.createCommentSymbol("DRV_SPI_RX_DMA_CH_COMMENT", None)
    spiRXDMAChannelComment.setLabel("Warning!!! Couldn't Allocate DMA Channel for Receive. Check DMA manager.")
    spiRXDMAChannelComment.setVisible(False)
    spiRXDMAChannelComment.setDependencies(requestDMAComment, ["DRV_SPI_RX_DMA_CHANNEL"])

    ############################################################################
    #### Code Generation ####
    ############################################################################

    configName = Variables.get("__CONFIGURATION_NAME")

    # Global Header Files
    spiSymHeaderFile = spiComponent.createFileSymbol("DRV_SPI_HEADER", None)
    spiSymHeaderFile.setSourcePath("driver/spi/drv_spi.h")
    spiSymHeaderFile.setOutputName("drv_spi.h")
    spiSymHeaderFile.setDestPath("driver/spi/")
    spiSymHeaderFile.setProjectPath("config/" + configName + "/driver/spi/")
    spiSymHeaderFile.setType("HEADER")
    spiSymHeaderFile.setOverwrite(True)

    spiSymHeaderDefFile = spiComponent.createFileSymbol("DRV_SPI_DEF", None)
    spiSymHeaderDefFile.setSourcePath("driver/spi/templates/drv_spi_definitions.h.ftl")
    spiSymHeaderDefFile.setOutputName("drv_spi_definitions.h")
    spiSymHeaderDefFile.setDestPath("driver/spi")
    spiSymHeaderDefFile.setProjectPath("config/" + configName + "/driver/spi/")
    spiSymHeaderDefFile.setType("HEADER")
    spiSymHeaderDefFile.setMarkup(True)
    spiSymHeaderDefFile.setOverwrite(True)

    spiSymVariantMappingFile = spiComponent.createFileSymbol("DRV_SPI_VARIANT_MAPPING", None)
    spiSymVariantMappingFile.setSourcePath("driver/spi/src/drv_spi_variant_mapping.h")
    spiSymVariantMappingFile.setOutputName("drv_spi_variant_mapping.h")
    spiSymVariantMappingFile.setDestPath("driver/spi/src")
    spiSymVariantMappingFile.setProjectPath("config/" + configName + "/driver/spi/")
    spiSymVariantMappingFile.setType("HEADER")
    spiSymVariantMappingFile.setMarkup(False)
    spiSymVariantMappingFile.setOverwrite(True)

    # Async Source Files
    spiAsyncSymSourceFile = spiComponent.createFileSymbol("DRV_SPI_ASYNC_SOURCE", None)
    spiAsyncSymSourceFile.setSourcePath("driver/spi/src/async/drv_spi.c")
    spiAsyncSymSourceFile.setOutputName("drv_spi.c")
    spiAsyncSymSourceFile.setDestPath("driver/spi/src")
    spiAsyncSymSourceFile.setProjectPath("config/" + configName + "/driver/spi/")
    spiAsyncSymSourceFile.setType("SOURCE")
    spiAsyncSymSourceFile.setOverwrite(True)
    spiAsyncSymSourceFile.setEnabled(True)
    spiAsyncSymSourceFile.setDependencies(asyncFileGen, ["DRV_SPI_MODE"])

    spiAsyncSymHeaderLocalFile = spiComponent.createFileSymbol("DRV_SPI_ASYNC_HEADER_LOCAL", None)
    spiAsyncSymHeaderLocalFile.setSourcePath("driver/spi/src/async/drv_spi_local.h")
    spiAsyncSymHeaderLocalFile.setOutputName("drv_spi_local.h")
    spiAsyncSymHeaderLocalFile.setDestPath("driver/spi/src")
    spiAsyncSymHeaderLocalFile.setProjectPath("config/" + configName + "/driver/spi/")
    spiAsyncSymHeaderLocalFile.setType("HEADER")
    spiAsyncSymHeaderLocalFile.setOverwrite(True)
    spiAsyncSymHeaderLocalFile.setEnabled(True)
    spiAsyncSymHeaderLocalFile.setDependencies(asyncFileGen, ["DRV_SPI_MODE"])

    # Sync Source Files
    spiSyncSymSourceFile = spiComponent.createFileSymbol("DRV_SPI_SYNC_SOURCE", None)
    spiSyncSymSourceFile.setSourcePath("driver/spi/src/sync/drv_spi.c")
    spiSyncSymSourceFile.setOutputName("drv_spi.c")
    spiSyncSymSourceFile.setDestPath("driver/spi/src")
    spiSyncSymSourceFile.setProjectPath("config/" + configName + "/driver/spi/")
    spiSyncSymSourceFile.setType("SOURCE")
    spiSyncSymSourceFile.setOverwrite(True)
    spiSyncSymSourceFile.setEnabled(False)
    spiSyncSymSourceFile.setDependencies(syncFileGen, ["DRV_SPI_MODE"])

    spiSyncSymHeaderLocalFile = spiComponent.createFileSymbol("DRV_SPI_SYNC_HEADER_LOCAL", None)
    spiSyncSymHeaderLocalFile.setSourcePath("driver/spi/src/sync/drv_spi_local.h")
    spiSyncSymHeaderLocalFile.setOutputName("drv_spi_local.h")
    spiSyncSymHeaderLocalFile.setDestPath("driver/spi/src")
    spiSyncSymHeaderLocalFile.setProjectPath("config/" + configName + "/driver/spi/")
    spiSyncSymHeaderLocalFile.setType("SOURCE")
    spiSyncSymHeaderLocalFile.setOverwrite(True)
    spiSyncSymHeaderLocalFile.setEnabled(False)
    spiSyncSymHeaderLocalFile.setDependencies(syncFileGen, ["DRV_SPI_MODE"])

    # System Template Files
    spiSymSystemDefIncFile = spiComponent.createFileSymbol("DRV_SPI_SYSTEM_DEF", None)
    spiSymSystemDefIncFile.setType("STRING")
    spiSymSystemDefIncFile.setOutputName("core.LIST_SYSTEM_DEFINITIONS_H_INCLUDES")
    spiSymSystemDefIncFile.setSourcePath("driver/spi/templates/system/system_definitions.h.ftl")
    spiSymSystemDefIncFile.setMarkup(True)

    spiSymSystemDefObjFile = spiComponent.createFileSymbol("DRV_SPI_SYSTEM_DEF_OBJECT", None)
    spiSymSystemDefObjFile.setType("STRING")
    spiSymSystemDefObjFile.setOutputName("core.LIST_SYSTEM_DEFINITIONS_H_OBJECTS")
    spiSymSystemDefObjFile.setSourcePath("driver/spi/templates/system/system_definitions_objects.h.ftl")
    spiSymSystemDefObjFile.setMarkup(True)

    spiSymSystemConfigFile = spiComponent.createFileSymbol("DRV_SPI_SYSTEM_CONFIG", None)
    spiSymSystemConfigFile.setType("STRING")
    spiSymSystemConfigFile.setOutputName("core.LIST_SYSTEM_CONFIG_H_DRIVER_CONFIGURATION")
    spiSymSystemConfigFile.setSourcePath("driver/spi/templates/system/system_config.h.ftl")
    spiSymSystemConfigFile.setMarkup(True)

    spiSymSystemInitDataFile = spiComponent.createFileSymbol("DRV_SPI_INIT_DATA", None)
    spiSymSystemInitDataFile.setType("STRING")
    spiSymSystemInitDataFile.setOutputName("core.LIST_SYSTEM_INIT_C_DRIVER_INITIALIZATION_DATA")
    spiSymSystemInitDataFile.setSourcePath("driver/spi/templates/system/system_initialize_data.c.ftl")
    spiSymSystemInitDataFile.setMarkup(True)

    spiSymSystemInitFile = spiComponent.createFileSymbol("DRV_SPI_SYS_INIT", None)
    spiSymSystemInitFile.setType("STRING")
    spiSymSystemInitFile.setOutputName("core.LIST_SYSTEM_INIT_C_SYS_INITIALIZE_DRIVERS")
    spiSymSystemInitFile.setSourcePath("driver/spi/templates/system/system_initialize.c.ftl")
    spiSymSystemInitFile.setMarkup(True)

def spiDriverMode (Sym, event):
    Sym.setValue(Database.getSymbolValue("drv_spi", "DRV_SPI_COMMON_MODE"), 1)

def onDependencyConnected(info):
    dmaRxRequestID = "DMA_CH_NEEDED_FOR_" + info["remoteComponent"].getID().upper() + "_Receive"
    dmaTxRequestID = "DMA_CH_NEEDED_FOR_" + info["remoteComponent"].getID().upper() + "_Transmit"
    dmaTxChannelID = "DMA_CH_FOR_" + info["remoteComponent"].getID().upper() + "_Transmit"
    dmaRxChannelID = "DMA_CH_FOR_" + info["remoteComponent"].getID().upper() + "_Receive"

    localComponent = connectionInfo["localComponent"]

    if info["dependencyID"] == "drv_spi_SPI_dependency" :
        localComponent.setSymbolValue("DRV_SPI_PLIB_CONNECTION", True, 2)
        plibUsed = localComponent.getSymbolByID("DRV_SPI_PLIB")
        plibUsed.clearValue()
        plibUsed.setValue(info["remoteComponent"].getID().upper(), 1)
        Database.setSymbolValue(info["remoteComponent"].getID().upper(), "SPI_DRIVER_CONTROLLED", True, 1)

        if localComponent.getSymbolValue("DRV_SPI_TX_RX_DMA") == True:
            Database.setSymbolValue("core", dmaRxRequestID, True, 2)
            Database.setSymbolValue("core", dmaTxRequestID, True, 2)

            # Get the allocated channel and assign it
            txChannel = Database.getSymbolValue("core", dmaTxChannelID)
            localComponent.setSymbolValue("DRV_SPI_TX_DMA_CHANNEL", txChannel, 2)
            rxChannel = Database.getSymbolValue("core", dmaRxChannelID)
            localComponent.setSymbolValue("DRV_SPI_RX_DMA_CHANNEL", rxChannel, 2)

def onDependencyDisconnected(info):
    dmaRxRequestID = "DMA_CH_NEEDED_FOR_" + info["remoteComponent"].getID().upper() + "_Receive"
    dmaTxRequestID = "DMA_CH_NEEDED_FOR_" + info["remoteComponent"].getID().upper() + "_Transmit"
    dmaTxChannelID = "DMA_CH_FOR_" + info["remoteComponent"].getID().upper() + "_Transmit"
    dmaRxChannelID = "DMA_CH_FOR_" + info["remoteComponent"].getID().upper() + "_Receive"

    localComponent = connectionInfo["localComponent"]

    if info["dependencyID"] == "drv_spi_SPI_dependency" :
        localComponent.setSymbolValue("DRV_SPI_PLIB_CONNECTION", False, 2)
        Database.setSymbolValue(info["remoteComponent"].getID().upper(), "SPI_DRIVER_CONTROLLED", False, 1)

        if localComponent.getSymbolValue("DRV_SPI_TX_RX_DMA") == True:
            Database.setSymbolValue("core", dmaRxRequestID, False, 2)
            Database.setSymbolValue("core", dmaTxRequestID, False, 2)

            # Get the allocated channel and assign it
            txChannel = Database.getSymbolValue("core", dmaTxChannelID)
            localComponent.setSymbolValue("DRV_SPI_TX_DMA_CHANNEL", txChannel, 2)
            rxChannel = Database.getSymbolValue("core", dmaRxChannelID)
            localComponent.setSymbolValue("DRV_SPI_RX_DMA_CHANNEL", rxChannel, 2)

def requestAndAssignDMAChannel(Sym, event):
    global drvSpiInstanceSpace
    global spiSymPLIBConnection

    spiPeripheral = Database.getSymbolValue(drvSpiInstanceSpace, "DRV_SPI_PLIB")

    if Sym.getID() == "DRV_SPI_TX_DMA_CHANNEL":
        dmaChannelID = "DMA_CH_FOR_" + str(spiPeripheral) + "_Transmit"
        dmaRequestID = "DMA_CH_NEEDED_FOR_" + str(spiPeripheral) + "_Transmit"
    else:
        dmaChannelID = "DMA_CH_FOR_" + str(spiPeripheral) + "_Receive"
        dmaRequestID = "DMA_CH_NEEDED_FOR_" + str(spiPeripheral) + "_Receive"

    # Control visibility
    Sym.setVisible(event["value"])

    if event["value"] == False:
        Database.setSymbolValue("core", dmaRequestID, False, 2)
    else:
        if (spiSymPLIBConnection.getValue() == True) and (Database.getSymbolValue("core", dmaChannelID) == -1):
            Database.setSymbolValue("core", dmaRequestID, True, 2)

    # Get the allocated channel and assign it
    channel = Database.getSymbolValue("core", dmaChannelID)
    Sym.setValue(channel, 2)

def requestDMAComment(Sym, event):
    if(event["value"] == -2):
        Sym.setVisible(True)
    else:
        Sym.setVisible(False)

def destroyComponent(spiComponent):
    global drvSpiInstanceSpace
    spiPeripheral = Database.getSymbolValue(drvSpiInstanceSpace, "DRV_SPI_PLIB")

    dmaTxID = "DMA_CH_NEEDED_FOR_" + str(spiPeripheral) + "_Transmit"
    dmaRxID = "DMA_CH_NEEDED_FOR_" + str(spiPeripheral) + "_Receive"

    Database.setSymbolValue("core", dmaTxID, False, 2)
    Database.setSymbolValue("core", dmaRxID, False, 2)

def asyncModeOptions(Sym, event):
    if(event["value"] == False):
       Sym.setVisible(True)
    elif(event["value"] == True):
       Sym.setVisible(False)

def syncFileGen(Sym, event):
    if(event["value"] == True):
       Sym.setEnabled(True)
    elif(event["value"] == False):
       Sym.setEnabled(False)

def asyncFileGen(Sym, event):
    if(event["value"] == False):
       Sym.setEnabled(True)
    elif(event["value"] == True):
       Sym.setEnabled(False)
