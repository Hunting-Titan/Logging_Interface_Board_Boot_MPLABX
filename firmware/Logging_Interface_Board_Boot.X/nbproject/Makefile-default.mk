#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Logging_Interface_Board_Boot.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Logging_Interface_Board_Boot.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/system_config/default/framework/driver/spi/dynamic/drv_spi_tasks.c ../src/system_config/default/framework/driver/spi/dynamic/drv_spi_api.c ../src/system_config/default/framework/driver/spi/dynamic/drv_spi_master_ebm_tasks.c ../src/system_config/default/framework/driver/tmr/src/drv_tmr_static.c ../src/system_config/default/framework/driver/tmr/src/drv_tmr_mapping.c ../src/system_config/default/framework/driver/usart/src/drv_usart_mapping.c ../src/system_config/default/framework/driver/usart/src/drv_usart_static.c ../src/system_config/default/framework/driver/usart/src/drv_usart_static_byte_model.c ../src/system_config/default/framework/system/clk/src/sys_clk_pic32mz.c ../src/system_config/default/framework/system/devcon/src/sys_devcon.c ../src/system_config/default/framework/system/devcon/src/sys_devcon_pic32mz.c ../src/system_config/default/framework/system/devcon/src/sys_devcon_cache_pic32mz.S ../src/system_config/default/framework/system/ports/src/sys_ports_static.c ../src/system_config/default/system_init.c ../src/system_config/default/system_interrupt.c ../src/system_config/default/system_exceptions.c ../src/system_config/default/system_tasks.c ../src/app.c ../src/main.c ../src/switches.c ../src/timers.c ../src/crc.c ../src/commands.c ../src/statusst.c ../src/fifo.c ../src/commmodule.c ../src/document.c ../src/system_okay.c ../src/test.c ../src/gpt.c ../src/high_side.c ../src/gamma.c ../src/nvm_disk_images.c ../src/nvm_fs.c ../src/hid.c ../src/report.c ../../../../harmony/v2_06/framework/classb/src/CLASSB_CPURegistersTest.S ../../../../harmony/v2_06/framework/classb/src/CLASSB_CPUPCTest.c ../../../../harmony/v2_06/framework/classb/src/CLASSB_CRCbyte.c ../../../../harmony/v2_06/framework/classb/src/CLASSB_CRCFlashTest.c ../../../../harmony/v2_06/framework/classb/src/CLASSB_RAMCheckerBoardTest.c ../../../../harmony/v2_06/framework/classb/src/CLASSB_RAMMarchBTest.c ../../../../harmony/v2_06/framework/classb/src/CLASSB_RAMMarchCStackTest.c ../../../../harmony/v2_06/framework/classb/src/CLASSB_RAMMarchCTest.c ../../../../harmony/v2_06/framework/driver/nvm/src/dynamic/drv_nvm.c ../../../../harmony/v2_06/framework/driver/nvm/src/dynamic/drv_nvm_erasewrite.c ../../../../harmony/v2_06/framework/driver/spi/src/dynamic/drv_spi.c ../../../../harmony/v2_06/framework/driver/spi/src/drv_spi_sys_queue_fifo.c ../../../../harmony/v2_06/framework/driver/usb/usbhs/src/dynamic/drv_usbhs.c ../../../../harmony/v2_06/framework/driver/usb/usbhs/src/dynamic/drv_usbhs_device.c ../../../../harmony/v2_06/framework/system/fs/src/dynamic/sys_fs.c ../../../../harmony/v2_06/framework/system/fs/src/dynamic/sys_fs_media_manager.c ../../../../harmony/v2_06/framework/system/fs/fat_fs/src/file_system/ff.c ../../../../harmony/v2_06/framework/system/fs/fat_fs/src/hardware_access/diskio.c ../../../../harmony/v2_06/framework/system/int/src/sys_int_pic32.c ../../../../harmony/v2_06/framework/system/tmr/src/sys_tmr.c ../../../../harmony/v2_06/framework/usb/src/dynamic/usb_device.c ../../../../harmony/v2_06/framework/usb/src/dynamic/usb_device_hid.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/977502197/drv_spi_tasks.o ${OBJECTDIR}/_ext/977502197/drv_spi_api.o ${OBJECTDIR}/_ext/977502197/drv_spi_master_ebm_tasks.o ${OBJECTDIR}/_ext/1407244131/drv_tmr_static.o ${OBJECTDIR}/_ext/1407244131/drv_tmr_mapping.o ${OBJECTDIR}/_ext/327000265/drv_usart_mapping.o ${OBJECTDIR}/_ext/327000265/drv_usart_static.o ${OBJECTDIR}/_ext/327000265/drv_usart_static_byte_model.o ${OBJECTDIR}/_ext/639803181/sys_clk_pic32mz.o ${OBJECTDIR}/_ext/340578644/sys_devcon.o ${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mz.o ${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o ${OBJECTDIR}/_ext/822048611/sys_ports_static.o ${OBJECTDIR}/_ext/1688732426/system_init.o ${OBJECTDIR}/_ext/1688732426/system_interrupt.o ${OBJECTDIR}/_ext/1688732426/system_exceptions.o ${OBJECTDIR}/_ext/1688732426/system_tasks.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/switches.o ${OBJECTDIR}/_ext/1360937237/timers.o ${OBJECTDIR}/_ext/1360937237/crc.o ${OBJECTDIR}/_ext/1360937237/commands.o ${OBJECTDIR}/_ext/1360937237/statusst.o ${OBJECTDIR}/_ext/1360937237/fifo.o ${OBJECTDIR}/_ext/1360937237/commmodule.o ${OBJECTDIR}/_ext/1360937237/document.o ${OBJECTDIR}/_ext/1360937237/system_okay.o ${OBJECTDIR}/_ext/1360937237/test.o ${OBJECTDIR}/_ext/1360937237/gpt.o ${OBJECTDIR}/_ext/1360937237/high_side.o ${OBJECTDIR}/_ext/1360937237/gamma.o ${OBJECTDIR}/_ext/1360937237/nvm_disk_images.o ${OBJECTDIR}/_ext/1360937237/nvm_fs.o ${OBJECTDIR}/_ext/1360937237/hid.o ${OBJECTDIR}/_ext/1360937237/report.o ${OBJECTDIR}/_ext/2062801281/CLASSB_CPURegistersTest.o ${OBJECTDIR}/_ext/2062801281/CLASSB_CPUPCTest.o ${OBJECTDIR}/_ext/2062801281/CLASSB_CRCbyte.o ${OBJECTDIR}/_ext/2062801281/CLASSB_CRCFlashTest.o ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMCheckerBoardTest.o ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchBTest.o ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchCStackTest.o ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchCTest.o ${OBJECTDIR}/_ext/274850301/drv_nvm.o ${OBJECTDIR}/_ext/274850301/drv_nvm_erasewrite.o ${OBJECTDIR}/_ext/1415029366/drv_spi.o ${OBJECTDIR}/_ext/1745438118/drv_spi_sys_queue_fifo.o ${OBJECTDIR}/_ext/1329795486/drv_usbhs.o ${OBJECTDIR}/_ext/1329795486/drv_usbhs_device.o ${OBJECTDIR}/_ext/746721678/sys_fs.o ${OBJECTDIR}/_ext/746721678/sys_fs_media_manager.o ${OBJECTDIR}/_ext/408548909/ff.o ${OBJECTDIR}/_ext/1290481162/diskio.o ${OBJECTDIR}/_ext/2087805404/sys_int_pic32.o ${OBJECTDIR}/_ext/945675698/sys_tmr.o ${OBJECTDIR}/_ext/419360567/usb_device.o ${OBJECTDIR}/_ext/419360567/usb_device_hid.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/977502197/drv_spi_tasks.o.d ${OBJECTDIR}/_ext/977502197/drv_spi_api.o.d ${OBJECTDIR}/_ext/977502197/drv_spi_master_ebm_tasks.o.d ${OBJECTDIR}/_ext/1407244131/drv_tmr_static.o.d ${OBJECTDIR}/_ext/1407244131/drv_tmr_mapping.o.d ${OBJECTDIR}/_ext/327000265/drv_usart_mapping.o.d ${OBJECTDIR}/_ext/327000265/drv_usart_static.o.d ${OBJECTDIR}/_ext/327000265/drv_usart_static_byte_model.o.d ${OBJECTDIR}/_ext/639803181/sys_clk_pic32mz.o.d ${OBJECTDIR}/_ext/340578644/sys_devcon.o.d ${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mz.o.d ${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o.d ${OBJECTDIR}/_ext/822048611/sys_ports_static.o.d ${OBJECTDIR}/_ext/1688732426/system_init.o.d ${OBJECTDIR}/_ext/1688732426/system_interrupt.o.d ${OBJECTDIR}/_ext/1688732426/system_exceptions.o.d ${OBJECTDIR}/_ext/1688732426/system_tasks.o.d ${OBJECTDIR}/_ext/1360937237/app.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/1360937237/switches.o.d ${OBJECTDIR}/_ext/1360937237/timers.o.d ${OBJECTDIR}/_ext/1360937237/crc.o.d ${OBJECTDIR}/_ext/1360937237/commands.o.d ${OBJECTDIR}/_ext/1360937237/statusst.o.d ${OBJECTDIR}/_ext/1360937237/fifo.o.d ${OBJECTDIR}/_ext/1360937237/commmodule.o.d ${OBJECTDIR}/_ext/1360937237/document.o.d ${OBJECTDIR}/_ext/1360937237/system_okay.o.d ${OBJECTDIR}/_ext/1360937237/test.o.d ${OBJECTDIR}/_ext/1360937237/gpt.o.d ${OBJECTDIR}/_ext/1360937237/high_side.o.d ${OBJECTDIR}/_ext/1360937237/gamma.o.d ${OBJECTDIR}/_ext/1360937237/nvm_disk_images.o.d ${OBJECTDIR}/_ext/1360937237/nvm_fs.o.d ${OBJECTDIR}/_ext/1360937237/hid.o.d ${OBJECTDIR}/_ext/1360937237/report.o.d ${OBJECTDIR}/_ext/2062801281/CLASSB_CPURegistersTest.o.d ${OBJECTDIR}/_ext/2062801281/CLASSB_CPUPCTest.o.d ${OBJECTDIR}/_ext/2062801281/CLASSB_CRCbyte.o.d ${OBJECTDIR}/_ext/2062801281/CLASSB_CRCFlashTest.o.d ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMCheckerBoardTest.o.d ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchBTest.o.d ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchCStackTest.o.d ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchCTest.o.d ${OBJECTDIR}/_ext/274850301/drv_nvm.o.d ${OBJECTDIR}/_ext/274850301/drv_nvm_erasewrite.o.d ${OBJECTDIR}/_ext/1415029366/drv_spi.o.d ${OBJECTDIR}/_ext/1745438118/drv_spi_sys_queue_fifo.o.d ${OBJECTDIR}/_ext/1329795486/drv_usbhs.o.d ${OBJECTDIR}/_ext/1329795486/drv_usbhs_device.o.d ${OBJECTDIR}/_ext/746721678/sys_fs.o.d ${OBJECTDIR}/_ext/746721678/sys_fs_media_manager.o.d ${OBJECTDIR}/_ext/408548909/ff.o.d ${OBJECTDIR}/_ext/1290481162/diskio.o.d ${OBJECTDIR}/_ext/2087805404/sys_int_pic32.o.d ${OBJECTDIR}/_ext/945675698/sys_tmr.o.d ${OBJECTDIR}/_ext/419360567/usb_device.o.d ${OBJECTDIR}/_ext/419360567/usb_device_hid.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/977502197/drv_spi_tasks.o ${OBJECTDIR}/_ext/977502197/drv_spi_api.o ${OBJECTDIR}/_ext/977502197/drv_spi_master_ebm_tasks.o ${OBJECTDIR}/_ext/1407244131/drv_tmr_static.o ${OBJECTDIR}/_ext/1407244131/drv_tmr_mapping.o ${OBJECTDIR}/_ext/327000265/drv_usart_mapping.o ${OBJECTDIR}/_ext/327000265/drv_usart_static.o ${OBJECTDIR}/_ext/327000265/drv_usart_static_byte_model.o ${OBJECTDIR}/_ext/639803181/sys_clk_pic32mz.o ${OBJECTDIR}/_ext/340578644/sys_devcon.o ${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mz.o ${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o ${OBJECTDIR}/_ext/822048611/sys_ports_static.o ${OBJECTDIR}/_ext/1688732426/system_init.o ${OBJECTDIR}/_ext/1688732426/system_interrupt.o ${OBJECTDIR}/_ext/1688732426/system_exceptions.o ${OBJECTDIR}/_ext/1688732426/system_tasks.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/1360937237/switches.o ${OBJECTDIR}/_ext/1360937237/timers.o ${OBJECTDIR}/_ext/1360937237/crc.o ${OBJECTDIR}/_ext/1360937237/commands.o ${OBJECTDIR}/_ext/1360937237/statusst.o ${OBJECTDIR}/_ext/1360937237/fifo.o ${OBJECTDIR}/_ext/1360937237/commmodule.o ${OBJECTDIR}/_ext/1360937237/document.o ${OBJECTDIR}/_ext/1360937237/system_okay.o ${OBJECTDIR}/_ext/1360937237/test.o ${OBJECTDIR}/_ext/1360937237/gpt.o ${OBJECTDIR}/_ext/1360937237/high_side.o ${OBJECTDIR}/_ext/1360937237/gamma.o ${OBJECTDIR}/_ext/1360937237/nvm_disk_images.o ${OBJECTDIR}/_ext/1360937237/nvm_fs.o ${OBJECTDIR}/_ext/1360937237/hid.o ${OBJECTDIR}/_ext/1360937237/report.o ${OBJECTDIR}/_ext/2062801281/CLASSB_CPURegistersTest.o ${OBJECTDIR}/_ext/2062801281/CLASSB_CPUPCTest.o ${OBJECTDIR}/_ext/2062801281/CLASSB_CRCbyte.o ${OBJECTDIR}/_ext/2062801281/CLASSB_CRCFlashTest.o ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMCheckerBoardTest.o ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchBTest.o ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchCStackTest.o ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchCTest.o ${OBJECTDIR}/_ext/274850301/drv_nvm.o ${OBJECTDIR}/_ext/274850301/drv_nvm_erasewrite.o ${OBJECTDIR}/_ext/1415029366/drv_spi.o ${OBJECTDIR}/_ext/1745438118/drv_spi_sys_queue_fifo.o ${OBJECTDIR}/_ext/1329795486/drv_usbhs.o ${OBJECTDIR}/_ext/1329795486/drv_usbhs_device.o ${OBJECTDIR}/_ext/746721678/sys_fs.o ${OBJECTDIR}/_ext/746721678/sys_fs_media_manager.o ${OBJECTDIR}/_ext/408548909/ff.o ${OBJECTDIR}/_ext/1290481162/diskio.o ${OBJECTDIR}/_ext/2087805404/sys_int_pic32.o ${OBJECTDIR}/_ext/945675698/sys_tmr.o ${OBJECTDIR}/_ext/419360567/usb_device.o ${OBJECTDIR}/_ext/419360567/usb_device_hid.o

