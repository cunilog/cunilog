
# Cunilog basics

## General
### Comments and documentation

Each Cunilog interface definition, function, macro, structure, variable, constant, and enumeration
should be self-explanatory in the header file(s). The comments above or next to the
definition, function, macro, structure, variable, constant, or enumeration should contain enough
information to understand their purposes and how to use them appropriately.

Often the descriptions are detailed enough to recreate functions from scratch without having seen
their code. However, this may not always be the case for simplicity reasons and to allow for comments
that get straight to the point from the caller's perspective. If in doubt, check the source code.

If the description isn't detailed enough, then the function, macro, or object is most likely a variation
of one of the functions, macros, or objects before/above. These comments may contain only differences
to the previous object, function, or macro, and necessary information is found there.

If something consistently requires referring to the code in order to understand its use, it is considered a bug and should be rectified.

To distinguish between functions and macros, in the documentation and comments, functions are normally referred to as __function_name ()__ with a single space between name and opening bracket while macros are referred to as __macro_name()__ without space.

### Debugging

When compiled for release versions Cunilog carries out only the most imporant parameters and bounds checks.

It neither checks upper nor lower bounds of enumeration types. Function parameters that are not documented to be allowed to be NULL are not checked against being NULL. String parameters complemented by a length argument do not have their buffers examined to see if they're eventually NUL-terminated.

It is recommended to always test debug builds first. Debug builds include extensive assertions
and abort messages that should catch most argument mismatches, buffer overruns, out-of-bounds enums, etc.

First, build a debug version of your application and make sure you also use a Cunilog debug
build.  Then test it to ensure all function and macro arguments are good and that there are no
buffer overruns or accidental NULL pointers.

### Name collisions

This is something that may happen every now and then, in particular in bigger projects. Many function and object
names in Cunilog do not have unique prefixes. If this happens, the names should be changed where it makes
most sense. This means if a name is already relatively unique it should probably be changed in the application to avoid the clash. If Cunilog uses a very common name it should be changed in Cunilog. However, I would like to avoid having general prefixes like many other projects and libraries.
Feel free to raise an issue.

### String arguments

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

## Logging target

In Cunilog a log file is called a target. In fact, a target
can be anything from console output to log file or both or a database or
any other destination. This is entirely configurable. Whatever the target is, all
logging functions expect a target.

An application can create an arbitrary number of targets for Cunilog, or just
use the default (static) target. Logging to targets can be suspended and resumed.
Every target, however, needs to be configured first so that Cunilog knows what to do
with it. This also applies to the default (static) target.

Logging functions create events and events are sent to targets. A target can be configured to fork/duplicate events to other targets. Events can also be redirected to another target.

All logging functions expect as their first parameter a pointer to a target
structure of type __CUNILOG_TARGET__. For the default (static) target,
macros are provided that end in _static. These macros set the target to an
internal (static) __CUNILOG_TARGET__ structure, which is shared by all these
macros/functions.

The characteristics of a Cunilog target are specified when it is initialised. Some of these
characteristics can be changed afterwards but need to be applied before the first logging
function that uses this target is called. Some characteristics can still be changed even after
logging functions have been called. If the application only has a single thread and the target
has been initialised for a single thread only, all of its characterisitcs can be changed if
enough care is taken.

### Log path and application name

Cunilog distinguishes between a log path and an application's name. By default, events are written
to text files named (log path)__/__(application name)___YYYY-MM-DD.log__.

If the path is relative, the enumeration __enCunilogRelLogPath__ decides on an appropriate base path.

### Threading

The type of a Cunilog target is probably its most important characteristic. This type cannot be changed
later unless the application and the target are both single-threaded.

The __enum cunilogtype__ denotes the type of a target.

| __enum cunilogtype__ | |
| :------------------- | --- |
| cunilogSingleThreaded | Only a single thread can use this target |
| cunilogMultiThreaded  | Several threads can use this target but function calls block if the target is busy |
| cunilogSingleThreadedSeparateLoggingThread cunilogMultiThreadedSeparateLoggingThread | A single or several threads can use this target but the actual work is done in a separate logging thread
| cunilogMultiProcesses | Not implemented yet |

Note that __cunilogSingleThreadedSeparateLoggingThread__ is meant for a single application thread only but the actual logging tasks are delegated to a separate logging thread via an event queue. On the other hand __cunilogMultiThreadedSeparateLoggingThread__ is meant to do the same in a multi-threaded application. However, both are currently implemented identically.

If unsure, __cunilogMultiThreadedSeparateLoggingThread__ is most likely what you should use. For more details on Cunilog target types, check the comments in the header file or have a look at the code.

## Processors

When an event goes to a target it is passed through an array of processors, literally in a loop.
The C type definition for a Cunilog processor structure is __CUNILOG_PROCESSOR__. Each target holds a pointer
to an array of processors. If a target is initialised without a processors array, the default
is assigned.

Each processor is assigned a certain task. Cunilog provides a default set of tasks for processors
to carry out. A custom task is also available for which a callback function can be invoked.
Each processor is assigned precisely one task, which is the member __task__ of data type __enum cunilogprocesstask__.


## Rotators

Rotators are s special type of processor. While other processors do something with an event, the job of a rotator is to do something with the logfile or an entire set of logfiles.

See [Processors and Rotators](processors.md) for more information.
