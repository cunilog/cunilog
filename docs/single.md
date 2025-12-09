# Specific (single) Cunilog Modules in your Project

You can build each module Cunilog consists of together with your C or C++
application as long as you compile the Cunilog code files as C code. This means
you can add single modules that suit specific purposes to your projects. If a
code file depends on other code files, it goes without saying that you also need
to add those dependencies.

The headers can be included from C and C++ modules/units.

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