# Source Files
SOURCEFILES=../src/system_config/default/framework/driver/spi/dynamic/drv_spi_tasks.c ../src/system_config/default/framework/driver/spi/dynamic/drv_spi_api.c ../src/system_config/default/framework/driver/spi/dynamic/drv_spi_master_ebm_tasks.c ../src/system_config/default/framework/driver/tmr/src/drv_tmr_static.c ../src/system_config/default/framework/driver/tmr/src/drv_tmr_mapping.c ../src/system_config/default/framework/driver/usart/src/drv_usart_mapping.c ../src/system_config/default/framework/driver/usart/src/drv_usart_static.c ../src/system_config/default/framework/driver/usart/src/drv_usart_static_byte_model.c ../src/system_config/default/framework/system/clk/src/sys_clk_pic32mz.c ../src/system_config/default/framework/system/devcon/src/sys_devcon.c ../src/system_config/default/framework/system/devcon/src/sys_devcon_pic32mz.c ../src/system_config/default/framework/system/devcon/src/sys_devcon_cache_pic32mz.S ../src/system_config/default/framework/system/ports/src/sys_ports_static.c ../src/system_config/default/system_init.c ../src/system_config/default/system_interrupt.c ../src/system_config/default/system_exceptions.c ../src/system_config/default/system_tasks.c ../src/app.c ../src/main.c ../src/switches.c ../src/timers.c ../src/crc.c ../src/commands.c ../src/statusst.c ../src/fifo.c ../src/commmodule.c ../src/document.c ../src/system_okay.c ../src/test.c ../src/gpt.c ../src/high_side.c ../src/gamma.c ../src/nvm_disk_images.c ../src/nvm_fs.c ../src/hid.c ../src/report.c ../../../../harmony/v2_06/framework/classb/src/CLASSB_CPURegistersTest.S ../../../../harmony/v2_06/framework/classb/src/CLASSB_CPUPCTest.c ../../../../harmony/v2_06/framework/classb/src/CLASSB_CRCbyte.c ../../../../harmony/v2_06/framework/classb/src/CLASSB_CRCFlashTest.c ../../../../harmony/v2_06/framework/classb/src/CLASSB_RAMCheckerBoardTest.c ../../../../harmony/v2_06/framework/classb/src/CLASSB_RAMMarchBTest.c ../../../../harmony/v2_06/framework/classb/src/CLASSB_RAMMarchCStackTest.c ../../../../harmony/v2_06/framework/classb/src/CLASSB_RAMMarchCTest.c ../../../../harmony/v2_06/framework/driver/nvm/src/dynamic/drv_nvm.c ../../../../harmony/v2_06/framework/driver/nvm/src/dynamic/drv_nvm_erasewrite.c ../../../../harmony/v2_06/framework/driver/spi/src/dynamic/drv_spi.c ../../../../harmony/v2_06/framework/driver/spi/src/drv_spi_sys_queue_fifo.c ../../../../harmony/v2_06/framework/driver/usb/usbhs/src/dynamic/drv_usbhs.c ../../../../harmony/v2_06/framework/driver/usb/usbhs/src/dynamic/drv_usbhs_device.c ../../../../harmony/v2_06/framework/system/fs/src/dynamic/sys_fs.c ../../../../harmony/v2_06/framework/system/fs/src/dynamic/sys_fs_media_manager.c ../../../../harmony/v2_06/framework/system/fs/fat_fs/src/file_system/ff.c ../../../../harmony/v2_06/framework/system/fs/fat_fs/src/hardware_access/diskio.c ../../../../harmony/v2_06/framework/system/int/src/sys_int_pic32.c ../../../../harmony/v2_06/framework/system/tmr/src/sys_tmr.c ../../../../harmony/v2_06/framework/usb/src/dynamic/usb_device.c ../../../../harmony/v2_06/framework/usb/src/dynamic/usb_device_hid.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/Logging_Interface_Board_Boot.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MZ2048EFH144
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o: ../src/system_config/default/framework/system/devcon/src/sys_devcon_cache_pic32mz.S  .generated_files/flags/default/84f8de36ab630175b2ca59ed19f02a42d4bd72e0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/340578644" 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o.d 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o.ok ${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1 -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o.d"  -o ${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o ../src/system_config/default/framework/system/devcon/src/sys_devcon_cache_pic32mz.S  -DXPRJ_default=$(CND_CONF)  -legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD5=1 -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o.d" "${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2062801281/CLASSB_CPURegistersTest.o: ../../../../harmony/v2_06/framework/classb/src/CLASSB_CPURegistersTest.S  .generated_files/flags/default/6b302bb1481bf0875cfd48913ce0990b0ec4f0c6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2062801281" 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_CPURegistersTest.o.d 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_CPURegistersTest.o 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_CPURegistersTest.o.ok ${OBJECTDIR}/_ext/2062801281/CLASSB_CPURegistersTest.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1 -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2062801281/CLASSB_CPURegistersTest.o.d"  -o ${OBJECTDIR}/_ext/2062801281/CLASSB_CPURegistersTest.o ../../../../harmony/v2_06/framework/classb/src/CLASSB_CPURegistersTest.S  -DXPRJ_default=$(CND_CONF)  -legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/2062801281/CLASSB_CPURegistersTest.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD5=1 -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/2062801281/CLASSB_CPURegistersTest.o.d" "${OBJECTDIR}/_ext/2062801281/CLASSB_CPURegistersTest.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o: ../src/system_config/default/framework/system/devcon/src/sys_devcon_cache_pic32mz.S  .generated_files/flags/default/4ba195afaa0accdd8c3bb4c2d689b799ef388b27 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/340578644" 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o.d 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o.ok ${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o.d"  -o ${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o ../src/system_config/default/framework/system/devcon/src/sys_devcon_cache_pic32mz.S  -DXPRJ_default=$(CND_CONF)  -legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o.asm.d",--gdwarf-2 -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o.d" "${OBJECTDIR}/_ext/340578644/sys_devcon_cache_pic32mz.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/2062801281/CLASSB_CPURegistersTest.o: ../../../../harmony/v2_06/framework/classb/src/CLASSB_CPURegistersTest.S  .generated_files/flags/default/a2bfb97e124e5972d7fec54c04640a343280d1fb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2062801281" 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_CPURegistersTest.o.d 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_CPURegistersTest.o 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_CPURegistersTest.o.ok ${OBJECTDIR}/_ext/2062801281/CLASSB_CPURegistersTest.o.err 
	${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2062801281/CLASSB_CPURegistersTest.o.d"  -o ${OBJECTDIR}/_ext/2062801281/CLASSB_CPURegistersTest.o ../../../../harmony/v2_06/framework/classb/src/CLASSB_CPURegistersTest.S  -DXPRJ_default=$(CND_CONF)  -legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/2062801281/CLASSB_CPURegistersTest.o.asm.d",--gdwarf-2 -mdfp="${DFP_DIR}"
	@${FIXDEPS} "${OBJECTDIR}/_ext/2062801281/CLASSB_CPURegistersTest.o.d" "${OBJECTDIR}/_ext/2062801281/CLASSB_CPURegistersTest.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/977502197/drv_spi_tasks.o: ../src/system_config/default/framework/driver/spi/dynamic/drv_spi_tasks.c  .generated_files/flags/default/6f39cbf0cdceebbf3ec17a822c7064194cd52fb8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/977502197" 
	@${RM} ${OBJECTDIR}/_ext/977502197/drv_spi_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/977502197/drv_spi_tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/977502197/drv_spi_tasks.o.d" -o ${OBJECTDIR}/_ext/977502197/drv_spi_tasks.o ../src/system_config/default/framework/driver/spi/dynamic/drv_spi_tasks.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/977502197/drv_spi_api.o: ../src/system_config/default/framework/driver/spi/dynamic/drv_spi_api.c  .generated_files/flags/default/b3a5f4d1e190eb87473ccca9739b994c9b084e16 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/977502197" 
	@${RM} ${OBJECTDIR}/_ext/977502197/drv_spi_api.o.d 
	@${RM} ${OBJECTDIR}/_ext/977502197/drv_spi_api.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/977502197/drv_spi_api.o.d" -o ${OBJECTDIR}/_ext/977502197/drv_spi_api.o ../src/system_config/default/framework/driver/spi/dynamic/drv_spi_api.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/977502197/drv_spi_master_ebm_tasks.o: ../src/system_config/default/framework/driver/spi/dynamic/drv_spi_master_ebm_tasks.c  .generated_files/flags/default/46d57dfb376f090514132d5e685c41b6e83dde84 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/977502197" 
	@${RM} ${OBJECTDIR}/_ext/977502197/drv_spi_master_ebm_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/977502197/drv_spi_master_ebm_tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/977502197/drv_spi_master_ebm_tasks.o.d" -o ${OBJECTDIR}/_ext/977502197/drv_spi_master_ebm_tasks.o ../src/system_config/default/framework/driver/spi/dynamic/drv_spi_master_ebm_tasks.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1407244131/drv_tmr_static.o: ../src/system_config/default/framework/driver/tmr/src/drv_tmr_static.c  .generated_files/flags/default/13a84d3c9f183cf9bf8b662e995fe871a6264fec .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1407244131" 
	@${RM} ${OBJECTDIR}/_ext/1407244131/drv_tmr_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/1407244131/drv_tmr_static.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1407244131/drv_tmr_static.o.d" -o ${OBJECTDIR}/_ext/1407244131/drv_tmr_static.o ../src/system_config/default/framework/driver/tmr/src/drv_tmr_static.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1407244131/drv_tmr_mapping.o: ../src/system_config/default/framework/driver/tmr/src/drv_tmr_mapping.c  .generated_files/flags/default/c24c446bb7fd5a063f0e42229d61deaedc1e6f12 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1407244131" 
	@${RM} ${OBJECTDIR}/_ext/1407244131/drv_tmr_mapping.o.d 
	@${RM} ${OBJECTDIR}/_ext/1407244131/drv_tmr_mapping.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1407244131/drv_tmr_mapping.o.d" -o ${OBJECTDIR}/_ext/1407244131/drv_tmr_mapping.o ../src/system_config/default/framework/driver/tmr/src/drv_tmr_mapping.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/327000265/drv_usart_mapping.o: ../src/system_config/default/framework/driver/usart/src/drv_usart_mapping.c  .generated_files/flags/default/ea8a16f6777146b8c51ab0ad38776a7a515541e2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/327000265" 
	@${RM} ${OBJECTDIR}/_ext/327000265/drv_usart_mapping.o.d 
	@${RM} ${OBJECTDIR}/_ext/327000265/drv_usart_mapping.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/327000265/drv_usart_mapping.o.d" -o ${OBJECTDIR}/_ext/327000265/drv_usart_mapping.o ../src/system_config/default/framework/driver/usart/src/drv_usart_mapping.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/327000265/drv_usart_static.o: ../src/system_config/default/framework/driver/usart/src/drv_usart_static.c  .generated_files/flags/default/1afabbf824e95118118b5d75fb30a44073879606 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/327000265" 
	@${RM} ${OBJECTDIR}/_ext/327000265/drv_usart_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/327000265/drv_usart_static.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/327000265/drv_usart_static.o.d" -o ${OBJECTDIR}/_ext/327000265/drv_usart_static.o ../src/system_config/default/framework/driver/usart/src/drv_usart_static.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/327000265/drv_usart_static_byte_model.o: ../src/system_config/default/framework/driver/usart/src/drv_usart_static_byte_model.c  .generated_files/flags/default/7a9c9879981015cad7f6a057a055138180825609 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/327000265" 
	@${RM} ${OBJECTDIR}/_ext/327000265/drv_usart_static_byte_model.o.d 
	@${RM} ${OBJECTDIR}/_ext/327000265/drv_usart_static_byte_model.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/327000265/drv_usart_static_byte_model.o.d" -o ${OBJECTDIR}/_ext/327000265/drv_usart_static_byte_model.o ../src/system_config/default/framework/driver/usart/src/drv_usart_static_byte_model.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/639803181/sys_clk_pic32mz.o: ../src/system_config/default/framework/system/clk/src/sys_clk_pic32mz.c  .generated_files/flags/default/7630d3c3cdd95bfed652283c6bfb87b9a9f69adf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/639803181" 
	@${RM} ${OBJECTDIR}/_ext/639803181/sys_clk_pic32mz.o.d 
	@${RM} ${OBJECTDIR}/_ext/639803181/sys_clk_pic32mz.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/639803181/sys_clk_pic32mz.o.d" -o ${OBJECTDIR}/_ext/639803181/sys_clk_pic32mz.o ../src/system_config/default/framework/system/clk/src/sys_clk_pic32mz.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/340578644/sys_devcon.o: ../src/system_config/default/framework/system/devcon/src/sys_devcon.c  .generated_files/flags/default/a63e0b6b4997a16005b13fe8922d97d493c8546 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/340578644" 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon.o.d 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/340578644/sys_devcon.o.d" -o ${OBJECTDIR}/_ext/340578644/sys_devcon.o ../src/system_config/default/framework/system/devcon/src/sys_devcon.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mz.o: ../src/system_config/default/framework/system/devcon/src/sys_devcon_pic32mz.c  .generated_files/flags/default/e5f841d05e66ddf6ab1212ee54040534e8a81fb9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/340578644" 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mz.o.d 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mz.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mz.o.d" -o ${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mz.o ../src/system_config/default/framework/system/devcon/src/sys_devcon_pic32mz.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/822048611/sys_ports_static.o: ../src/system_config/default/framework/system/ports/src/sys_ports_static.c  .generated_files/flags/default/b4d3e4d1e3b2bace87b79fc9f9c38f6fc3c40e7d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/822048611" 
	@${RM} ${OBJECTDIR}/_ext/822048611/sys_ports_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/822048611/sys_ports_static.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/822048611/sys_ports_static.o.d" -o ${OBJECTDIR}/_ext/822048611/sys_ports_static.o ../src/system_config/default/framework/system/ports/src/sys_ports_static.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1688732426/system_init.o: ../src/system_config/default/system_init.c  .generated_files/flags/default/25973692c44674d0074485cbecc9dc8157078c00 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1688732426" 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_init.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1688732426/system_init.o.d" -o ${OBJECTDIR}/_ext/1688732426/system_init.o ../src/system_config/default/system_init.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1688732426/system_interrupt.o: ../src/system_config/default/system_interrupt.c  .generated_files/flags/default/8b9a7520bd01a1e5bd0bb147484303a77387f7db .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1688732426" 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_interrupt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1688732426/system_interrupt.o.d" -o ${OBJECTDIR}/_ext/1688732426/system_interrupt.o ../src/system_config/default/system_interrupt.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1688732426/system_exceptions.o: ../src/system_config/default/system_exceptions.c  .generated_files/flags/default/cce86550b09ff0f664dd395cf4cac6f720d3d22d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1688732426" 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1688732426/system_exceptions.o.d" -o ${OBJECTDIR}/_ext/1688732426/system_exceptions.o ../src/system_config/default/system_exceptions.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1688732426/system_tasks.o: ../src/system_config/default/system_tasks.c  .generated_files/flags/default/af358f82f7279eb17e3e12bb86fcdae8a04ae9eb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1688732426" 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1688732426/system_tasks.o.d" -o ${OBJECTDIR}/_ext/1688732426/system_tasks.o ../src/system_config/default/system_tasks.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  .generated_files/flags/default/dcd143c0e265ed908d8cd2a88c29a8bd9dafefe5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/flags/default/8758ce005b1242480cd3a918700430062f656894 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/switches.o: ../src/switches.c  .generated_files/flags/default/57512da34afa364add18400f2fc1208c772dd416 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/switches.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/switches.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/switches.o.d" -o ${OBJECTDIR}/_ext/1360937237/switches.o ../src/switches.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/timers.o: ../src/timers.c  .generated_files/flags/default/3708fc131134506d3ab74a02be93d802781436db .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/timers.o.d" -o ${OBJECTDIR}/_ext/1360937237/timers.o ../src/timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/crc.o: ../src/crc.c  .generated_files/flags/default/939c109a96de5d08e6cc51440c3c3f1d0ea5e140 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/crc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/crc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/crc.o.d" -o ${OBJECTDIR}/_ext/1360937237/crc.o ../src/crc.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/commands.o: ../src/commands.c  .generated_files/flags/default/7a824b060680b3639f151d32c7aab14d88344dd1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/commands.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/commands.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/commands.o.d" -o ${OBJECTDIR}/_ext/1360937237/commands.o ../src/commands.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/statusst.o: ../src/statusst.c  .generated_files/flags/default/53841f7d576bf323c38cfb34941efc776eb5bd5e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/statusst.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/statusst.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/statusst.o.d" -o ${OBJECTDIR}/_ext/1360937237/statusst.o ../src/statusst.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/fifo.o: ../src/fifo.c  .generated_files/flags/default/50af7a39db49f276ab77934c2a52cd4ea23016ee .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/fifo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/fifo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/fifo.o.d" -o ${OBJECTDIR}/_ext/1360937237/fifo.o ../src/fifo.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/commmodule.o: ../src/commmodule.c  .generated_files/flags/default/606440a75450951c201ccd378ef07d7f59c5d670 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/commmodule.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/commmodule.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/commmodule.o.d" -o ${OBJECTDIR}/_ext/1360937237/commmodule.o ../src/commmodule.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/document.o: ../src/document.c  .generated_files/flags/default/3d5d6cfa8932130f5f96b7d4ad0781d9bb1edf1f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/document.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/document.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/document.o.d" -o ${OBJECTDIR}/_ext/1360937237/document.o ../src/document.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/system_okay.o: ../src/system_okay.c  .generated_files/flags/default/ef7b9dfd861d1a0ca9791fd6bc341a3753df0c3b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/system_okay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/system_okay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/system_okay.o.d" -o ${OBJECTDIR}/_ext/1360937237/system_okay.o ../src/system_okay.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/test.o: ../src/test.c  .generated_files/flags/default/4927264afe26bf3b7186986ea73a2bd50153d4bc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/test.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/test.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/test.o.d" -o ${OBJECTDIR}/_ext/1360937237/test.o ../src/test.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/gpt.o: ../src/gpt.c  .generated_files/flags/default/9e89598e9546101728a180987f2bc7cad31fd67 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/gpt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/gpt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/gpt.o.d" -o ${OBJECTDIR}/_ext/1360937237/gpt.o ../src/gpt.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/high_side.o: ../src/high_side.c  .generated_files/flags/default/40b1b6c1e48181213be867322c7961e9271cf479 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/high_side.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/high_side.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/high_side.o.d" -o ${OBJECTDIR}/_ext/1360937237/high_side.o ../src/high_side.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/gamma.o: ../src/gamma.c  .generated_files/flags/default/7e372ed8b4aa69136ab44315737c7b2f78e69d5b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/gamma.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/gamma.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/gamma.o.d" -o ${OBJECTDIR}/_ext/1360937237/gamma.o ../src/gamma.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/nvm_disk_images.o: ../src/nvm_disk_images.c  .generated_files/flags/default/a82bd875375915461088577ec1a836a4bd6362fb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/nvm_disk_images.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/nvm_disk_images.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/nvm_disk_images.o.d" -o ${OBJECTDIR}/_ext/1360937237/nvm_disk_images.o ../src/nvm_disk_images.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/nvm_fs.o: ../src/nvm_fs.c  .generated_files/flags/default/1d8380645726cfbb13e16f766b5986fc15c5757 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/nvm_fs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/nvm_fs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/nvm_fs.o.d" -o ${OBJECTDIR}/_ext/1360937237/nvm_fs.o ../src/nvm_fs.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/hid.o: ../src/hid.c  .generated_files/flags/default/c3d4cab8e18e3b1f3eb02028143e22861b92e8ca .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/hid.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/hid.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/hid.o.d" -o ${OBJECTDIR}/_ext/1360937237/hid.o ../src/hid.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/report.o: ../src/report.c  .generated_files/flags/default/9147ee0f716fcb010f796b155e008291d19fb1ef .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/report.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/report.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/report.o.d" -o ${OBJECTDIR}/_ext/1360937237/report.o ../src/report.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2062801281/CLASSB_CPUPCTest.o: ../../../../harmony/v2_06/framework/classb/src/CLASSB_CPUPCTest.c  .generated_files/flags/default/b111926aeb18235c064b496f33cfef62e36638a4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2062801281" 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_CPUPCTest.o.d 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_CPUPCTest.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/2062801281/CLASSB_CPUPCTest.o.d" -o ${OBJECTDIR}/_ext/2062801281/CLASSB_CPUPCTest.o ../../../../harmony/v2_06/framework/classb/src/CLASSB_CPUPCTest.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2062801281/CLASSB_CRCbyte.o: ../../../../harmony/v2_06/framework/classb/src/CLASSB_CRCbyte.c  .generated_files/flags/default/8be852f12d8b37949f17bab15f1518b1de4b219c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2062801281" 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_CRCbyte.o.d 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_CRCbyte.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/2062801281/CLASSB_CRCbyte.o.d" -o ${OBJECTDIR}/_ext/2062801281/CLASSB_CRCbyte.o ../../../../harmony/v2_06/framework/classb/src/CLASSB_CRCbyte.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2062801281/CLASSB_CRCFlashTest.o: ../../../../harmony/v2_06/framework/classb/src/CLASSB_CRCFlashTest.c  .generated_files/flags/default/8488047a5248f0855d40411250dd98a826aa636c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2062801281" 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_CRCFlashTest.o.d 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_CRCFlashTest.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/2062801281/CLASSB_CRCFlashTest.o.d" -o ${OBJECTDIR}/_ext/2062801281/CLASSB_CRCFlashTest.o ../../../../harmony/v2_06/framework/classb/src/CLASSB_CRCFlashTest.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2062801281/CLASSB_RAMCheckerBoardTest.o: ../../../../harmony/v2_06/framework/classb/src/CLASSB_RAMCheckerBoardTest.c  .generated_files/flags/default/91603823c2db1ac57b507770dcbcd80dda0bd246 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2062801281" 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMCheckerBoardTest.o.d 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMCheckerBoardTest.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/2062801281/CLASSB_RAMCheckerBoardTest.o.d" -o ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMCheckerBoardTest.o ../../../../harmony/v2_06/framework/classb/src/CLASSB_RAMCheckerBoardTest.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchBTest.o: ../../../../harmony/v2_06/framework/classb/src/CLASSB_RAMMarchBTest.c  .generated_files/flags/default/b216b7da236523eb3a3c6880e0a9bf3155af38cd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2062801281" 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchBTest.o.d 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchBTest.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchBTest.o.d" -o ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchBTest.o ../../../../harmony/v2_06/framework/classb/src/CLASSB_RAMMarchBTest.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchCStackTest.o: ../../../../harmony/v2_06/framework/classb/src/CLASSB_RAMMarchCStackTest.c  .generated_files/flags/default/857b71ad18799c291dc047c54f7cb153500574ba .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2062801281" 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchCStackTest.o.d 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchCStackTest.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchCStackTest.o.d" -o ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchCStackTest.o ../../../../harmony/v2_06/framework/classb/src/CLASSB_RAMMarchCStackTest.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchCTest.o: ../../../../harmony/v2_06/framework/classb/src/CLASSB_RAMMarchCTest.c  .generated_files/flags/default/fcad64e0423e2477b576e5415816ed7c852807f1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2062801281" 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchCTest.o.d 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchCTest.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchCTest.o.d" -o ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchCTest.o ../../../../harmony/v2_06/framework/classb/src/CLASSB_RAMMarchCTest.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/274850301/drv_nvm.o: ../../../../harmony/v2_06/framework/driver/nvm/src/dynamic/drv_nvm.c  .generated_files/flags/default/4e112254c21521090cd28643a6e317748b457206 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/274850301" 
	@${RM} ${OBJECTDIR}/_ext/274850301/drv_nvm.o.d 
	@${RM} ${OBJECTDIR}/_ext/274850301/drv_nvm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/274850301/drv_nvm.o.d" -o ${OBJECTDIR}/_ext/274850301/drv_nvm.o ../../../../harmony/v2_06/framework/driver/nvm/src/dynamic/drv_nvm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/274850301/drv_nvm_erasewrite.o: ../../../../harmony/v2_06/framework/driver/nvm/src/dynamic/drv_nvm_erasewrite.c  .generated_files/flags/default/cba0a311594bf19e21b41a23f8ade4a75f707177 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/274850301" 
	@${RM} ${OBJECTDIR}/_ext/274850301/drv_nvm_erasewrite.o.d 
	@${RM} ${OBJECTDIR}/_ext/274850301/drv_nvm_erasewrite.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/274850301/drv_nvm_erasewrite.o.d" -o ${OBJECTDIR}/_ext/274850301/drv_nvm_erasewrite.o ../../../../harmony/v2_06/framework/driver/nvm/src/dynamic/drv_nvm_erasewrite.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1415029366/drv_spi.o: ../../../../harmony/v2_06/framework/driver/spi/src/dynamic/drv_spi.c  .generated_files/flags/default/458d3f23fb4e41d6572ea702356c9a354a5dfd19 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1415029366" 
	@${RM} ${OBJECTDIR}/_ext/1415029366/drv_spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1415029366/drv_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1415029366/drv_spi.o.d" -o ${OBJECTDIR}/_ext/1415029366/drv_spi.o ../../../../harmony/v2_06/framework/driver/spi/src/dynamic/drv_spi.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745438118/drv_spi_sys_queue_fifo.o: ../../../../harmony/v2_06/framework/driver/spi/src/drv_spi_sys_queue_fifo.c  .generated_files/flags/default/a189eceeb73fdcef6ee1369575e6722622a1322 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1745438118" 
	@${RM} ${OBJECTDIR}/_ext/1745438118/drv_spi_sys_queue_fifo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745438118/drv_spi_sys_queue_fifo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1745438118/drv_spi_sys_queue_fifo.o.d" -o ${OBJECTDIR}/_ext/1745438118/drv_spi_sys_queue_fifo.o ../../../../harmony/v2_06/framework/driver/spi/src/drv_spi_sys_queue_fifo.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1329795486/drv_usbhs.o: ../../../../harmony/v2_06/framework/driver/usb/usbhs/src/dynamic/drv_usbhs.c  .generated_files/flags/default/c6f9c19716fc7560f46c23a141fd6d7dd628cfdc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1329795486" 
	@${RM} ${OBJECTDIR}/_ext/1329795486/drv_usbhs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1329795486/drv_usbhs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1329795486/drv_usbhs.o.d" -o ${OBJECTDIR}/_ext/1329795486/drv_usbhs.o ../../../../harmony/v2_06/framework/driver/usb/usbhs/src/dynamic/drv_usbhs.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1329795486/drv_usbhs_device.o: ../../../../harmony/v2_06/framework/driver/usb/usbhs/src/dynamic/drv_usbhs_device.c  .generated_files/flags/default/871604cfabc6e40ca5748729f6e84801ca3329b5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1329795486" 
	@${RM} ${OBJECTDIR}/_ext/1329795486/drv_usbhs_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1329795486/drv_usbhs_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1329795486/drv_usbhs_device.o.d" -o ${OBJECTDIR}/_ext/1329795486/drv_usbhs_device.o ../../../../harmony/v2_06/framework/driver/usb/usbhs/src/dynamic/drv_usbhs_device.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/746721678/sys_fs.o: ../../../../harmony/v2_06/framework/system/fs/src/dynamic/sys_fs.c  .generated_files/flags/default/6bc618fda626be12e6f08d2fcc69bf3ca3f27b21 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/746721678" 
	@${RM} ${OBJECTDIR}/_ext/746721678/sys_fs.o.d 
	@${RM} ${OBJECTDIR}/_ext/746721678/sys_fs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/746721678/sys_fs.o.d" -o ${OBJECTDIR}/_ext/746721678/sys_fs.o ../../../../harmony/v2_06/framework/system/fs/src/dynamic/sys_fs.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/746721678/sys_fs_media_manager.o: ../../../../harmony/v2_06/framework/system/fs/src/dynamic/sys_fs_media_manager.c  .generated_files/flags/default/27b77191983c4692e851ef0e8ef4de99cf21c20e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/746721678" 
	@${RM} ${OBJECTDIR}/_ext/746721678/sys_fs_media_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/746721678/sys_fs_media_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/746721678/sys_fs_media_manager.o.d" -o ${OBJECTDIR}/_ext/746721678/sys_fs_media_manager.o ../../../../harmony/v2_06/framework/system/fs/src/dynamic/sys_fs_media_manager.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/408548909/ff.o: ../../../../harmony/v2_06/framework/system/fs/fat_fs/src/file_system/ff.c  .generated_files/flags/default/f2ddedf0cc36d8da7f005a4e3f38fa20db16646d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/408548909" 
	@${RM} ${OBJECTDIR}/_ext/408548909/ff.o.d 
	@${RM} ${OBJECTDIR}/_ext/408548909/ff.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/408548909/ff.o.d" -o ${OBJECTDIR}/_ext/408548909/ff.o ../../../../harmony/v2_06/framework/system/fs/fat_fs/src/file_system/ff.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1290481162/diskio.o: ../../../../harmony/v2_06/framework/system/fs/fat_fs/src/hardware_access/diskio.c  .generated_files/flags/default/beaf9c248ec59e2437db2fdab39c88cc259943bb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1290481162" 
	@${RM} ${OBJECTDIR}/_ext/1290481162/diskio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1290481162/diskio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1290481162/diskio.o.d" -o ${OBJECTDIR}/_ext/1290481162/diskio.o ../../../../harmony/v2_06/framework/system/fs/fat_fs/src/hardware_access/diskio.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2087805404/sys_int_pic32.o: ../../../../harmony/v2_06/framework/system/int/src/sys_int_pic32.c  .generated_files/flags/default/75b30f4684f7da7151cc8e7a40af8fa6e1a26dc7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2087805404" 
	@${RM} ${OBJECTDIR}/_ext/2087805404/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/2087805404/sys_int_pic32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/2087805404/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/2087805404/sys_int_pic32.o ../../../../harmony/v2_06/framework/system/int/src/sys_int_pic32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/945675698/sys_tmr.o: ../../../../harmony/v2_06/framework/system/tmr/src/sys_tmr.c  .generated_files/flags/default/148539f32ba761f079cf4dbad10edf40fbabb813 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/945675698" 
	@${RM} ${OBJECTDIR}/_ext/945675698/sys_tmr.o.d 
	@${RM} ${OBJECTDIR}/_ext/945675698/sys_tmr.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/945675698/sys_tmr.o.d" -o ${OBJECTDIR}/_ext/945675698/sys_tmr.o ../../../../harmony/v2_06/framework/system/tmr/src/sys_tmr.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/419360567/usb_device.o: ../../../../harmony/v2_06/framework/usb/src/dynamic/usb_device.c  .generated_files/flags/default/2e9b8390e6e245724de55b23ed8e3717c9960b94 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/419360567" 
	@${RM} ${OBJECTDIR}/_ext/419360567/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/419360567/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/419360567/usb_device.o.d" -o ${OBJECTDIR}/_ext/419360567/usb_device.o ../../../../harmony/v2_06/framework/usb/src/dynamic/usb_device.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/419360567/usb_device_hid.o: ../../../../harmony/v2_06/framework/usb/src/dynamic/usb_device_hid.c  .generated_files/flags/default/635d60cc0b4b11355c5b952dd55b85b9e534d86c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/419360567" 
	@${RM} ${OBJECTDIR}/_ext/419360567/usb_device_hid.o.d 
	@${RM} ${OBJECTDIR}/_ext/419360567/usb_device_hid.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD5=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/419360567/usb_device_hid.o.d" -o ${OBJECTDIR}/_ext/419360567/usb_device_hid.o ../../../../harmony/v2_06/framework/usb/src/dynamic/usb_device_hid.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/977502197/drv_spi_tasks.o: ../src/system_config/default/framework/driver/spi/dynamic/drv_spi_tasks.c  .generated_files/flags/default/91640abc96b0f8394bfa0cfeef0116c2be260ef .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/977502197" 
	@${RM} ${OBJECTDIR}/_ext/977502197/drv_spi_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/977502197/drv_spi_tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/977502197/drv_spi_tasks.o.d" -o ${OBJECTDIR}/_ext/977502197/drv_spi_tasks.o ../src/system_config/default/framework/driver/spi/dynamic/drv_spi_tasks.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/977502197/drv_spi_api.o: ../src/system_config/default/framework/driver/spi/dynamic/drv_spi_api.c  .generated_files/flags/default/e00657b435d7b8d155b1c2afa6d7c09dbfa84e81 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/977502197" 
	@${RM} ${OBJECTDIR}/_ext/977502197/drv_spi_api.o.d 
	@${RM} ${OBJECTDIR}/_ext/977502197/drv_spi_api.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/977502197/drv_spi_api.o.d" -o ${OBJECTDIR}/_ext/977502197/drv_spi_api.o ../src/system_config/default/framework/driver/spi/dynamic/drv_spi_api.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/977502197/drv_spi_master_ebm_tasks.o: ../src/system_config/default/framework/driver/spi/dynamic/drv_spi_master_ebm_tasks.c  .generated_files/flags/default/e9507958357c188be5afa5d9a7ef15e385e4bca0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/977502197" 
	@${RM} ${OBJECTDIR}/_ext/977502197/drv_spi_master_ebm_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/977502197/drv_spi_master_ebm_tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/977502197/drv_spi_master_ebm_tasks.o.d" -o ${OBJECTDIR}/_ext/977502197/drv_spi_master_ebm_tasks.o ../src/system_config/default/framework/driver/spi/dynamic/drv_spi_master_ebm_tasks.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1407244131/drv_tmr_static.o: ../src/system_config/default/framework/driver/tmr/src/drv_tmr_static.c  .generated_files/flags/default/bc97323f48bb3900db2b9446ae8426ed602be292 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1407244131" 
	@${RM} ${OBJECTDIR}/_ext/1407244131/drv_tmr_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/1407244131/drv_tmr_static.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1407244131/drv_tmr_static.o.d" -o ${OBJECTDIR}/_ext/1407244131/drv_tmr_static.o ../src/system_config/default/framework/driver/tmr/src/drv_tmr_static.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1407244131/drv_tmr_mapping.o: ../src/system_config/default/framework/driver/tmr/src/drv_tmr_mapping.c  .generated_files/flags/default/2350a34b81079b566965e3f80ee7c8893b2a429c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1407244131" 
	@${RM} ${OBJECTDIR}/_ext/1407244131/drv_tmr_mapping.o.d 
	@${RM} ${OBJECTDIR}/_ext/1407244131/drv_tmr_mapping.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1407244131/drv_tmr_mapping.o.d" -o ${OBJECTDIR}/_ext/1407244131/drv_tmr_mapping.o ../src/system_config/default/framework/driver/tmr/src/drv_tmr_mapping.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/327000265/drv_usart_mapping.o: ../src/system_config/default/framework/driver/usart/src/drv_usart_mapping.c  .generated_files/flags/default/13c0dbdc09f1fbfa197b6bdcbc547152edcda8b4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/327000265" 
	@${RM} ${OBJECTDIR}/_ext/327000265/drv_usart_mapping.o.d 
	@${RM} ${OBJECTDIR}/_ext/327000265/drv_usart_mapping.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/327000265/drv_usart_mapping.o.d" -o ${OBJECTDIR}/_ext/327000265/drv_usart_mapping.o ../src/system_config/default/framework/driver/usart/src/drv_usart_mapping.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/327000265/drv_usart_static.o: ../src/system_config/default/framework/driver/usart/src/drv_usart_static.c  .generated_files/flags/default/2a756d441ef6fed3ab225d7b3bbfb855b19ea467 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/327000265" 
	@${RM} ${OBJECTDIR}/_ext/327000265/drv_usart_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/327000265/drv_usart_static.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/327000265/drv_usart_static.o.d" -o ${OBJECTDIR}/_ext/327000265/drv_usart_static.o ../src/system_config/default/framework/driver/usart/src/drv_usart_static.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/327000265/drv_usart_static_byte_model.o: ../src/system_config/default/framework/driver/usart/src/drv_usart_static_byte_model.c  .generated_files/flags/default/310c261f8b6d3ef61e470e595caab823a44980bc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/327000265" 
	@${RM} ${OBJECTDIR}/_ext/327000265/drv_usart_static_byte_model.o.d 
	@${RM} ${OBJECTDIR}/_ext/327000265/drv_usart_static_byte_model.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/327000265/drv_usart_static_byte_model.o.d" -o ${OBJECTDIR}/_ext/327000265/drv_usart_static_byte_model.o ../src/system_config/default/framework/driver/usart/src/drv_usart_static_byte_model.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/639803181/sys_clk_pic32mz.o: ../src/system_config/default/framework/system/clk/src/sys_clk_pic32mz.c  .generated_files/flags/default/44b7eb8b670d4cc6e9190adbe81cee2a40b27fa1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/639803181" 
	@${RM} ${OBJECTDIR}/_ext/639803181/sys_clk_pic32mz.o.d 
	@${RM} ${OBJECTDIR}/_ext/639803181/sys_clk_pic32mz.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/639803181/sys_clk_pic32mz.o.d" -o ${OBJECTDIR}/_ext/639803181/sys_clk_pic32mz.o ../src/system_config/default/framework/system/clk/src/sys_clk_pic32mz.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/340578644/sys_devcon.o: ../src/system_config/default/framework/system/devcon/src/sys_devcon.c  .generated_files/flags/default/ed489c4a184ce5767405b0fb2e46f9bbcdd7d542 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/340578644" 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon.o.d 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/340578644/sys_devcon.o.d" -o ${OBJECTDIR}/_ext/340578644/sys_devcon.o ../src/system_config/default/framework/system/devcon/src/sys_devcon.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mz.o: ../src/system_config/default/framework/system/devcon/src/sys_devcon_pic32mz.c  .generated_files/flags/default/78c501b61777ad7b93aef34380201971fd290821 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/340578644" 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mz.o.d 
	@${RM} ${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mz.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mz.o.d" -o ${OBJECTDIR}/_ext/340578644/sys_devcon_pic32mz.o ../src/system_config/default/framework/system/devcon/src/sys_devcon_pic32mz.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/822048611/sys_ports_static.o: ../src/system_config/default/framework/system/ports/src/sys_ports_static.c  .generated_files/flags/default/a48ed6c3dfa919a81768c35e38b7ee2363ffeddd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/822048611" 
	@${RM} ${OBJECTDIR}/_ext/822048611/sys_ports_static.o.d 
	@${RM} ${OBJECTDIR}/_ext/822048611/sys_ports_static.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/822048611/sys_ports_static.o.d" -o ${OBJECTDIR}/_ext/822048611/sys_ports_static.o ../src/system_config/default/framework/system/ports/src/sys_ports_static.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1688732426/system_init.o: ../src/system_config/default/system_init.c  .generated_files/flags/default/709f8f08c33518253ab129b47e1e4dc422619590 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1688732426" 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_init.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_init.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1688732426/system_init.o.d" -o ${OBJECTDIR}/_ext/1688732426/system_init.o ../src/system_config/default/system_init.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1688732426/system_interrupt.o: ../src/system_config/default/system_interrupt.c  .generated_files/flags/default/785090e11adf39ff7d1c2aa15c39165ba2f8d4a8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1688732426" 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_interrupt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_interrupt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1688732426/system_interrupt.o.d" -o ${OBJECTDIR}/_ext/1688732426/system_interrupt.o ../src/system_config/default/system_interrupt.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1688732426/system_exceptions.o: ../src/system_config/default/system_exceptions.c  .generated_files/flags/default/27d2abba15dab1584409f9cf2d8729a093690720 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1688732426" 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1688732426/system_exceptions.o.d" -o ${OBJECTDIR}/_ext/1688732426/system_exceptions.o ../src/system_config/default/system_exceptions.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1688732426/system_tasks.o: ../src/system_config/default/system_tasks.c  .generated_files/flags/default/a6ca57bfbea1a2369e4459cbd1e64d30a294ea0c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1688732426" 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1688732426/system_tasks.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1688732426/system_tasks.o.d" -o ${OBJECTDIR}/_ext/1688732426/system_tasks.o ../src/system_config/default/system_tasks.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  .generated_files/flags/default/9a15b32e180cb5c2fce7fa551fff9a42ce5d07be .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/flags/default/78a9bce29ed9ab067c6ca17ab961becd4a4c5fed .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/switches.o: ../src/switches.c  .generated_files/flags/default/a14749f9d50e58d000b7a179631500fb17631af5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/switches.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/switches.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/switches.o.d" -o ${OBJECTDIR}/_ext/1360937237/switches.o ../src/switches.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/timers.o: ../src/timers.c  .generated_files/flags/default/66c48683cc7e985374b86eeb57e6f7fe4dde19f2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/timers.o.d" -o ${OBJECTDIR}/_ext/1360937237/timers.o ../src/timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/crc.o: ../src/crc.c  .generated_files/flags/default/9fa14c884438e887b76455f231570308b25025ec .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/crc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/crc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/crc.o.d" -o ${OBJECTDIR}/_ext/1360937237/crc.o ../src/crc.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/commands.o: ../src/commands.c  .generated_files/flags/default/b82916c08fba2a944c4b25c71858d3b644c49490 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/commands.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/commands.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/commands.o.d" -o ${OBJECTDIR}/_ext/1360937237/commands.o ../src/commands.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/statusst.o: ../src/statusst.c  .generated_files/flags/default/7a37f2b45238b26170aec2f3f407a4e45f8725da .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/statusst.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/statusst.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/statusst.o.d" -o ${OBJECTDIR}/_ext/1360937237/statusst.o ../src/statusst.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/fifo.o: ../src/fifo.c  .generated_files/flags/default/d2c271db7e5d83d225042260c41d26a1c2fdffd3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/fifo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/fifo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/fifo.o.d" -o ${OBJECTDIR}/_ext/1360937237/fifo.o ../src/fifo.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/commmodule.o: ../src/commmodule.c  .generated_files/flags/default/2d738e0ea43a2c4ba27393db81f2fb3cad39dbb1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/commmodule.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/commmodule.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/commmodule.o.d" -o ${OBJECTDIR}/_ext/1360937237/commmodule.o ../src/commmodule.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/document.o: ../src/document.c  .generated_files/flags/default/e6f2a0fd05cd35ef74093cb6ab09d8a4e258fab0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/document.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/document.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/document.o.d" -o ${OBJECTDIR}/_ext/1360937237/document.o ../src/document.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/system_okay.o: ../src/system_okay.c  .generated_files/flags/default/68c23b0df73642bfb7bf34d74a289266a7957cf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/system_okay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/system_okay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/system_okay.o.d" -o ${OBJECTDIR}/_ext/1360937237/system_okay.o ../src/system_okay.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/test.o: ../src/test.c  .generated_files/flags/default/9778998b1b14a3f807b5e382830068ca70306c5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/test.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/test.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/test.o.d" -o ${OBJECTDIR}/_ext/1360937237/test.o ../src/test.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/gpt.o: ../src/gpt.c  .generated_files/flags/default/71f761312a3dde39e5845808f51f30355f5bd82a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/gpt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/gpt.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/gpt.o.d" -o ${OBJECTDIR}/_ext/1360937237/gpt.o ../src/gpt.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/high_side.o: ../src/high_side.c  .generated_files/flags/default/5160466cc36d83c21fe0cd7aa9eaf581b4ebac34 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/high_side.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/high_side.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/high_side.o.d" -o ${OBJECTDIR}/_ext/1360937237/high_side.o ../src/high_side.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/gamma.o: ../src/gamma.c  .generated_files/flags/default/189fadea4b6db4cc0b9a5efb0138c7d3102ececc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/gamma.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/gamma.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/gamma.o.d" -o ${OBJECTDIR}/_ext/1360937237/gamma.o ../src/gamma.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/nvm_disk_images.o: ../src/nvm_disk_images.c  .generated_files/flags/default/85693af343f4a412661514c7a67191ecb3b4f755 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/nvm_disk_images.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/nvm_disk_images.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/nvm_disk_images.o.d" -o ${OBJECTDIR}/_ext/1360937237/nvm_disk_images.o ../src/nvm_disk_images.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/nvm_fs.o: ../src/nvm_fs.c  .generated_files/flags/default/3451488fb72c4432445b7639ed2f04f6efa6a0fe .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/nvm_fs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/nvm_fs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/nvm_fs.o.d" -o ${OBJECTDIR}/_ext/1360937237/nvm_fs.o ../src/nvm_fs.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/hid.o: ../src/hid.c  .generated_files/flags/default/c0903d1c3f5840719d4139eaf34ba355b1d532e6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/hid.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/hid.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/hid.o.d" -o ${OBJECTDIR}/_ext/1360937237/hid.o ../src/hid.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1360937237/report.o: ../src/report.c  .generated_files/flags/default/a84cc208b34244ff924e0ed66c2370e029f27331 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/report.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/report.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/report.o.d" -o ${OBJECTDIR}/_ext/1360937237/report.o ../src/report.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2062801281/CLASSB_CPUPCTest.o: ../../../../harmony/v2_06/framework/classb/src/CLASSB_CPUPCTest.c  .generated_files/flags/default/eb662c994a41fa72a426c22a9779dcf9d69ef31a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2062801281" 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_CPUPCTest.o.d 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_CPUPCTest.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/2062801281/CLASSB_CPUPCTest.o.d" -o ${OBJECTDIR}/_ext/2062801281/CLASSB_CPUPCTest.o ../../../../harmony/v2_06/framework/classb/src/CLASSB_CPUPCTest.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2062801281/CLASSB_CRCbyte.o: ../../../../harmony/v2_06/framework/classb/src/CLASSB_CRCbyte.c  .generated_files/flags/default/140bc599fc6559e76e6d42ea69918abb020455fd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2062801281" 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_CRCbyte.o.d 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_CRCbyte.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/2062801281/CLASSB_CRCbyte.o.d" -o ${OBJECTDIR}/_ext/2062801281/CLASSB_CRCbyte.o ../../../../harmony/v2_06/framework/classb/src/CLASSB_CRCbyte.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2062801281/CLASSB_CRCFlashTest.o: ../../../../harmony/v2_06/framework/classb/src/CLASSB_CRCFlashTest.c  .generated_files/flags/default/160f137d0a9fc2a104f1fed71a5e2b915da7ebb8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2062801281" 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_CRCFlashTest.o.d 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_CRCFlashTest.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/2062801281/CLASSB_CRCFlashTest.o.d" -o ${OBJECTDIR}/_ext/2062801281/CLASSB_CRCFlashTest.o ../../../../harmony/v2_06/framework/classb/src/CLASSB_CRCFlashTest.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2062801281/CLASSB_RAMCheckerBoardTest.o: ../../../../harmony/v2_06/framework/classb/src/CLASSB_RAMCheckerBoardTest.c  .generated_files/flags/default/f8862ce040ee21493d7097dc80453b3e9204cd85 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2062801281" 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMCheckerBoardTest.o.d 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMCheckerBoardTest.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/2062801281/CLASSB_RAMCheckerBoardTest.o.d" -o ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMCheckerBoardTest.o ../../../../harmony/v2_06/framework/classb/src/CLASSB_RAMCheckerBoardTest.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchBTest.o: ../../../../harmony/v2_06/framework/classb/src/CLASSB_RAMMarchBTest.c  .generated_files/flags/default/1fa26fb5fbff8a66eab133185c267c20a358e5d7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2062801281" 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchBTest.o.d 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchBTest.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchBTest.o.d" -o ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchBTest.o ../../../../harmony/v2_06/framework/classb/src/CLASSB_RAMMarchBTest.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchCStackTest.o: ../../../../harmony/v2_06/framework/classb/src/CLASSB_RAMMarchCStackTest.c  .generated_files/flags/default/69ae17f9f039d37d6b081fcc02dda903bcf2ec7e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2062801281" 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchCStackTest.o.d 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchCStackTest.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchCStackTest.o.d" -o ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchCStackTest.o ../../../../harmony/v2_06/framework/classb/src/CLASSB_RAMMarchCStackTest.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchCTest.o: ../../../../harmony/v2_06/framework/classb/src/CLASSB_RAMMarchCTest.c  .generated_files/flags/default/28d9c5fbee9912ed577ca00ed7f34701291fb464 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2062801281" 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchCTest.o.d 
	@${RM} ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchCTest.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchCTest.o.d" -o ${OBJECTDIR}/_ext/2062801281/CLASSB_RAMMarchCTest.o ../../../../harmony/v2_06/framework/classb/src/CLASSB_RAMMarchCTest.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/274850301/drv_nvm.o: ../../../../harmony/v2_06/framework/driver/nvm/src/dynamic/drv_nvm.c  .generated_files/flags/default/d7f0715029a4625c908d14502feacbb3b1655481 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/274850301" 
	@${RM} ${OBJECTDIR}/_ext/274850301/drv_nvm.o.d 
	@${RM} ${OBJECTDIR}/_ext/274850301/drv_nvm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/274850301/drv_nvm.o.d" -o ${OBJECTDIR}/_ext/274850301/drv_nvm.o ../../../../harmony/v2_06/framework/driver/nvm/src/dynamic/drv_nvm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/274850301/drv_nvm_erasewrite.o: ../../../../harmony/v2_06/framework/driver/nvm/src/dynamic/drv_nvm_erasewrite.c  .generated_files/flags/default/fec3afba96e9e9cbe41a1e2e399aaa46022bdff7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/274850301" 
	@${RM} ${OBJECTDIR}/_ext/274850301/drv_nvm_erasewrite.o.d 
	@${RM} ${OBJECTDIR}/_ext/274850301/drv_nvm_erasewrite.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/274850301/drv_nvm_erasewrite.o.d" -o ${OBJECTDIR}/_ext/274850301/drv_nvm_erasewrite.o ../../../../harmony/v2_06/framework/driver/nvm/src/dynamic/drv_nvm_erasewrite.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1415029366/drv_spi.o: ../../../../harmony/v2_06/framework/driver/spi/src/dynamic/drv_spi.c  .generated_files/flags/default/257cb87a1eedfcb0a97d162bd61149ec2edb2582 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1415029366" 
	@${RM} ${OBJECTDIR}/_ext/1415029366/drv_spi.o.d 
	@${RM} ${OBJECTDIR}/_ext/1415029366/drv_spi.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1415029366/drv_spi.o.d" -o ${OBJECTDIR}/_ext/1415029366/drv_spi.o ../../../../harmony/v2_06/framework/driver/spi/src/dynamic/drv_spi.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1745438118/drv_spi_sys_queue_fifo.o: ../../../../harmony/v2_06/framework/driver/spi/src/drv_spi_sys_queue_fifo.c  .generated_files/flags/default/6cca5fbff181a58f95f49588f8354c838d5fb04d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1745438118" 
	@${RM} ${OBJECTDIR}/_ext/1745438118/drv_spi_sys_queue_fifo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1745438118/drv_spi_sys_queue_fifo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1745438118/drv_spi_sys_queue_fifo.o.d" -o ${OBJECTDIR}/_ext/1745438118/drv_spi_sys_queue_fifo.o ../../../../harmony/v2_06/framework/driver/spi/src/drv_spi_sys_queue_fifo.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1329795486/drv_usbhs.o: ../../../../harmony/v2_06/framework/driver/usb/usbhs/src/dynamic/drv_usbhs.c  .generated_files/flags/default/acfd033e4224639f654df2f6195dda5a9838fea1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1329795486" 
	@${RM} ${OBJECTDIR}/_ext/1329795486/drv_usbhs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1329795486/drv_usbhs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1329795486/drv_usbhs.o.d" -o ${OBJECTDIR}/_ext/1329795486/drv_usbhs.o ../../../../harmony/v2_06/framework/driver/usb/usbhs/src/dynamic/drv_usbhs.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1329795486/drv_usbhs_device.o: ../../../../harmony/v2_06/framework/driver/usb/usbhs/src/dynamic/drv_usbhs_device.c  .generated_files/flags/default/83ec0da7ba2184d2d963ae5150af1377dc1e1116 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1329795486" 
	@${RM} ${OBJECTDIR}/_ext/1329795486/drv_usbhs_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/1329795486/drv_usbhs_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1329795486/drv_usbhs_device.o.d" -o ${OBJECTDIR}/_ext/1329795486/drv_usbhs_device.o ../../../../harmony/v2_06/framework/driver/usb/usbhs/src/dynamic/drv_usbhs_device.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/746721678/sys_fs.o: ../../../../harmony/v2_06/framework/system/fs/src/dynamic/sys_fs.c  .generated_files/flags/default/74159336ec30c81270e92e054684af7f9da28595 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/746721678" 
	@${RM} ${OBJECTDIR}/_ext/746721678/sys_fs.o.d 
	@${RM} ${OBJECTDIR}/_ext/746721678/sys_fs.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/746721678/sys_fs.o.d" -o ${OBJECTDIR}/_ext/746721678/sys_fs.o ../../../../harmony/v2_06/framework/system/fs/src/dynamic/sys_fs.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/746721678/sys_fs_media_manager.o: ../../../../harmony/v2_06/framework/system/fs/src/dynamic/sys_fs_media_manager.c  .generated_files/flags/default/85b4aa6b3380285e20605c6a0ede1b8374b45397 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/746721678" 
	@${RM} ${OBJECTDIR}/_ext/746721678/sys_fs_media_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/746721678/sys_fs_media_manager.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/746721678/sys_fs_media_manager.o.d" -o ${OBJECTDIR}/_ext/746721678/sys_fs_media_manager.o ../../../../harmony/v2_06/framework/system/fs/src/dynamic/sys_fs_media_manager.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/408548909/ff.o: ../../../../harmony/v2_06/framework/system/fs/fat_fs/src/file_system/ff.c  .generated_files/flags/default/795931973c7663ada46fba52b4ad094f6eccf060 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/408548909" 
	@${RM} ${OBJECTDIR}/_ext/408548909/ff.o.d 
	@${RM} ${OBJECTDIR}/_ext/408548909/ff.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/408548909/ff.o.d" -o ${OBJECTDIR}/_ext/408548909/ff.o ../../../../harmony/v2_06/framework/system/fs/fat_fs/src/file_system/ff.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1290481162/diskio.o: ../../../../harmony/v2_06/framework/system/fs/fat_fs/src/hardware_access/diskio.c  .generated_files/flags/default/5052427f54a1da1bebcc1d67d81afa713016ad15 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1290481162" 
	@${RM} ${OBJECTDIR}/_ext/1290481162/diskio.o.d 
	@${RM} ${OBJECTDIR}/_ext/1290481162/diskio.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/1290481162/diskio.o.d" -o ${OBJECTDIR}/_ext/1290481162/diskio.o ../../../../harmony/v2_06/framework/system/fs/fat_fs/src/hardware_access/diskio.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2087805404/sys_int_pic32.o: ../../../../harmony/v2_06/framework/system/int/src/sys_int_pic32.c  .generated_files/flags/default/69766d722b1a78309ef2365fee89e9fd227cae75 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/2087805404" 
	@${RM} ${OBJECTDIR}/_ext/2087805404/sys_int_pic32.o.d 
	@${RM} ${OBJECTDIR}/_ext/2087805404/sys_int_pic32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/2087805404/sys_int_pic32.o.d" -o ${OBJECTDIR}/_ext/2087805404/sys_int_pic32.o ../../../../harmony/v2_06/framework/system/int/src/sys_int_pic32.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/945675698/sys_tmr.o: ../../../../harmony/v2_06/framework/system/tmr/src/sys_tmr.c  .generated_files/flags/default/a10660cf76d10dd47c52252b298f60cc4ae24184 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/945675698" 
	@${RM} ${OBJECTDIR}/_ext/945675698/sys_tmr.o.d 
	@${RM} ${OBJECTDIR}/_ext/945675698/sys_tmr.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/945675698/sys_tmr.o.d" -o ${OBJECTDIR}/_ext/945675698/sys_tmr.o ../../../../harmony/v2_06/framework/system/tmr/src/sys_tmr.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/419360567/usb_device.o: ../../../../harmony/v2_06/framework/usb/src/dynamic/usb_device.c  .generated_files/flags/default/8f85c464cff2884759648350ec4847bf204a0c15 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/419360567" 
	@${RM} ${OBJECTDIR}/_ext/419360567/usb_device.o.d 
	@${RM} ${OBJECTDIR}/_ext/419360567/usb_device.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/419360567/usb_device.o.d" -o ${OBJECTDIR}/_ext/419360567/usb_device.o ../../../../harmony/v2_06/framework/usb/src/dynamic/usb_device.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/419360567/usb_device_hid.o: ../../../../harmony/v2_06/framework/usb/src/dynamic/usb_device_hid.c  .generated_files/flags/default/61bc6abc9a3b2be001a6d71046011ab7b9da3651 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/419360567" 
	@${RM} ${OBJECTDIR}/_ext/419360567/usb_device_hid.o.d 
	@${RM} ${OBJECTDIR}/_ext/419360567/usb_device_hid.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../../../../framework" -I"../src" -I"../src/system_config/default" -I"../src/default" -I"../../../../harmony/v2_06/framework" -I"../src/system_config/default/framework" -MP -MMD -MF "${OBJECTDIR}/_ext/419360567/usb_device_hid.o.d" -o ${OBJECTDIR}/_ext/419360567/usb_device_hid.o ../../../../harmony/v2_06/framework/usb/src/dynamic/usb_device_hid.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -fvar-tracking -fno-short-double  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/Logging_Interface_Board_Boot.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../harmony/v2_06/bin/framework/peripheral/PIC32MZ2048EFH144_peripherals.a  
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_ICD5=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/Logging_Interface_Board_Boot.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\..\harmony\v2_06\bin\framework\peripheral\PIC32MZ2048EFH144_peripherals.a      -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x37F   -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_ICD5=1,--defsym=_min_heap_size=512,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/Logging_Interface_Board_Boot.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  ../../../../harmony/v2_06/bin/framework/peripheral/PIC32MZ2048EFH144_peripherals.a 
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/Logging_Interface_Board_Boot.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    ..\..\..\..\harmony\v2_06\bin\framework\peripheral\PIC32MZ2048EFH144_peripherals.a      -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=512,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/Logging_Interface_Board_Boot.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
