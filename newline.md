
# Newline/Line Endings

## POSIX

In POSIX lines of text end with a Line Feed character (LF, 10d, 0Ah).
See [Newline](https://en.wikipedia.org/wiki/Newline) on Wikipedia.
A Line Feed ASCII character is Cunilog's default newline, or end of line (EOF) character.

## Windows

On Windows, the "native" line ending is a sequence of an ASCII Carriage Return (CR, 13d, 0Dh)
and an ASCII Line Feed (LF, 10d, 0Ah) character.

Most Windows text editors and logfile viewers are also fine with POSIX line endings, which consist
of a stand-alone Line Feed character only.

The Windows text editor Notepad used to not be able to understand POSIX line endings. Developers
were therefore forced to ensure that lines of text were correctly ended with a CR + LF sequence.

In 2018 Microsoft have addressed this inconsistency and updated Notepad accordingly.
See [Introducing extended line endings support in Notepad](https://devblogs.microsoft.com/commandline/extended-eol-in-notepad/).

With the Notepad hurdle gone, Cunilog's default newline sequence on Windows is also a single Line Feed ASCII character.

If you still need to support versions of Notepad up to Mai 2018, use one of the "__Ex__" Cunilog target initialisation functions, for instance __InitCUNILOG_TARGETstaticEx ()__, which let you specify a line ending for the target during initialisation. Use __cunilogNewLineWindows__ as line ending. This adds
Windows native end of line sequnces of CR + LF.

Alternatively, initialise the target first with an initialisation function whose
name doesn't end with "__Ex__", and call __configCUNILOG_TARGETcunilognewline ()__ with line ending argument __cunilogNewLineWindows__ before actual logging has begun (before logging functions have been called).

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
