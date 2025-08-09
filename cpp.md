# Cunilog and C++

## Compatibility

Cunilog should be entirely compatible with C++ as long as it is built with a
C compiler. Each header file contains (or, as of 2025-08, at least *should* contain,
because actually still untested) C++ extern "C" definitions so that they can be
included from C++:
```C
#ifdef __cplusplus
	extern "C"	{
#endif
```
```C
#ifdef __cplusplus
				}
#endif
```

Do not try to compile any of the code files as C++ code. While it might compile,
some modules (compilation units) may contain code that is perfectly valid in C
but produces undefined behaviour in C++. This evidently applies to the module
membuf and all modules that depend on it but may also apply to others.

The reason why the module membuf must not be compiled as C++ is because it relies
heavily on the structure below. In fact, the entire module acts as a class around
that structure.
```C
/*
	The structure that holds the buffer and its length. It is meant to be a generic
	buffer. If a required type is missing, please feel free to add it.
*/
typedef struct smembuf
{
	union
	{
		void			*pvoid;
		char			*pch;
		const char      *pcc;
		signed char		*psc;
		unsigned char	*puc;
		size_t			*pst;
		uint64_t		*pu64;
	} buf;
	size_t				size;
	#ifdef DEBUG
		char			initComplete;
	#endif
} SMEMBUF;
```
The union serves as an implicit type converter. This is valid in C but not in
C++ due to C++'s *active member* rule. See the C/C++ paragraph at https://en.wikipedia.org/wiki/Union_type.

## Copy & Paste

For the above reasons, copying any of the C code from any of the Cunilog modules,
and pasting it into a C++ unit is discouraged, unless you know what you're doing and
you're 100 % certain the copied passage won't introduce undefined behaviour in your C++ code.

A C++ compiler might pick up some, most, or all incompatibility issues. For
instance, returned pointers from calls to malloc () are compatible with any
pointer type in C. In C++, however, a cast is required.

It is recommended to always switch on all compiler warnings and treat them as
errors.

The modules Cunilog consists of can usually be utilised separately. You can build
them as C code and include their headers from your C++ modules/units.

## Specific Cunilog Modules in your Project

To include a single module/translation unit/code and header file into your own
project without including the entire combined Cunilog code and header files,
you may want to drop this module and the files/modules it depends on in a single
directory for the build process.

This is possible by defining UBF_USE_FLAT_FOLDER_STRUCTURE. Each header and code
file that is part of Cunilog contains an include block similar to this one:
```C
#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./functionptrtpydef.h"
		#include "./restrict.h"
		#include "./ubfmem.h"
	#else
		#include "./../pre/externC.h"
		#include "./../pre/functionptrtpydef.h"
		#include "./../pre/restrict.h"
		#include "./../mem/ubfmem.h"
	#endif

#endif
```
The default is to include files from the Cunilog folder/directory tree structure.
If UBF_USE_FLAT_FOLDER_STRUCTURE is defined, all files are expected to reside in
the same directory.
