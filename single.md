# Specific (single) Cunilog Modules in your Project

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
