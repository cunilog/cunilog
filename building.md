
# Building Cunilog

There's two options to build Cunilog. It can be built as part of your application or as a static or dynamically linked library. Dynamically linked libraries on Windows are called DLLs.

## Building Cunilog as part of your application

It is recommended that Cunilog is compiled and built together with your application. Since this is not always possible, static and shared libraries are alternatives.

To build the software as part of your application, you got two choices:

- Add the two combined source code files __cunilog_combined.h__ and
	__cunilog_combined.c__ in folder __src/c/combined__ to your project and compile them as 	part of it. This is the recommended option if you do not intend to change the code, neither for yourself nor to contribute to Cunilog. If your application is for Windows, another condition is that it is built with the Unicode character set. Cunilog can only be built with __Character Set__ set to __Use Unicode Character Set__. In Visual Studio, this can be found under __Project__, __Properties__, __Configuration Properties__, then __Advanced__. If your application needs to be built differently, include Cunilog as a static library.
	
- Do not add the two combined source code files to your project but add every
	single file that belongs to Cunilog instead. This is the preferred option
	if you either intend to contribute to Cunilog's development or intend to
	change the code for yourself only. It's a little bit more effort to add
	every single file at first but it makes life much easier when applying code
	changes. Updates might require files to be removed or added. The list with the files to add to your project can be found in the file __SingleFiles.txt__ in the __scripts__ directory. Alternatively you can follow these instructions:
  - Add all files from the folders __cunilog__, __datetime__, __dbg__, __extern__, __mem__, __pre__, and __string__.
  - Add all files from the folder __OS__ and its subfolders, which are __Apple__, __POSIX__, and __Windows__.
  - If you're on Windows, create the followoing preprocessor definitions: ___CRT_SECURE_NO_WARNINGS__, __HAVE_STRWILDCARDS__, __HAVE_SHELLAPI__, and __HAVE_USERENV__.

## Android

So far, Cunilog neither builds nor works on Android. Stay tuned.

## Linux

So far, Cunilog neither builds nor works on Linux. Stay tuned.

## Windows

### Building Cunilog as part of a Windows application

Apart from the correct character set there's nothing special to consider for Windows. Either include the combined source code files or add every single file to your project.

On Windows, Cunilog requires to be built with __Character Set__ set to __Use Unicode Character Set__. This means it can only be compiled as part of your application if your application is compiled with the same character set. Note that __Unicode Character Set__ on Windows means UTF-16, not UTF-8, which is fine because Cunilog converts all strings/texts to UTF-16 before it calls any Windows API, and it converts strings/texts coming back from Windows APIs to UTF-8 before returning them to the caller.
In Visual Studio, the character set an application is built with can be found under __Project__, __Properties__, __Configuration Properties__, then __Advanced__. If your application needs to be built differently, include Cunilog as a static library.

### Building Cunilog as a Windows static or dynamic (shared) library (DLL)

Open the MSVC solution __libcunilog.sln__ in folder __proj\msvc2019\libcunilog__ with MSVC 2019 and build it. There's currently only solution/project files for MSVC 2019.

In Visual Studio, go to __Build__, then __Batch Build...__*. Select the type of the static or shared (DLL) libraries you intend to use (see below) or press __Select All__, then __Rebuild__. You should get a completion message for the amount of project configurations you selected:
```
========== Rebuild All: 16 succeeded, 0 failed, 0 skipped ==========
```

