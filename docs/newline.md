
# Newline/Line Endings

## POSIX

In POSIX, lines of text end with a Line Feed character (LF, 10d, 0Ah).
See [Newline](https://en.wikipedia.org/wiki/Newline) on Wikipedia.
A Line Feed ASCII character is Cunilog's default newline, or end of line (EOF) character.

## Windows

On Windows, the "native" line ending is a sequence of an ASCII Carriage Return (CR, 13d, 0Dh)
and an ASCII Line Feed (LF, 10d, 0Ah) character.

Most Windows text editors and logfile viewers are also fine with POSIX line endings, which consist
of a single Line Feed character only.

In the past, the Windows text editor Notepad had not been able to understand POSIX line endings. Developers
were therefore forced to ensure that lines of text were correctly ended with a CR + LF sequence.

Microsoft have addressed this inconsistency and updated Notepad accordingly in 2018.
See [Introducing extended line endings support in Notepad](https://devblogs.microsoft.com/commandline/extended-eol-in-notepad/).

With the Notepad hurdle gone, Cunilog's default newline sequence on Windows is also a single Line Feed ASCII character.
However, Windows versions below build 17763 do *not* support single Line Feed line endings. Of these, version 1607 (build 14393) is officially supported until October 2026. Refer to [Supported versions of Windows client](https://learn.microsoft.com/en-us/windows/release-health/supported-versions-windows-client) for details.

Since Dec 2025, Cunilog checks the version of Notepad installed, which is usually identical to the Windows version, when the first Cunilog target is created or initialised after an application has been started, and when no particular line ending has been specified explicitely. To avoid this version check when further targets are initialised or created, Cunilog sets a flag and uses it when more targets are initialised or created. The function __CunilogAutoNewLine ()__ returns the line ending picked automatically. This behaviour may be reviewed and possibly adjusted in due time, depending on how long Cunilog is still required to run on versions of Windows that do not have the correct support for POSIX line endings.

If you already know that you still need to support versions of Notepad lower than build 17763, and want to avoid the small overhead induced by the version check, use one of the "__Ex__" Cunilog target initialisation functions, for instance __InitCUNILOG_TARGETstaticEx ()__. These functions let you specify a line ending for the target during initialisation. Set __cunilogNewLineWindows__ as line ending to use Windows native end of line sequnces of CR + LF.

If you already know that you do not need to support versions of Windows/Notepad before build 17763, you can also avoid the overhead of the version check and set this value to __cunilogNewLinePOSIX__ to make Cunilog write out LF end of line markers only.

Alternatively, initialise the target first with an initialisation function whose
name doesn't end with "__Ex__", and call __configCUNILOG_TARGETcunilognewline ()__ with line ending argument __cunilogNewLineWindows__ or __cunilogNewLineWindows__ before actual logging has begun (before logging functions have been called).

## Legacy Systems

Cunilog can be built to support all sorts of line endings. When CUNILOG_NEWLINE_EXTENDED
is defined, additional legacy or exotic line endings are available, for example for zOS,
QNX, and RISC OS.

To make Cunilog write those legacy line endings, call one of the "__Ex__" Cunilog target
initialisation functions, for instance __InitCUNILOG_TARGETstaticEx ()__, which let you specify
a line ending when the target is initialised. Or, initialise the target first
with an initialisation function whose name doesn't end with "__Ex__", and then
call __configCUNILOG_TARGETcunilognewline ()__ with the preferred line ending
before any logging functions have been called.
