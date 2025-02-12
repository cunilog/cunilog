
# Cunilog Basics

## General
### Comments and Documentation

Each Cunilog interface definition, function, macro, structure, variable, constant, and enumeration
should be self-explanatory in the header file(s). The comments above or next to the
definition, function, macro, structure, variable, constant, or enumeration should contain enough
information to understand their purposes and how to use them appropriately.

Often the descriptions are detailed enough to recreate functions from scratch without having seen
their code. However, this may not always be the case for simplicity reasons and to allow for comments
that get straight to the point from a user's/caller's perspective. If in doubt, check the source code.

If the description isn't detailed enough, then the function, macro, or object is most likely a variation
of one of the functions, macros, or objects before/above. These comments may contain only differences
to the previous object, function, or macro, and necessary information is found there.

If something consistently requires looking at the code in order to understand how to call or use it, though, this is considered a bug and should be rectified.

To distinguish between functions and macros in the documentation and comments, functions are normally referred to as __function_name ()__ with a single space between name and opening bracket while macros are referred to as __macro_name()__ without space.

### Debugging

When compiled for release versions Cunilog carries out only the most imporant parameters and bounds checks.
It is recommended to always test debug builds first. Debug builds contain tons of assertions
and abort messages that should catch most argument mismatches, buffer overruns, out-of-bound enums, etc.

First, build a debug version of your application and make sure you also use a Cunilog debug
build, then test it to ensure all function and macro arguments are good and that there are no
buffer overruns or accidental NULL pointers.

### String Arguments

Unless mentioned otherwise, most functions and macros that accept string
arguments/parameters also expect a length parameter that tells the function/macro
how long the string is. The length is the length of a string excluding a
terminating NUL character as if obtained via a call to strlen (). For example,
"ABC" has a length of 3.

This length argument can be USE_STRLEN, in which case the function/macro calls
strlen () implicitely on the string. USE_STRLEN is defined as ((size_t) -1).

If the length of a string is provided instead of USE_STRLEN, the function/macro
will not read beyond this length. This means that most functions/macros can
be called with string buffers that are not NUL-terminated.

Cunilog treats all strings as UTF-8 strings without actually understanding the
concept of UTF-8. For instance, a UTF-8 codepoint consisting of 3 octets/bytes
is worked with as a string that consists of 3 characters. It is the caller's
responsibility to ensure UTF-8 passed on to Cunilog is correct UTF-8.

For more information on Cunilog and UTF-8, please refer to [Cunilog and UTF-8](utf8.md).

## Logging Target

In Cunilog terms a log file is called a __target__. In fact, a __target__
can be anything from console output to log file or both or a database or
whatever. This is entirely configurable. Whatever the __target__ is, all
logging functions expect a target.

An application can create an arbitrary number of targets for Cunilog, or just
use the default (static) __target__. Logging to targets can be suspended and resumed.
Every __target__, however, needs to be configured first so that Cunilog knows what to do
with it. This also applies to the default (static) __target__.

Logging functions create events, and events are sent to targets. A target can be configured to fork/duplicate events to other targets. Events can also be redirected to another target.

All logging functions expect as their first parameter a pointer to a __target__
structure of type __SCUNILOGTARGET__. For the default (static) __target__,
macros are provided that end in _static. These macros set the __target__ to an
internal (static) __SCUNILOGTARGET__ structure, which is shared by all these
macros/functions.

