# Cunilog versioning

Cunilog's version scheme mostly follows the scheme for MS Windows applications.
A Cunilog version consists of:
 - A major version
 - A minor version
 - A subversion
 - A build number
 - A version year
 
```C
// Version numbers.
#define CUNILOG_VERSION_MAJOR	0							// Major version.
#define CUNILOG_VERSION_MINOR	8							// Minor version.
#define CUNILOG_VERSION_SUB		0							// Subversion for maintenance.
#define CUNILOG_VERSION_BUILD	1							// Build number.
#define CUNILOG_VERSION_YEAR	"2026"						// Version year.
```

Since Cunilog currently is still considered alpha software, the version stays below 0.9.0.0. Version 0.9.0.0 and above are going to be beta versions, with the first official release being 1.0.0.0. The year plays no role in the actual versioning.

Cunilog at the moment is not considered alpha because it is buggy or instable but rather because its interface is still subject to major changes.

## Version check

Primarily meant for when Cunilog is linked statically or dynamically to an application, a function/macro exists to check that the library and the used header file belong to the same version. The function's name is currently ***cunilogCheckVersionIntChk ()***. Call it with CUNILOG_VERSION_HDR as its parameter, like ***cunilogCheckVersionIntChk (CUNILOG_VERSION_HDR)***. The macro ***cunilogCheckVersion()*** is an alias for this invokation.

The function returns -1, 0, or 1.
```C
-1		The version of cunilog.c is less than the one in cunilogversion.h.
 0		The version of cunilog.c is identical to the one in cunilogversion.h.
 1		The version of cunilog.c is greater than the one in cunilogversion.h.
```

