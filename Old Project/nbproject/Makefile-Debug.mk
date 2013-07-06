#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=Cygwin-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/2048919765/discovery.o \
	${OBJECTDIR}/_ext/2048919765/main.o \
	${OBJECTDIR}/bridge.o \
	${OBJECTDIR}/colors.o \
	${OBJECTDIR}/process.o


# C Compiler Flags
CFLAGS=-mwindows

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ambify.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ambify.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ambify ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/2048919765/discovery.o: ../Ambify/discovery.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/2048919765
	${RM} $@.d
	$(COMPILE.c) -g -mwindows -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2048919765/discovery.o ../Ambify/discovery.c

${OBJECTDIR}/_ext/2048919765/main.o: ../Ambify/main.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/2048919765
	${RM} $@.d
	$(COMPILE.c) -g -mwindows -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2048919765/main.o ../Ambify/main.c

${OBJECTDIR}/bridge.o: bridge.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -mwindows -MMD -MP -MF $@.d -o ${OBJECTDIR}/bridge.o bridge.c

${OBJECTDIR}/colors.o: colors.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -mwindows -MMD -MP -MF $@.d -o ${OBJECTDIR}/colors.o colors.c

${OBJECTDIR}/process.o: process.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -mwindows -MMD -MP -MF $@.d -o ${OBJECTDIR}/process.o process.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ambify.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
