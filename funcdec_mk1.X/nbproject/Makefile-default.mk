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
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/funcdec_mk1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/funcdec_mk1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=funcdec_main.c funcdec_recv.c funcdec_decode.c funcdec_app.c funcdec_cvlist.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/funcdec_main.o ${OBJECTDIR}/funcdec_recv.o ${OBJECTDIR}/funcdec_decode.o ${OBJECTDIR}/funcdec_app.o ${OBJECTDIR}/funcdec_cvlist.o
POSSIBLE_DEPFILES=${OBJECTDIR}/funcdec_main.o.d ${OBJECTDIR}/funcdec_recv.o.d ${OBJECTDIR}/funcdec_decode.o.d ${OBJECTDIR}/funcdec_app.o.d ${OBJECTDIR}/funcdec_cvlist.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/funcdec_main.o ${OBJECTDIR}/funcdec_recv.o ${OBJECTDIR}/funcdec_decode.o ${OBJECTDIR}/funcdec_app.o ${OBJECTDIR}/funcdec_cvlist.o

# Source Files
SOURCEFILES=funcdec_main.c funcdec_recv.c funcdec_decode.c funcdec_app.c funcdec_cvlist.c

# Pack Options 
PACK_COMPILER_OPTIONS=-I ${DFP_DIR}/include
PACK_COMMON_OPTIONS=-B ${DFP_DIR}/avr-gcc/dev/atmega3208



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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/funcdec_mk1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=ATmega3208
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
${OBJECTDIR}/funcdec_main.o: funcdec_main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/funcdec_main.o.d 
	@${RM} ${OBJECTDIR}/funcdec_main.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega3208 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/funcdec_main.o.d" -MT "${OBJECTDIR}/funcdec_main.o.d" -MT ${OBJECTDIR}/funcdec_main.o  -o ${OBJECTDIR}/funcdec_main.o funcdec_main.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/funcdec_recv.o: funcdec_recv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/funcdec_recv.o.d 
	@${RM} ${OBJECTDIR}/funcdec_recv.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega3208 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/funcdec_recv.o.d" -MT "${OBJECTDIR}/funcdec_recv.o.d" -MT ${OBJECTDIR}/funcdec_recv.o  -o ${OBJECTDIR}/funcdec_recv.o funcdec_recv.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/funcdec_decode.o: funcdec_decode.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/funcdec_decode.o.d 
	@${RM} ${OBJECTDIR}/funcdec_decode.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega3208 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/funcdec_decode.o.d" -MT "${OBJECTDIR}/funcdec_decode.o.d" -MT ${OBJECTDIR}/funcdec_decode.o  -o ${OBJECTDIR}/funcdec_decode.o funcdec_decode.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/funcdec_app.o: funcdec_app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/funcdec_app.o.d 
	@${RM} ${OBJECTDIR}/funcdec_app.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega3208 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/funcdec_app.o.d" -MT "${OBJECTDIR}/funcdec_app.o.d" -MT ${OBJECTDIR}/funcdec_app.o  -o ${OBJECTDIR}/funcdec_app.o funcdec_app.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/funcdec_cvlist.o: funcdec_cvlist.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/funcdec_cvlist.o.d 
	@${RM} ${OBJECTDIR}/funcdec_cvlist.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega3208 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/funcdec_cvlist.o.d" -MT "${OBJECTDIR}/funcdec_cvlist.o.d" -MT ${OBJECTDIR}/funcdec_cvlist.o  -o ${OBJECTDIR}/funcdec_cvlist.o funcdec_cvlist.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/funcdec_main.o: funcdec_main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/funcdec_main.o.d 
	@${RM} ${OBJECTDIR}/funcdec_main.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega3208 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/funcdec_main.o.d" -MT "${OBJECTDIR}/funcdec_main.o.d" -MT ${OBJECTDIR}/funcdec_main.o  -o ${OBJECTDIR}/funcdec_main.o funcdec_main.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/funcdec_recv.o: funcdec_recv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/funcdec_recv.o.d 
	@${RM} ${OBJECTDIR}/funcdec_recv.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega3208 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/funcdec_recv.o.d" -MT "${OBJECTDIR}/funcdec_recv.o.d" -MT ${OBJECTDIR}/funcdec_recv.o  -o ${OBJECTDIR}/funcdec_recv.o funcdec_recv.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/funcdec_decode.o: funcdec_decode.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/funcdec_decode.o.d 
	@${RM} ${OBJECTDIR}/funcdec_decode.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega3208 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/funcdec_decode.o.d" -MT "${OBJECTDIR}/funcdec_decode.o.d" -MT ${OBJECTDIR}/funcdec_decode.o  -o ${OBJECTDIR}/funcdec_decode.o funcdec_decode.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/funcdec_app.o: funcdec_app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/funcdec_app.o.d 
	@${RM} ${OBJECTDIR}/funcdec_app.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega3208 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/funcdec_app.o.d" -MT "${OBJECTDIR}/funcdec_app.o.d" -MT ${OBJECTDIR}/funcdec_app.o  -o ${OBJECTDIR}/funcdec_app.o funcdec_app.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/funcdec_cvlist.o: funcdec_cvlist.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/funcdec_cvlist.o.d 
	@${RM} ${OBJECTDIR}/funcdec_cvlist.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=atmega3208 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/funcdec_cvlist.o.d" -MT "${OBJECTDIR}/funcdec_cvlist.o.d" -MT ${OBJECTDIR}/funcdec_cvlist.o  -o ${OBJECTDIR}/funcdec_cvlist.o funcdec_cvlist.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/funcdec_mk1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mmcu=atmega3208 ${PACK_COMMON_OPTIONS}   -gdwarf-2 -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="dist/${CND_CONF}/${IMAGE_TYPE}/funcdec_mk1.X.${IMAGE_TYPE}.map"    -o dist/${CND_CONF}/${IMAGE_TYPE}/funcdec_mk1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1 -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	
	
	
	
	
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/funcdec_mk1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mmcu=atmega3208 ${PACK_COMMON_OPTIONS}  -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="dist/${CND_CONF}/${IMAGE_TYPE}/funcdec_mk1.X.${IMAGE_TYPE}.map"    -o dist/${CND_CONF}/${IMAGE_TYPE}/funcdec_mk1.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION) -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	${MP_CC_DIR}/avr-objcopy -O ihex "dist/${CND_CONF}/${IMAGE_TYPE}/funcdec_mk1.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "dist/${CND_CONF}/${IMAGE_TYPE}/funcdec_mk1.X.${IMAGE_TYPE}.hex"
	
	
	
	
	
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

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
