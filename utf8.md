
# Cunilog and UTF-8

Cunilog does not understand the concept of UTF-8. All strings are handled like
ASCII strings. Cunilog treats a UTF-8 codepoint consisting of two or more
octets/bytes, like a string that consists of two or more ASCII characters.

For this reason Cunilog generally does not check if UTF-8 strings provided are
actually well-formed and valid UTF-8. An exception are functions that
distinguish between text and binary data and detect the correct output data
implicitely.

Cunilog however includes a module/unit called check_utf8 written by
YASUOKA Masahiko (https://github.com/yasuoka/check_utf8). Since the function
name is probably relatively common, it has been renamed to __c_check_utf8 ()__ in
order to avoid name clashes.

Since checking if text is well-formed and valid UTF-8 is a relatively expensive
operation, it is recommended to reduce the amount of checks as much as possible
but maybe not so far down to a point where security issues might arise.

Texts that are logged to a target are passed between Cunilog processors and
almost always end up in a text file. If these texts are not correct UTF-8, the
worst that can happen in most cases is that they end up somewhat crippled in a
text file. This of course assumes that software used to view or further
process these logfiles isn't crashing due to malformed UTF-8 sequences.

On the other hand, when a CUNILOG_TARGET structure is initialised with the
dedicated functions and logging folder and application name are provided, who
knows what kind of filename the operating system produces when creating a logfile?
Initialisation usually only happens once per target throughout the lifetime of
an application. In this case checking beforehand if the arguments are valid
UTF-8 might be a good habit. However, if these parameters come from user input
or other unknown sources, it should go without saying that UTF-8 checks are a must.

Remember that Cunilog does not carry out any of these checks.

## Windows and UTF-8

Windows and UTF-8 are not at all best friends. Microsoft have done a lot to
improve the situation but it's still quite murky.

The native character set of Windows is UTF-16, which derived from the original
UCS-2 [Universal Coded Character Set](https://en.wikipedia.org/wiki/Universal_Coded_Character_Set).
Many Windows APIs are available in two different flavours: Functions/macros
ending in "A" and functions/macros ending with a "W". When a function/macro is
called without either ending, a project's character set configuration determines
the final function/macro name.

Since 2019 many Windows API functions accept UTF-8 when the ASCII version of
an API is called (the "A" version). The documentation however does not go into
a lot of details here. Long filenames (longer than 260 characters) still don't
seem to be possible when using "A" API versions and most APIs still don't support
UTF-8.

Cunilog, therefore, still converts UTF-8 strings to Windows UTF-16 before calling
most of the system APIs. It does the opposite with strings coming back from the
Windows API. One reason for this is to support very long filenames. (However, this
is a different topic altogether, as many Windows APIs don't support very long
filenames at all anyway yet).

## Windows and a console

Since 2019 the Windows console accepts UTF-8 output and provides input in UTF-8 when
configured accordingly. Yeah, __when configured accordingly__. This means when
the console is set to code page 65001 (CP_UTF8). Note that the behaviour differs
between versions of Windows, in particular between versions/updates after 2019
and before that.

The list with [Code Page Identifiers](https://learn.microsoft.com/en-us/windows/win32/intl/code-page-identifiers)
doesn't seem to contain a code page for UTF-16, at least not for unmanaged
applications. In other words, once an application has set an attached console to
CP_UTF8 (code page 65001), there's no simple way back.

Versions of Windows __before__ 2019 require the console to be set to UTF-16, and the "W"
versions of the input and output functions to be used. Windows versions __from__
2019 accept the console to be configured for UTF-8 and then understand UTF-8
for the "A" output functions.

Wikipedia's got a nice overview explaining that mess.
Check out [Unicode in Microsoft Windows](https://en.wikipedia.org/wiki/Unicode_in_Microsoft_Windows).

Microsoft recommends an application manifest.
See [Use UTF-8 code pages in Windows apps](https://learn.microsoft.com/en-us/windows/apps/design/globalizing/use-utf8-code-page).

By default, Cunilog configures a console attached to an application for UTF-8
the very first time it sends text to it. This may or may not be a good thing to
do. It is a good thing if the console isn't used for anything else. It is a bad
thing if the application expects the console to be configured differently.

You can tell Cunilog to set up the console beforehand to avoid that the first
logging or print function that outputs something to the console changes it.

__CunilogSetConsoleToUTF8 ()__ sets the console to UTF-8. It is not required to call
this function as Cunilog calls it automatically just before it outputs something
to the console the very first time. From that moment on Cunilog uses the ASCII
function [puts ()](https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/puts-putws?view=msvc-170)
to output to the console. Note that puts () or one of its
derivatives is literally the only console output function Cunilog ever invokes.

__CunilogSetConsoleToUTF16 ()__ sets the console to UTF-16. Cunilog then uses the
UTF-16 version of puts (), which is [_putws ()](https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/puts-putws?view=msvc-170), for console output, of course only
after the text to ouput has been converted from UTF-8 to UTF-16 first.
Maybe I'm doing it wrong, but the console output itself, and not the conversion
from UTF-8 to UTF-16, is terribly slow.
I haven't measured it but it feels
like console output is at least 10 or 20 times slower than when the console is
set up for UTF-8 and puts () is called instead.

__CunilogSetConsoleToNone ()__ configures, as the name suggests, the console
output... not at all. If you call this function before Cunilog had to output something
to the console it won't change the console at all. This is the fastest option
but doesn't print unicode characters correctly if the console isn't configured
correctly by the application beforehand. To send text to the console, Cunilog calls
[puts ()](https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/puts-putws?view=msvc-170).

If you don't need console output, another option is to just suppress it altogether.
Either set up your own Cunilog processor array/chain that doesn't contain an
echo processor, or call
__configCUNILOG_TARGETdisableEchoProcessor ()__ on the target just after
it has been initialised and before any of the logging functions have been
invoked.

Note that when Cunilog changes the console on Windows, this also affects all
__CUNILOG_TARGET__ Cunilog targets, and of course the application's console output too.
A Windows application can only be attached to
a single console, and changes to this console's configuration affect all
functions reading from or writing to that console. To be fair, Windows distinguishes
between input and output but Cunilog does not, at least not currently. When Cunilog
configures the console attached to an application it does this for output as well
as input at the same time.
