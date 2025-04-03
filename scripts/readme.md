# Creating the combined Cunilog module source code files

To create the combined source code files the following scripts are provided:

- __CreateCombinedCunilog.cmd__ (Windows command-line script/batch file)
- __CreateCombinedCunilog.pl__ (Perl script)
- __CreateCombinedCunilog.sh__ (Bash shell script)

The scripts have identical functionality. They read the file __SingleFiles.txt__
and use it as the basis to create the files __cunilog_combined.c__ and
__cunilog_combined.h__ in folder __src/c/combined__.

These two files (__cunilog_combined.c__ and
__cunilog_combined.h__) can then either be added to your project(s), or serve as the basis for the static library __libcunilog__. If you link to Cunilog statically, include __cunilog_combined.h__ in any code file that requires access to Cunilog.

See [Building Cunilog](../building.md) for details on how to build Cunilog as a static library or directly add the combined files to your project(s).

# Creating the export definition file for the Windows DLLs

The Perl script __CreateWindowsDLLDef.pl__ is used to create the export definition file __src/def/libcunilog.def__. The file __scripts/libcunilog_src.def__ is the source file to be edited. Use __@nnn__ as a placeholder for the ordinal value of an exported function or variable.

The script takes the file __scripts/libcunilog_src_head.def__ and places it in __src/def/libcunilog.def__ first, then reads __scripts/libcunilog_src.def__ and replaces __@nnn__ entries with the calculated ordinal values for the exports. The end result is stored in __src/def/libcunilog.def__.

See [Exporting from a DLL Using DEF Files](https://learn.microsoft.com/en-us/cpp/build/exporting-from-a-dll-using-def-files?view=msvc-170) and [Module-Definition (.Def) Files](https://learn.microsoft.com/en-us/cpp/build/reference/module-definition-dot-def-files?view=msvc-170) for more details.

