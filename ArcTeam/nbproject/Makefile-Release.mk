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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/4ccc2a23/ErrorHandler.o \
	${OBJECTDIR}/_ext/cf7d2710/PlayersPanel.o \
	${OBJECTDIR}/_ext/cf7d2710/StatusPanel.o \
	${OBJECTDIR}/_ext/cf7d2710/SwapPanel.o \
	${OBJECTDIR}/_ext/2c8a6064/GenericWindow.o \
	${OBJECTDIR}/_ext/2c8a6064/MainWindow.o \
	${OBJECTDIR}/_ext/2c8a6064/UserWindow.o \
	${OBJECTDIR}/_ext/2c8a6064/WindowManager.o \
	${OBJECTDIR}/handler/PeriodicHandler.o \
	${OBJECTDIR}/handler/Player/Player.o \
	${OBJECTDIR}/handler/PlayerHandler.o \
	${OBJECTDIR}/handler/UserHandler.o \
	${OBJECTDIR}/handler/WebHandler.o \
	${OBJECTDIR}/main.o


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
LDLIBSOPTIONS=-L/cygdrive/C/cygwin64/bin -lgdi32 -lcurl.dll -lshlwapi -lGdiPlus resources/resources.o -lcomctl32 -lmsimg32

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/arcteam.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/arcteam.exe: resources/resources.o

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/arcteam.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/arcteam ${OBJECTFILES} ${LDLIBSOPTIONS} -Wl,-subsystem,windows

${OBJECTDIR}/_ext/4ccc2a23/ErrorHandler.o: /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/handler/ErrorHandler.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/4ccc2a23
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/4ccc2a23/ErrorHandler.o /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/handler/ErrorHandler.cpp

${OBJECTDIR}/_ext/cf7d2710/PlayersPanel.o: /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/panel/PlayersPanel.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/cf7d2710
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/cf7d2710/PlayersPanel.o /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/panel/PlayersPanel.cpp

${OBJECTDIR}/_ext/cf7d2710/StatusPanel.o: /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/panel/StatusPanel.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/cf7d2710
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/cf7d2710/StatusPanel.o /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/panel/StatusPanel.cpp

${OBJECTDIR}/_ext/cf7d2710/SwapPanel.o: /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/panel/SwapPanel.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/cf7d2710
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/cf7d2710/SwapPanel.o /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/panel/SwapPanel.cpp

${OBJECTDIR}/_ext/2c8a6064/GenericWindow.o: /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/window/GenericWindow.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/2c8a6064
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2c8a6064/GenericWindow.o /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/window/GenericWindow.cpp

${OBJECTDIR}/_ext/2c8a6064/MainWindow.o: /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/window/MainWindow.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/2c8a6064
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2c8a6064/MainWindow.o /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/window/MainWindow.cpp

${OBJECTDIR}/_ext/2c8a6064/UserWindow.o: /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/window/UserWindow.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/2c8a6064
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2c8a6064/UserWindow.o /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/window/UserWindow.cpp

${OBJECTDIR}/_ext/2c8a6064/WindowManager.o: /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/window/WindowManager.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/2c8a6064
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2c8a6064/WindowManager.o /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/window/WindowManager.cpp

${OBJECTDIR}/handler/PeriodicHandler.o: handler/PeriodicHandler.cpp
	${MKDIR} -p ${OBJECTDIR}/handler
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/handler/PeriodicHandler.o handler/PeriodicHandler.cpp

${OBJECTDIR}/handler/Player/Player.o: handler/Player/Player.cpp
	${MKDIR} -p ${OBJECTDIR}/handler/Player
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/handler/Player/Player.o handler/Player/Player.cpp

${OBJECTDIR}/handler/PlayerHandler.o: handler/PlayerHandler.cpp
	${MKDIR} -p ${OBJECTDIR}/handler
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/handler/PlayerHandler.o handler/PlayerHandler.cpp

${OBJECTDIR}/handler/UserHandler.o: handler/UserHandler.cpp
	${MKDIR} -p ${OBJECTDIR}/handler
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/handler/UserHandler.o handler/UserHandler.cpp

${OBJECTDIR}/handler/WebHandler.o: handler/WebHandler.cpp
	${MKDIR} -p ${OBJECTDIR}/handler
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/handler/WebHandler.o handler/WebHandler.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

resources/resources.o: resources/resources.rc resources/resources.h
	${MKDIR} -p resources
	@echo Compiling resources...
	windres.exe resources/resources.rc resources/resources.o

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
