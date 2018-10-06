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
	${OBJECTDIR}/_ext/ceaacb99/DownloadHandler.o \
	${OBJECTDIR}/_ext/ceaacb99/ErrorHandler.o \
	${OBJECTDIR}/_ext/ceaacb99/FileHandler.o \
	${OBJECTDIR}/_ext/ceaacb99/WebHandler.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/ui/GenericWindow.o \
	${OBJECTDIR}/ui/UpdaterWindow.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lcurl.dll -lshlwapi resources/resources.o

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/arcupdater.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/arcupdater.exe: resources/resources.o

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/arcupdater.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/arcupdater ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/ceaacb99/DownloadHandler.o: /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcUpdater/handler/DownloadHandler.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/ceaacb99
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/ceaacb99/DownloadHandler.o /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcUpdater/handler/DownloadHandler.cpp

${OBJECTDIR}/_ext/ceaacb99/ErrorHandler.o: /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcUpdater/handler/ErrorHandler.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/ceaacb99
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/ceaacb99/ErrorHandler.o /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcUpdater/handler/ErrorHandler.cpp

${OBJECTDIR}/_ext/ceaacb99/FileHandler.o: /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcUpdater/handler/FileHandler.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/ceaacb99
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/ceaacb99/FileHandler.o /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcUpdater/handler/FileHandler.cpp

${OBJECTDIR}/_ext/ceaacb99/WebHandler.o: /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcUpdater/handler/WebHandler.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/ceaacb99
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/ceaacb99/WebHandler.o /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcUpdater/handler/WebHandler.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/ui/GenericWindow.o: ui/GenericWindow.cpp
	${MKDIR} -p ${OBJECTDIR}/ui
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ui/GenericWindow.o ui/GenericWindow.cpp

${OBJECTDIR}/ui/UpdaterWindow.o: ui/UpdaterWindow.cpp
	${MKDIR} -p ${OBJECTDIR}/ui
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ui/UpdaterWindow.o ui/UpdaterWindow.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
