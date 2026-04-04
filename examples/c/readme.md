# Cunilog examples in C

This folder contains examples on how to use Cunilog from C.

## Building with MSVC

### On the command-line directly

To build the examples with MSVC, open an MSVC command-line and then __cd__ into this folder.

For instance, for Microsoft Visual Studio 2022, the start menu entry is called __x64 Native Tools Command Prompt for VS 2022__.

Once in the MSVC command-prompt, use [cd](https://en.wikipedia.org/wiki/Cd_(command)) to change the current working directory to this folder. For example, if you got the Cunilog source code repo in __C:\MyProjects\Cunilog__, enter this command:

```
cd C:\MyProjects\Cunilog\examples\c
```

You should then see this prompt:
```
C:\MyProjects\Cunilog\examples\c>_
```

You may want to refer to the Microsoft documentation at 
[Use the Microsoft C++ Build Tools from the command line](https://learn.microsoft.com/en-us/cpp/build/building-on-the-command-line?view=msvc-170).

The examples can be built directly from the command-line:
```
cl /DUNICODE example.c ../../src/c/combined/cunilog_combined.c
```
Replace __example.c__ with the name of the example module you intend to build. For example, to build __ex000_SimpleSingleThreadedStatic.c__, use this command:
```
cl /DUNICODE ex000_SimpleSingleThreadedStatic.c ../../src/c/combined/cunilog_combined.c
```

__cl__ is the Microsoft compiler. The command-line argument __/DUNICODE__ builds the example as a Windows unicode application, which is required for Cunilog. See [Building Cunilog](../../docs/building.md) and [Cunilog and UTF-8](../../docs/utf8.md) for more details. 
The arguments/parameters __ex000_SimpleSingleThreadedStatic.c__ and __../../src/c/combined/cunilog_combined.c__ are the source code modules to build. The first one is the example's source code, and the second one is the combined Cunilog source code, sometimes also called amalgamation.

The examples themselves include Cunilog's header file with:
```C
#include "../../src/c/combined/cunilog_combined.h"
```
If you copied or moved the files from the repo to a different folder structure, you'll have to adjust these paths as well.

### On the command-line with batch scripts

Scripts are provided to simplify the build and clean process. Each example's source code file is accompanied by a Windows command-line batch script (.cmd) to build it. For example, to build __ex000_SimpleSingleThreadedStatic.c__,
run __ex000_SimpleSingleThreadedStatic_build.cmd__.

The script __BuildAll.cmd__ builds all C examples from a single script, and the script __CleanAll.cmd__ deletes all files generated during the build process, nameley the resulting object (.obj) and executable files (.exe).

### With the MSVC IDE

Create a new project/solution, then add the files __cunilog_combined.c__ and __cunilog_combined.h__ from the folder __src/c__. After that, add the example file in question to the project/solution.

For instance, to build the __ex000_SimpleSingleThreadedStatic__ example, add the file __ex000_SimpleSingleThreadedStatic.c__ from the __examples/c__ folder.
