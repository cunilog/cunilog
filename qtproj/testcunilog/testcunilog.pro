#****************************************************************************************
#
#	File:		testcunilog.pro
#	Why:		Qt (qmake) project file for testcunilog.
#	OS:			-
#	Author:		Thomas
#	Created:	2024-10-12
#  
# History
# -------
#
# When			Who				What
# ---------------------------------------------------------------------------------------
# 2024-10-12	Thomas			Created by copying from another qmake project file.
#
#****************************************************************************************

# The name of this project. Makes some code further down more flexible and portable.
PROJECTNAME=testcunilog

TARGET = $${PROJECTNAME}	# See http://doc.qt.io/qt-5/qmake-variable-reference.html#target .
QT -= gui					# It is a console application.
TEMPLATE = app

CONFIG += c99				# See http://doc.qt.io/qt-5/qmake-variable-reference.html#config .
#CONFIG += c++11				# See http://doc.qt.io/qt-5/qmake-variable-reference.html#config .
CONFIG += force_debug_info	# Force the generation of debug information. On Windows, this creates
							#	a .pdb file.
							#	See https://stackoverflow.com/questions/6993061/build-qt-in-release-with-debug-info-mode .
CONFIG += cmdline			# Cross-platform command-line application.
CONFIG -= gui
# Speeds up the compilation process.
CONFIG -= qt				# See https://doc.qt.io/qt-5/qmake-variable-reference.html#config .

# See https://forum.qt.io/topic/96936/macos-mojave-and-qt-creator/3 . This warning might
#	pop up on OSX Mojave. I reckon it'll disappear with a newer version of Qt. According
#	to the documentation, Qt 5.12.0 is the first one to fully support Mojave (OSX 10.14).
CONFIG += sdk_no_version_check

# Cunilog requirements.
DEFINES += HAVE_STRWILDCARDS
win32:DEFINES += _CRT_SECURE_NO_WARNINGS
win32:DEFINES += HAVE_ADVAPI32
win32:DEFINES += HAVE_SHELLAPI
win32:DEFINES += HAVE_USERENV
#win32:LIBS += Shell32.lib

# The tests
DEFINES += CUNILOG_DEBUG_USE_TEST_ROTATOR_VALUES
DEFINES += CUNILOG_BUILD_TEST_FNCTS
DEFINES += STRNEWLINE_BUILD_TEST
DEFINES += BUILD_STRHEXDUMP_TEST_FNCT
DEFINES += UBF_TIME_BUILD_UBF_TIMES_TEST_FUNCTION
DEFINES += UBF_BUILD_STRINTUINT_TEST
DEFINES += STRWILDCARDS_BUILD_TEST_FNCT
DEFINES += BUILD_DEBUG_UBF_STRFILESYS_TESTS
DEFINES += STRCUSTOMFMT_BUILD_TEST_FNCTS
DEFINES += BUILD_BULKMALLOC_TEST_FUNCTIONS
DEFINES += U_CHECK_UTF8_BUILD_TEST_FNCT
DEFINES += BUILD_TEST_WINAPI_U8_FNCT
DEFINES += PROCESS_HELPERS_BUILD_TEST_FNCT

# If this -ldl is missing, the linker on Linux complains with
#	"sqlite3.o: undefined reference to symbol 'dlclose@@GLIBC_2.2.5'".
#	See https://linux.die.net/man/3/dlclose .
linux:LIBS += \
		-ldl

# See
#	https://stackoverflow.com/questions/14015950/which-library-to-link-osx
macx:LIBS += \
		-framework CoreFoundation
macx:LIBS += \
		-framework Cocoa
		
