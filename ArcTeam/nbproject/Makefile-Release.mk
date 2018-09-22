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
	${OBJECTDIR}/_ext/7f5b181b/FooterPanel.o \
	${OBJECTDIR}/_ext/7f5b181b/PlayersPanel.o \
	${OBJECTDIR}/_ext/7f5b181b/SwapPanel.o \
	${OBJECTDIR}/handler/PeriodicHandler.o \
	${OBJECTDIR}/handler/Player/Player.o \
	${OBJECTDIR}/handler/PlayerHandler.o \
	${OBJECTDIR}/handler/UserHandler.o \
	${OBJECTDIR}/handler/WebHandler.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/ui/GenericWindow.o \
	${OBJECTDIR}/ui/MainWindow.o \
	${OBJECTDIR}/ui/UserWindow.o \
	${OBJECTDIR}/ui/WindowManager.o


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
LDLIBSOPTIONS=-L/cygdrive/C/cygwin64/bin -lgdi32 -lcurl.dll -lshlwapi -lGdiPlus resources/resources.o -lcomctl32

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

${OBJECTDIR}/_ext/7f5b181b/FooterPanel.o: /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/FooterPanel.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/7f5b181b
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7f5b181b/FooterPanel.o /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/FooterPanel.cpp

${OBJECTDIR}/_ext/7f5b181b/PlayersPanel.o: /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/PlayersPanel.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/7f5b181b
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7f5b181b/PlayersPanel.o /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/PlayersPanel.cpp

${OBJECTDIR}/_ext/7f5b181b/SwapPanel.o: /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/SwapPanel.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/7f5b181b
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/7f5b181b/SwapPanel.o /cygdrive/C/Users/Urt/Documents/Projects/ArcTeam/ArcTeam/ui/SwapPanel.cpp

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

${OBJECTDIR}/ui/GenericWindow.o: ui/GenericWindow.cpp
	${MKDIR} -p ${OBJECTDIR}/ui
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ui/GenericWindow.o ui/GenericWindow.cpp

${OBJECTDIR}/ui/MainWindow.o: ui/MainWindow.cpp
	${MKDIR} -p ${OBJECTDIR}/ui
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ui/MainWindow.o ui/MainWindow.cpp

${OBJECTDIR}/ui/UserWindow.o: ui/UserWindow.cpp
	${MKDIR} -p ${OBJECTDIR}/ui
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ui/UserWindow.o ui/UserWindow.cpp

${OBJECTDIR}/ui/WindowManager.o: ui/WindowManager.cpp
	${MKDIR} -p ${OBJECTDIR}/ui
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/ui/WindowManager.o ui/WindowManager.cpp

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
