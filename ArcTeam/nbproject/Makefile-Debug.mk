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
	${OBJECTDIR}/handler/PeriodicHandler.o \
	${OBJECTDIR}/handler/Player/Player.o \
	${OBJECTDIR}/handler/PlayerHandler.o \
	${OBJECTDIR}/handler/UserHandler.o \
	${OBJECTDIR}/handler/WebHandler.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/ui/panel/PlayersPanel.o \
	${OBJECTDIR}/ui/panel/StatusPanel.o \
	${OBJECTDIR}/ui/panel/SwapPanel.o \
	${OBJECTDIR}/ui/window/GenericWindow.o \
	${OBJECTDIR}/ui/window/MainWindow.o \
	${OBJECTDIR}/ui/window/UserWindow.o \
	${OBJECTDIR}/ui/window/WindowManager.o


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

${OBJECTDIR}/handler/PeriodicHandler.o: handler/PeriodicHandler.cpp
	${MKDIR} -p ${OBJECTDIR}/handler
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/handler/PeriodicHandler.o handler/PeriodicHandler.cpp

${OBJECTDIR}/handler/Player/Player.o: handler/Player/Player.cpp
	${MKDIR} -p ${OBJECTDIR}/handler/Player
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/handler/Player/Player.o handler/Player/Player.cpp

${OBJECTDIR}/handler/PlayerHandler.o: handler/PlayerHandler.cpp
	${MKDIR} -p ${OBJECTDIR}/handler
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/handler/PlayerHandler.o handler/PlayerHandler.cpp

${OBJECTDIR}/handler/UserHandler.o: handler/UserHandler.cpp
	${MKDIR} -p ${OBJECTDIR}/handler
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/handler/UserHandler.o handler/UserHandler.cpp

${OBJECTDIR}/handler/WebHandler.o: handler/WebHandler.cpp
	${MKDIR} -p ${OBJECTDIR}/handler
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/handler/WebHandler.o handler/WebHandler.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

resources/resources.o: resources/resources.rc resources/resources.h
	${MKDIR} -p resources
	@echo Compiling resources...
	windres.exe resources/resources.rc resources/resources.o

${OBJECTDIR}/ui/panel/PlayersPanel.o: ui/panel/PlayersPanel.cpp
	${MKDIR} -p ${OBJECTDIR}/ui/panel
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ui/panel/PlayersPanel.o ui/panel/PlayersPanel.cpp

${OBJECTDIR}/ui/panel/StatusPanel.o: ui/panel/StatusPanel.cpp
	${MKDIR} -p ${OBJECTDIR}/ui/panel
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ui/panel/StatusPanel.o ui/panel/StatusPanel.cpp

${OBJECTDIR}/ui/panel/SwapPanel.o: ui/panel/SwapPanel.cpp
	${MKDIR} -p ${OBJECTDIR}/ui/panel
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ui/panel/SwapPanel.o ui/panel/SwapPanel.cpp

${OBJECTDIR}/ui/window/GenericWindow.o: ui/window/GenericWindow.cpp
	${MKDIR} -p ${OBJECTDIR}/ui/window
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ui/window/GenericWindow.o ui/window/GenericWindow.cpp

${OBJECTDIR}/ui/window/MainWindow.o: ui/window/MainWindow.cpp
	${MKDIR} -p ${OBJECTDIR}/ui/window
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ui/window/MainWindow.o ui/window/MainWindow.cpp

${OBJECTDIR}/ui/window/UserWindow.o: ui/window/UserWindow.cpp
	${MKDIR} -p ${OBJECTDIR}/ui/window
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ui/window/UserWindow.o ui/window/UserWindow.cpp

${OBJECTDIR}/ui/window/WindowManager.o: ui/window/WindowManager.cpp
	${MKDIR} -p ${OBJECTDIR}/ui/window
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ui/window/WindowManager.o ui/window/WindowManager.cpp

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
