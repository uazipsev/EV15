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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Router_PIC_w_USB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Router_PIC_w_USB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED="USB stuff.c" usb_descriptors.c variables.cpp queue.cpp interrupt_handler.cpp initialize.cpp FastTransfer.cpp buffer.cpp main.cpp debug_handler.cpp

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED="${OBJECTDIR}/USB stuff.o" ${OBJECTDIR}/usb_descriptors.o ${OBJECTDIR}/variables.o ${OBJECTDIR}/queue.o ${OBJECTDIR}/interrupt_handler.o ${OBJECTDIR}/initialize.o ${OBJECTDIR}/FastTransfer.o ${OBJECTDIR}/buffer.o ${OBJECTDIR}/main.o ${OBJECTDIR}/debug_handler.o
POSSIBLE_DEPFILES="${OBJECTDIR}/USB stuff.o.d" ${OBJECTDIR}/usb_descriptors.o.d ${OBJECTDIR}/variables.o.d ${OBJECTDIR}/queue.o.d ${OBJECTDIR}/interrupt_handler.o.d ${OBJECTDIR}/initialize.o.d ${OBJECTDIR}/FastTransfer.o.d ${OBJECTDIR}/buffer.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/debug_handler.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/USB\ stuff.o ${OBJECTDIR}/usb_descriptors.o ${OBJECTDIR}/variables.o ${OBJECTDIR}/queue.o ${OBJECTDIR}/interrupt_handler.o ${OBJECTDIR}/initialize.o ${OBJECTDIR}/FastTransfer.o ${OBJECTDIR}/buffer.o ${OBJECTDIR}/main.o ${OBJECTDIR}/debug_handler.o

# Source Files
SOURCEFILES=USB stuff.c usb_descriptors.c variables.cpp queue.cpp interrupt_handler.cpp initialize.cpp FastTransfer.cpp buffer.cpp main.cpp debug_handler.cpp


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Router_PIC_w_USB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX575F512H
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/USB\ stuff.o: USB\ stuff.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/USB\ stuff.o.d 
	@${RM} "${OBJECTDIR}/USB stuff.o" 
	@${FIXDEPS} "${OBJECTDIR}/USB stuff.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../USB" -I"." -MMD -MF "${OBJECTDIR}/USB stuff.o.d" -o "${OBJECTDIR}/USB stuff.o" "USB stuff.c"   
	
${OBJECTDIR}/usb_descriptors.o: usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/usb_descriptors.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_descriptors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../USB" -I"." -MMD -MF "${OBJECTDIR}/usb_descriptors.o.d" -o ${OBJECTDIR}/usb_descriptors.o usb_descriptors.c   
	
else
${OBJECTDIR}/USB\ stuff.o: USB\ stuff.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/USB\ stuff.o.d 
	@${RM} "${OBJECTDIR}/USB stuff.o" 
	@${FIXDEPS} "${OBJECTDIR}/USB stuff.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../USB" -I"." -MMD -MF "${OBJECTDIR}/USB stuff.o.d" -o "${OBJECTDIR}/USB stuff.o" "USB stuff.c"   
	
${OBJECTDIR}/usb_descriptors.o: usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/usb_descriptors.o.d 
	@${RM} ${OBJECTDIR}/usb_descriptors.o 
	@${FIXDEPS} "${OBJECTDIR}/usb_descriptors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I".." -I"../USB" -I"." -MMD -MF "${OBJECTDIR}/usb_descriptors.o.d" -o ${OBJECTDIR}/usb_descriptors.o usb_descriptors.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/variables.o: variables.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/variables.o.d 
	@${RM} ${OBJECTDIR}/variables.o 
	@${FIXDEPS} "${OBJECTDIR}/variables.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/variables.o.d" -o ${OBJECTDIR}/variables.o variables.cpp  
	
${OBJECTDIR}/queue.o: queue.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/queue.o.d 
	@${RM} ${OBJECTDIR}/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/queue.o.d" -o ${OBJECTDIR}/queue.o queue.cpp  
	
${OBJECTDIR}/interrupt_handler.o: interrupt_handler.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/interrupt_handler.o.d 
	@${RM} ${OBJECTDIR}/interrupt_handler.o 
	@${FIXDEPS} "${OBJECTDIR}/interrupt_handler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/interrupt_handler.o.d" -o ${OBJECTDIR}/interrupt_handler.o interrupt_handler.cpp  
	
${OBJECTDIR}/initialize.o: initialize.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/initialize.o.d 
	@${RM} ${OBJECTDIR}/initialize.o 
	@${FIXDEPS} "${OBJECTDIR}/initialize.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/initialize.o.d" -o ${OBJECTDIR}/initialize.o initialize.cpp  
	
