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
	${OBJECTDIR}/_ext/4ccc2a23/ErrorHandler.o \
	${OBJECTDIR}/_ext/4ccc2a23/PeriodicHandler.o \
	${OBJECTDIR}/_ext/5fc2206d/Player.o \
	${OBJECTDIR}/_ext/4ccc2a23/PlayerHandler.o \
	${OBJECTDIR}/_ext/4ccc2a23/UserHandler.o \
	${OBJECTDIR}/_ext/4ccc2a23/WebHandler.o \
	${OBJECTDIR}/_ext/1271fde8/main.o \
	${OBJECTDIR}/_ext/cf7d2710/PlayersPanel.o \
	${OBJECTDIR}/_ext/cf7d2710/StatusPanel.o \
	${OBJECTDIR}/_ext/cf7d2710/SwapPanel.o \
	${OBJECTDIR}/_ext/2c8a6064/GenericWindow.o \
	${OBJECTDIR}/_ext/2c8a6064/MainWindow.o \
	${OBJECTDIR}/_ext/2c8a6064/UserWindow.o \
	${OBJECTDIR}/_ext/2c8a6064/WindowManager.o


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
LDLIBSOPTIONS=-lgdi32 -lcurl.dll -lshlwapi -lGdiPlus resources/resources.o -lcomctl32 -lmsimg32

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/arcteam.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/arcteam.exe: resources/resources.o

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/arcteam.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/arcteam ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/4ccc2a23/ErrorHandler.o: /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/handler/ErrorHandler.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/4ccc2a23
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4ccc2a23/ErrorHandler.o /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/handler/ErrorHandler.cpp

${OBJECTDIR}/_ext/4ccc2a23/PeriodicHandler.o: /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/handler/PeriodicHandler.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/4ccc2a23
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4ccc2a23/PeriodicHandler.o /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/handler/PeriodicHandler.cpp

${OBJECTDIR}/_ext/5fc2206d/Player.o: /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/handler/Player/Player.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/5fc2206d
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/5fc2206d/Player.o /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/handler/Player/Player.cpp

${OBJECTDIR}/_ext/4ccc2a23/PlayerHandler.o: /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/handler/PlayerHandler.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/4ccc2a23
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4ccc2a23/PlayerHandler.o /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/handler/PlayerHandler.cpp

${OBJECTDIR}/_ext/4ccc2a23/UserHandler.o: /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/handler/UserHandler.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/4ccc2a23
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4ccc2a23/UserHandler.o /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/handler/UserHandler.cpp

${OBJECTDIR}/_ext/4ccc2a23/WebHandler.o: /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/handler/WebHandler.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/4ccc2a23
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4ccc2a23/WebHandler.o /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/handler/WebHandler.cpp

${OBJECTDIR}/_ext/1271fde8/main.o: /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/main.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/1271fde8
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1271fde8/main.o /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/main.cpp

resources/resources.o: /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/resources/resources.rc resources/resources.h
	${MKDIR} -p resources
	@echo Compiling resources...
	windres.exe resources/resources.rc resources/resources.o

${OBJECTDIR}/_ext/cf7d2710/PlayersPanel.o: /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/panel/PlayersPanel.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/cf7d2710
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/cf7d2710/PlayersPanel.o /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/panel/PlayersPanel.cpp

${OBJECTDIR}/_ext/cf7d2710/StatusPanel.o: /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/panel/StatusPanel.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/cf7d2710
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/cf7d2710/StatusPanel.o /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/panel/StatusPanel.cpp

${OBJECTDIR}/_ext/cf7d2710/SwapPanel.o: /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/panel/SwapPanel.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/cf7d2710
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/cf7d2710/SwapPanel.o /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/panel/SwapPanel.cpp

${OBJECTDIR}/_ext/2c8a6064/GenericWindow.o: /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/window/GenericWindow.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/2c8a6064
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2c8a6064/GenericWindow.o /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/window/GenericWindow.cpp

${OBJECTDIR}/_ext/2c8a6064/MainWindow.o: /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/window/MainWindow.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/2c8a6064
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2c8a6064/MainWindow.o /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/window/MainWindow.cpp

${OBJECTDIR}/_ext/2c8a6064/UserWindow.o: /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/window/UserWindow.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/2c8a6064
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2c8a6064/UserWindow.o /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/window/UserWindow.cpp

${OBJECTDIR}/_ext/2c8a6064/WindowManager.o: /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/window/WindowManager.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/2c8a6064
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2c8a6064/WindowManager.o /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/window/WindowManager.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} resources/resources.o

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
