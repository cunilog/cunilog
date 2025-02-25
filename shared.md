
# Cunilog in a dynamically-linked (shared) library

Cunilog can be built as a shared library that is loaded at runtime. On Windows this is called a dynamically linked library, or short [DLL](https://learn.microsoft.com/en-us/windows/win32/dlls/dynamic-link-libraries). The filename extension of these files is __.dll__. On Unix/Linux systems they're called shared objects and usually have the filename extension __.so__.

See [Building Cunilog](building.md) on how to create such a library.

A dynamic (shared) library can be loaed in two different ways:
- It is loaded and linked when the application is started. This is called load-time or implicit loading/linking.
- It is loaded and linked when required. This is called run-time or explicit loading/linking.

## Implicit loading/linking

Implicit loading/linking is a relatively straight-forward process and generally requires no special attention.

On Windows, Microsoft call this method [Load-time dynamic linking](https://learn.microsoft.com/en-us/windows/win32/dlls/about-dynamic-link-libraries). Because Windows expects applications to be built, linked to, and use the C runtime libraries in the same manner within application boundaries, all components of the same application must be built identical. See [C runtime (CRT) and C++ standard library (STL)](https://learn.microsoft.com/en-us/cpp/c-runtime-library/crt-library-features?view=msvc-170) and [Building Cunilog](building.md).

## Explicit loading/linking

Loading a library that is shared dynamically and linking to it explicitely is very similar between Windows and POSIX. This method is also called [Run-time dynamic linking](https://learn.microsoft.com/en-us/windows/win32/dlls/about-dynamic-link-libraries). Don't worry about the Microsoft link. The idea is the same for POSIX.

Windows offers the API functions __LoadLibrary ()__ and __LoadLibraryEx ()__ to load modules into the address space of a calling process. POSIX on the other hand has __dlopen ()__, and Linux additionally provides __dlmopen ()__ with similar functionality.

On Windows, one would call __FreeLibrary ()__ to close a handle to the module returned by __LoadLibrary ()__ or __LoadLibraryEx ()__ and decrement its reference count. On POSIX, this would be __dlclose ()__ for handles returned by __dlopen ()__.

The API function [GetProcAddress ()](https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getprocaddress) retrieves the address of a function or data object within the library on Windows. The POSIX equivalent of this function is [dlsym ()](https://linux.die.net/man/3/dlsym).

Cunilog exports all relevant data objects and functions and offers preprocessor definitions for the signatures of exported functions to allow for easier explicit loading and linking.

Typedefs are created for each function's signature. The __typedef__ for a function starts with the prefix __fncpt___ followed by the function name and ends with the postfix ___t__ by default. For instance, the function's __InitSCUNILOGTARGETstatic ()__ signature typedef would be __fncpt_InitSCUNILOGTARGETstatic_t__.

Prefix and postfix of the type definitions for function signatures can be changed when the library is built. Define __CUL_FNCTS_POINTER_PREFIX__ during the build with your preferred prefix and __CUL_FNCTS_POINTER_POSTFIX__ with your preferred postfix.

Because implicitely linked functions are not available when a library is loaded and linked explicitely, some function-like macros are not going to work because they resolve to function names that are simply not available. For instance, the Cunilog function __ShutdownSCUNILOGTARGETstatic ()__ does not work in this case since it is actually a macro that resolves to __ShutdownSCUNILOGTARGET (pSCUNILOGTARGETstatic)__. In order to simulate __ShutdownSCUNILOGTARGETstatic ()__ the address of the pointer __pSCUNILOGTARGETstatic__ that points to the internal static __SCUNILOGTARGET__ structure needs to be obtained first via a call to [GetProcAddress ()](https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getprocaddress) on Windows or [dlsym ()](https://linux.die.net/man/3/dlsym) on POSIX.