${OBJECTDIR}/FastTransfer.o: FastTransfer.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/FastTransfer.o.d 
	@${RM} ${OBJECTDIR}/FastTransfer.o 
	@${FIXDEPS} "${OBJECTDIR}/FastTransfer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/FastTransfer.o.d" -o ${OBJECTDIR}/FastTransfer.o FastTransfer.cpp  
	
${OBJECTDIR}/buffer.o: buffer.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/buffer.o.d 
	@${RM} ${OBJECTDIR}/buffer.o 
	@${FIXDEPS} "${OBJECTDIR}/buffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/buffer.o.d" -o ${OBJECTDIR}/buffer.o buffer.cpp  
	
${OBJECTDIR}/main.o: main.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.cpp  
	
${OBJECTDIR}/debug_handler.o: debug_handler.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/debug_handler.o.d 
	@${RM} ${OBJECTDIR}/debug_handler.o 
	@${FIXDEPS} "${OBJECTDIR}/debug_handler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG  -fframe-base-loclist  -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/debug_handler.o.d" -o ${OBJECTDIR}/debug_handler.o debug_handler.cpp  
	
else
${OBJECTDIR}/variables.o: variables.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/variables.o.d 
	@${RM} ${OBJECTDIR}/variables.o 
	@${FIXDEPS} "${OBJECTDIR}/variables.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/variables.o.d" -o ${OBJECTDIR}/variables.o variables.cpp  
	
${OBJECTDIR}/queue.o: queue.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/queue.o.d 
	@${RM} ${OBJECTDIR}/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/queue.o.d" -o ${OBJECTDIR}/queue.o queue.cpp  
	
${OBJECTDIR}/interrupt_handler.o: interrupt_handler.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/interrupt_handler.o.d 
	@${RM} ${OBJECTDIR}/interrupt_handler.o 
	@${FIXDEPS} "${OBJECTDIR}/interrupt_handler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/interrupt_handler.o.d" -o ${OBJECTDIR}/interrupt_handler.o interrupt_handler.cpp  
	
${OBJECTDIR}/initialize.o: initialize.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/initialize.o.d 
	@${RM} ${OBJECTDIR}/initialize.o 
	@${FIXDEPS} "${OBJECTDIR}/initialize.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/initialize.o.d" -o ${OBJECTDIR}/initialize.o initialize.cpp  
	
${OBJECTDIR}/FastTransfer.o: FastTransfer.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/FastTransfer.o.d 
	@${RM} ${OBJECTDIR}/FastTransfer.o 
	@${FIXDEPS} "${OBJECTDIR}/FastTransfer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/FastTransfer.o.d" -o ${OBJECTDIR}/FastTransfer.o FastTransfer.cpp  
	
${OBJECTDIR}/buffer.o: buffer.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/buffer.o.d 
	@${RM} ${OBJECTDIR}/buffer.o 
	@${FIXDEPS} "${OBJECTDIR}/buffer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/buffer.o.d" -o ${OBJECTDIR}/buffer.o buffer.cpp  
	
${OBJECTDIR}/main.o: main.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.cpp  
	
${OBJECTDIR}/debug_handler.o: debug_handler.cpp  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/debug_handler.o.d 
	@${RM} ${OBJECTDIR}/debug_handler.o 
	@${FIXDEPS} "${OBJECTDIR}/debug_handler.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CPPC} $(MP_EXTRA_CC_PRE)  -g -x c++ -c -mprocessor=$(MP_PROCESSOR_OPTION)  -frtti -fexceptions -fno-check-new -fenforce-eh-specs -MMD -MF "${OBJECTDIR}/debug_handler.o.d" -o ${OBJECTDIR}/debug_handler.o debug_handler.cpp  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Router_PIC_w_USB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  PIC32_ESK_USB_Device_CDC_DEMO_wo_MAL.a  
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)    -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Router_PIC_w_USB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    PIC32_ESK_USB_Device_CDC_DEMO_wo_MAL.a          -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=_min_heap_size=500,-L"../../../MPLAB C32 Suite/lib",-L"../../../MPLAB C32 Suite/pic32mx/lib",-L".",-Map="${DISTDIR}/USB_Device_-_CDC_-_Basic_Demo_-__PIC32_ESK_wo_MAL.X.${IMAGE_TYPE}.map"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Router_PIC_w_USB.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk  PIC32_ESK_USB_Device_CDC_DEMO_wo_MAL.a 
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CPPC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Router_PIC_w_USB.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}    PIC32_ESK_USB_Device_CDC_DEMO_wo_MAL.a      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=500,-L"../../../MPLAB C32 Suite/lib",-L"../../../MPLAB C32 Suite/pic32mx/lib",-L".",-Map="${DISTDIR}/USB_Device_-_CDC_-_Basic_Demo_-__PIC32_ESK_wo_MAL.X.${IMAGE_TYPE}.map"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Router_PIC_w_USB.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