Which version of the Cunilog library you should link your application to depends on the method your application is built with. See [/MD, /MT, /LD (Use Run-Time Library)](https://learn.microsoft.com/en-us/cpp/build/reference/md-mt-ld-use-run-time-library?view=msvc-170).

__Debug__ and __Release__ Cunilog static library versions build against the Windows C run-time (CRT) in dynamic link libraries. __Release__ is built with __/MD__ and __Debug__ with __/MDd__. Applications built this way require the [Microsoft Visual C++ Redistributable](https://learn.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist?view=msvc-170) to be deployed on target systems first in order to run.

The __DebugMT__ and __ReleaseMT__ configurations link to the CRT statically. __ReleaseMT__ is built with __/MT__ and __DebugMT__ with __/MTd__. Applications linked this way do not require the Microsoft Visual C++ Redistributable to be installed on target systems but since the Windows C run-time is statically linked as part of the application, the size of the executable file is often bigger.

Add __cunilog_combined.h__ in folder __src/c/combined__ to your project and include it in every module/unit Cunilog structures, enumerations, functions, or macros are accessed.

To automatically link to the correct version of libcunilog you can insert the following code in at least one of your header files, preferably the one that contains your logging code:
```C
/*
	Link to the correct version of libcunilog.

	See
	https://learn.microsoft.com/en-us/cpp/build/reference/md-mt-ld-use-run-time-library?view=msvc-170
	and
	https://learn.microsoft.com/en-us/cpp/preprocessor/comment-c-cpp?view=msvc-170 .

	The following code assumes that the project repository and the cunilog repository rest
	side-by-side in the same root folder and that the cunilog folder structure hasn't been
	changed from the default.
*/
#if defined (_MSC_VER) && defined (_WIN32)
	// Climbs all the way up to our project's root. The compiler/linker starts in our project
	//	folder, which is the folder that hosts the MSVC project file (.vcxproj).
	#ifndef LIBCUNILOG_BASEPATH
	#define LIBCUNILOG_BASEPATH "./../../../../"
	#endif
	// Climbs up one folder to above our project's root and then down to our cunilog solution.
	//	Assumes that cunilog is in a sister directory.
	#ifndef LIBCUNILOG_PROJPATH
	#define LIBCUNILOG_PROJPATH "../cunilog/proj/msvc2019/libcunilog/"
	#endif
	#if defined (_M_X64)
		// 64 bit
		#ifndef LIBCUNILOG_X64PATH
		#define LIBCUNILOG_X64PATH "x64/"
		#endif
		#ifndef LIBCUNILOG_PATH
		#define LIBCUNILOG_PATH LIBCUNILOG_BASEPATH LIBCUNILOG_PROJPATH LIBCUNILOG_X64PATH
		#endif
		#if defined (_MT) && defined (_DLL) && !defined (_DEBUG)
			// MD
			#pragma comment (lib, LIBCUNILOG_PATH "Release/libcunilog.lib")
		#elif defined (_MT) && defined (_DLL) && defined (_DEBUG)
			// MDd
			#pragma comment (lib, LIBCUNILOG_PATH "Debug/libcunilog.lib")
		#elif defined (_MT) && !defined (_DLL) && !defined (_DEBUG)
			// MT
			#pragma comment (lib, LIBCUNILOG_PATH "ReleaseMT/libcunilogMT.lib")
		#elif defined (_MT) && !defined (_DLL) && defined (_DEBUG)
			// MTd
			#pragma comment (lib, LIBCUNILOG_PATH "DebugMT/libcunilogMT.lib")
		#endif
	#else
		// 32 bit
		#ifndef LIBCUNILOG_X32PATH
		#define LIBCUNILOG_X32PATH ""
		#endif
		#ifndef LIBCUNILOG_PATH
		#define LIBCUNILOG_PATH LIBCUNILOG_BASEPATH LIBCUNILOG_PROJPATH LIBCUNILOG_X32PATH
		#endif
		#if defined (_MT) && defined (_DLL) && !defined (_DEBUG)
			// MD
			#pragma comment (lib, LIBCUNILOG_PATH "Release/libcunilog.lib")
		#elif defined (_MT) && defined (_DLL) && defined (_DEBUG)
			// MDd
			#pragma comment (lib, LIBCUNILOG_PATH "Debug/libcunilog.lib")
		#elif defined (_MT) && !defined (_DLL) && !defined (_DEBUG)
			// MT
			#pragma comment (lib, LIBCUNILOG_PATH "ReleaseMT/libcunilogMT.lib")
		#elif defined (_MT) && !defined (_DLL) && defined (_DEBUG)
			// MTd
			#pragma comment (lib, LIBCUNILOG_PATH "DebugMT/libcunilogMT.lib")
		#endif
	#endif
#endif
```

The macro __cunilogCheckVersion()__ can be used to check that the version definitions in the file __cunilog_combined.h__ are compatible with the ones of the built library:
```C
if (0 != cunilogCheckVersion ())
{
	puts ("Version of cunilog_combined.h and libcunilog different.");
	return EXIT_FAILURE;
}
```