HEADERS += \
	../../src/c/OS/Apple/TrashCan.h \
    ../../src/c/OS/CompressFile.h \
    ../../src/c/OS/ExeFileName.h \
    ../../src/c/OS/POSIX/PsxCompressFile.h \
    ../../src/c/OS/POSIX/PsxExeFileName.h \
    ../../src/c/OS/POSIX/PsxHome.h \
    ../../src/c/OS/POSIX/PsxReadDirFncts.h \
    ../../src/c/OS/POSIX/PsxSharedMutex.h \
    ../../src/c/OS/POSIX/PsxTrash.h \
    ../../src/c/OS/ProcessHelpers.h \
    ../../src/c/OS/SharedMutex.h \
    ../../src/c/OS/UserHome.h \
    ../../src/c/OS/Windows/CompressNTFS_U8.h \
    ../../src/c/OS/Windows/WinAPI_ReadDirFncts.h \
    ../../src/c/OS/Windows/WinAPI_U8.h \
    ../../src/c/OS/Windows/WinAPI_U8_Test.h \
    ../../src/c/OS/Windows/WinExeFileName.h \
    ../../src/c/OS/Windows/WinSharedMutex.h \
    ../../src/c/cunilog/cunilog.h \
    ../../src/c/cunilog/cunilogcfgparser.h \
    ../../src/c/cunilog/cunilogdefs.h \
    ../../src/c/cunilog/cunilogevtcmds.h \
    ../../src/c/cunilog/cunilogevtcmdsstructs.h \
    ../../src/c/cunilog/cunilogstructs.h \
    ../../src/c/datetime/ISO__DATE__.h \
    ../../src/c/datetime/shortmonths.h \
    ../../src/c/datetime/timespecfncts.h \
    ../../src/c/datetime/ubf_date_and_time.h \
    ../../src/c/datetime/ubf_times.h \
    ../../src/c/dbg/dbgcountandtrack.h \
    ../../src/c/dbg/ubfdebug.h \
    ../../src/c/mem/VectorC.h \
    ../../src/c/mem/bulkmalloc.h \
    ../../src/c/mem/membuf.h \
    ../../src/c/mem/memstrstr.h \
    ../../src/c/mem/ubfmem.h \
    ../../src/c/pre/ArrayMacros.h \
    ../../src/c/pre/SingleBits.h \
    ../../src/c/pre/Warnings.h \
    ../../src/c/pre/externC.h \
    ../../src/c/pre/platform.h \
    ../../src/c/pre/unref.h \
    ../../src/c/string/check_utf8.h \
    ../../src/c/string/stransi.h \
    ../../src/c/string/strcustomfmt.h \
    ../../src/c/string/strfilesys.h \
    ../../src/c/string/strhex.h \
    ../../src/c/string/strhexdump.h \
    ../../src/c/string/strhexdumpstructs.h \
    ../../src/c/string/strintuint.h \
    ../../src/c/string/strisabsolutepath.h \
    ../../src/c/string/strisdotordotdot.h \
    ../../src/c/string/strmembuf.h \
    ../../src/c/string/strnewline.h \
    ../../src/c/string/struri.h \
    ../../src/c/string/strwildcards.h \
    ../../src/c/string/ubfcharscountsandchecks.h \
    ../../src/c/testcunilog/CunilogTestFncts.h \
    ../../src/c/testcunilog/testcunilog.h

SOURCES += \
	../../src/c/OS/Apple/TrashCan.c \
    ../../src/c/OS/CompressFile.c \
    ../../src/c/OS/ExeFileName.c \
    ../../src/c/OS/POSIX/PsxCompressFile.c \
    ../../src/c/OS/POSIX/PsxExeFileName.c \
    ../../src/c/OS/POSIX/PsxHome.c \
    ../../src/c/OS/POSIX/PsxReadDirFncts.c \
    ../../src/c/OS/POSIX/PsxSharedMutex.c \
    ../../src/c/OS/POSIX/PsxTrash.c \
    ../../src/c/OS/ProcessHelpers.c \
    ../../src/c/OS/SharedMutex.c \
    ../../src/c/OS/UserHome.c \
    ../../src/c/OS/Windows/CompressNTFS_U8.c \
    ../../src/c/OS/Windows/WinAPI_ReadDirFncts.c \
    ../../src/c/OS/Windows/WinAPI_U8.c \
    ../../src/c/OS/Windows/WinAPI_U8_Test.c \
    ../../src/c/OS/Windows/WinExeFileName.c \
    ../../src/c/OS/Windows/WinSharedMutex.c \
    ../../src/c/cunilog/cunilog.c \
    ../../src/c/cunilog/cunilogcfgparser.c \
    ../../src/c/cunilog/cunilogevtcmds.c \
    ../../src/c/cunilog/cunilogevtcmdsstructs.c \
    ../../src/c/cunilog/cunilogstructs.c \
    ../../src/c/datetime/ISO__DATE__.c \
    ../../src/c/datetime/shortmonths.c \
    ../../src/c/datetime/timespecfncts.c \
    ../../src/c/datetime/ubf_date_and_time.c \
    ../../src/c/datetime/ubf_times.c \
    ../../src/c/dbg/dbgcountandtrack.c \
    ../../src/c/dbg/ubfdebug.c \
    ../../src/c/mem/VectorC.c \
    ../../src/c/mem/bulkmalloc.c \
    ../../src/c/mem/membuf.c \
    ../../src/c/mem/memstrstr.c \
    ../../src/c/mem/ubfmem.c \
    ../../src/c/string/check_utf8.c \
    ../../src/c/string/stransi.c \
    ../../src/c/string/strcustomfmt.c \
    ../../src/c/string/strfilesys.c \
    ../../src/c/string/strhex.c \
    ../../src/c/string/strhexdump.c \
    ../../src/c/string/strhexdumpstructs.c \
    ../../src/c/string/strintuint.c \
    ../../src/c/string/strisabsolutepath.c \
    ../../src/c/string/strisdotordotdot.c \
    ../../src/c/string/strmembuf.c \
    ../../src/c/string/strnewline.c \
    ../../src/c/string/struri.c \
    ../../src/c/string/strwildcards.c \
    ../../src/c/string/ubfcharscountsandchecks.c \
    ../../src/c/testcunilog/CunilogTestFncts.c \
    ../../src/c/testcunilog/testcunilog.c
