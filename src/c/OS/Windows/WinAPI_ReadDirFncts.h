/****************************************************************************************

	File		WinAPI_ReadDirFncts.h
	Why:		Functions to read directory contents
	OS:			Windows
	Created:	2022-01-15

History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2022-01-15	Thomas			Created.

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Copyright (c) 2024, 2025 Thomas

	Permission is hereby granted, free of charge, to any person obtaining a copy of this
	software and associated documentation files (the "Software"), to deal in the Software
	without restriction, including without limitation the rights to use, copy, modify,
	merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
	permit persons to whom the Software is furnished to do so, subject to the following
	conditions:

	The above copyright notice and this permission notice shall be included in all copies
	or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
	INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
	PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
	CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
	OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef WINAPI_READDIRFNCTS_H
#define WINAPI_READDIRFNCTS_H

#include <stdbool.h>
#include <stdint.h>

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./WinAPI_U8.h"

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
		#include "./membuf.h"
	#else
		#include "./../../pre/externC.h"
		#include "./../../mem/membuf.h"
	#endif

#endif

EXTERN_C_BEGIN

#ifdef _WIN32

#ifndef HAVE_STRWILDCARDS
	#error This module requires HAVE_STRWILDCARDS to be defined and strwildcards.c/h
#endif

#ifndef WIN_READDIR_FNCTS_DEFAULT_MEM_ALIGNMENT
#define WIN_READDIR_FNCTS_DEFAULT_MEM_ALIGNMENT			(8)
#endif
#ifndef WIN_READDIR_FNCTS_DEFAULT_STACKVAR_THRSHLD
#define WIN_READDIR_FNCTS_DEFAULT_STACKVAR_THRSHLD		(64)
#endif
#ifndef WIN_READDIR_FNCTS_DEFAULT_MASK_THRSHLD
#define WIN_READDIR_FNCTS_DEFAULT_MASK_THRSHLD			(64)
#endif

/*
	Parameter u of the function ReadDirectoryEntriesSDIRW_WU8 ().
*/
enum enrdirentssdirw
{
	EN_READ_DIR_ENTS_SDIRW_UTF8,
	EN_READ_DIR_ENTS_SDIRW_UTF16
};

/*
	One singly-linked list element. Note the WIN32_FIND_DATAW member, which is in
	Windows UTF-16.
*/
typedef struct sDirW
{
	struct sDirW		*_next;
	WIN32_FIND_DATAW	wfdW;
} SDIRW;

/*
	The plinth (base) of an SDIRW singly-linked list.
*/
typedef struct sDirWplinth
{
	uint64_t				nElements;						// Amount of elements in the list.
	SDIRW					*_first;						// Pointer to the first element of the
															//	singly-linked list.
	SDIRW					**_array;						// Array of sorted pointers.
	union
	{
		void				*strPathWorU8;					// UTF-8 or UTF-16;
		char				*chPathU8;						// UTF-8.
		unsigned char		*ucPathU8;						// Unsigned UTF-8.
		WCHAR				*wcPathU8;						// UTF-16.
	} UTF8orUTF16;
	enum enrdirentssdirw	u;
} SDIRWPLINTH;

/*
	SRDIRONEENTRYSTRUCT

	The structure passed on to the ignore callback function.
*/
typedef struct srdirOneEntryStruct
{
	union
	{
		// Unchanged path provided by the caller.
		const void			*strPathWorU8;					// UTF-8 or UTF-16;
		const char			*chPathU8;						// UTF-8.
		const unsigned char	*ucPathU8;						// Unsigned UTF-8.
		const WCHAR			*wcPathU8;						// UTF-16.
	} UTF8orUTF16;
	enum enrdirentssdirw	u;								// Which union member?
	//size_t					

	WIN32_FIND_DATAW		*pwfd;
	void					*pCustom;

	// The file mask/pattern as provided by the caller.
	const char				*szMaskU8;
	size_t					lnMaskU8;						// Its length.

	// The current folder plus search mask/pattern for FindFirstFileU8long ().
	SMEMBUF					mbSearchPathU8;					// "C:\\dir\*"
	size_t					lnSearchPathU8;
	size_t					lnOrgSeaPathU8;					// Original length.

	// The full path, starting with the path originally provided by the caller,
	//	and its length. This points to the first character in mbSearchPath.
	char					*szFullPathU8;
	size_t					lnFullPathU8;

	// Everything between szFullPathU8 and szFileNameU8, i.e, excluding the start
	//	of the path, which was originally provided by the caller. This is the path
	//	the pattern/mask is matched against.
	char					*szPathU8;
	size_t					lnPathU8;

	// The filename alone converted to UTF-8. Not all functions set these members.
	//	The function ForEachDirectoryEntryMaskU8 () sets both members.
	char					*szFileNameU8;
	size_t					lnFileNameU8;
} SRDIRONEENTRYSTRUCT;

/*
	Callback function for ReadDirectoryEntriesSDIRW_WU8 () that returns TRUE
	for directory entries to be ignored.
*/
typedef BOOL (*IgnoreCondCB)(SRDIRONEENTRYSTRUCT *);

/*
	Callback function for memory allocations within ReadDirectoryEntriesSDIRW_WU8 ().
	The parameter is the size of the memory block to allocate.
*/
typedef void *(*RDEMallocCB)(size_t);

/*
	ReadDirectoryEntriesSDIRW_WU8_ex

	Reads the contents of a directory/folder and returns the first element of a
	singly-linked list of SDIRW structures.

	If pdwEntries is not NULL the function returns the amount of entries found/
	enumerated at the location it points to. This is the amount of list entries
	returned.

	To deallocate the memory used by the singly-linked list, the returned pointer
	can be passed on to the ReleaseDirectoryEntriesSDIRW () function, which
	releases the list.

	The parameter strPathWorU8 can either be in Windows UTF-16 encoding or UTF-8.
	The parameter u distinguishes the character set of this parameter. Set u to
	EN_READ_DIR_ENTS_SDIRW_UTF16 for the function to expect strPathWorU8 to be
	in UTF-16. Set u to EN_READ_DIR_ENTS_SDIRW_UTF8 for the function to treat the
	path name in UTF-8.

	Note that the parameter strPathWorU8 names the path of the directory whose
	entries are to be enumerated and that this parameter can either be in UTF-8 or
	UTF-16, depending on the parameter u, but the returned SDIRW elements hold
	the filenames in the WIN32_FIND_DATAW structure wfdW, which is always in
	Windows UTF-16.

	strPathWorU8	The path whose directory entries are to be retrieved. Can be
					UTF-8 or Windows UTF-16, depending on the paramter u.

	u				Specifies the character set of the parameter strPathWorU8
					(read as "string Path W or U8").
					EN_READ_DIR_ENTS_SDIRW_UTF8		-> strPathWorU8 is in UTF-8
					EN_READ_DIR_ENTS_SDIRW_UTF16	-> strPathWorU8 is in UTF-16

	pdwEntries		Pointer to the amount of singly-linked list entries the
					function created. If this is parameter is NULL the amount is
					not returned.

	pIgnore			Callback function that returns TRUE for each entry to be
					ignored. Entries for which this function returns FALSE are
					added to the singly-linked list. If this parameter is NULL,
					the default callback function
					ReadDirectoryEntriesSDIRW_DefaultIgnoreCondition () will be
					called to determine whether an entry should be ignored or not.
					The default function ignores the entries ".", "..", and hidden
					and system files. See the definition of the function
					ReadDirectoryEntriesSDIRW_DefaultIgnoreCondition () in the code
					file for reference.

	pCustom			A custom pointer argument passed on to the callback function
					pIgnore as the member pCustom of the SRDIRONEENTRYSTRUCT structure
					that can be used for custom data by the caller. This can be NULL
					if it is not required.

	pMalloc			A custom memory allocation function. Basically a replacement
					for malloc () or ubf_malloc (). If this parameter is NULL
					ubf_malloc () is used for allocating list elements.

	The function returns NULL if the directory is empty or if there is not enough
	space on the heap to allocate memory for all directory entries.

	In case of a heap error, the function sets *pdwEntries to (DWORD) -1, provided
	that pwdEntries is not NULL. It is therefore recommended to provide the
	parameter pdwEntries to distinguish between an empty folder and a heap error.
	Alternatively GetLastError () returns ERROR_NOT_ENOUGH_MEMORY as an indicator.
	When not enough space is available on the heap, the function releases already
	created list elements first.

	The caller is responsible for calling ReleaseDirectoryEntriesSDIRW () on the
	returned singly-linked liste when the data is not required anymore.
*/
SDIRW *ReadDirectoryEntriesSDIRW_WU8_ex	(
						void					*strPathWorU8,
						enum enrdirentssdirw	u,
						DWORD					*pdwEntries,
						IgnoreCondCB			pIgnore,
						void					*pCustom,
						RDEMallocCB				pMalloc
										)
;

/*
	ReadDirectoryEntriesSDIRW_W
	ReadDirectoryEntriesSDIRW_U8

	These functions read the contents of a directory/folder and return the first
	element of a singly-linked list of SDIRW structures. They call
	ReadDirectoryEntriesSDIRW_WU8_ex () with the appropriate parameter for the
	character set of the path parameter. ReadDirectoryEntriesSDIRW_W () calls
	ReadDirectoryEntriesSDIRW_WU8_ex () with a parameter u of
	EN_READ_DIR_ENTS_SDIRW_UTF16 while ReadDirectoryEntriesSDIRW_U8 () calls it
	with a paramter u of EN_READ_DIR_ENTS_SDIRW_UTF8.

	Like ReadDirectoryEntriesSDIRW_WU8_ex (), if pdwEntries is not NULL the functions
	return the amount of entries found/enumerated at the location this parameter
	points to.

	To deallocate the memory used by the singly-linked list the returned pointer
	can be passed on to the ReleaseDirectoryEntriesSDIRW () function, which
	releases the list.

	Note that in case of the UTF-8 version of the function the parameter strPathU8
	uses the UTF-8 character set. This is in contrast to the returned SDIRW elements.
	The filenames in the WIN32_FIND_DATAW structure wfdW are in Windows UTF-16.
*/
SDIRW *ReadDirectoryEntriesSDIRW_W		(
						WCHAR					*wstrPath,
						DWORD					*pdwEntries,
						IgnoreCondCB			ig,
						void					*pCustom,
						RDEMallocCB				pMalloc
										)
;
SDIRW *ReadDirectoryEntriesSDIRW_U8		(
						char					*strPathU8,
						DWORD					*pdwEntries,
						IgnoreCondCB			ig,
						void					*pCustom,
						RDEMallocCB				pMalloc
										)
;

/*
	ReleaseDirectoryEntriesSDIRW

	Releases the singly-linked list swd points to from the heap. The function
	always returns NULL.

	Use ReleaseDirectoryEntriesSDIRW_cnt () instead to retrieve the amount of directory
	entries released.
*/
SDIRW *ReleaseDirectoryEntriesSDIRW (SDIRW *swd);

/*
	ReleaseDirectoryEntriesSDIRW_cntReleaseDirectoryEntriesSDIRW_cnt

	Releases the singly-linked list swd points to from the heap and returns the
	amount of list elements freed. Use the function ReleaseDirectoryEntriesSDIRW ()
	instead if the amount of list elements freed is not required.
*/
uint64_t ReleaseDirectoryEntriesSDIRW_cnt (SDIRW *swd);

/*
	The callback function for ForEachDirectoryEntryU8 ().

	The function ForEachDirectoryEntryU8 () stops when the callback function returns
	FALSE.
*/
/* Obsolete declaration.
typedef bool (*pForEachDirEntryU8) (SRDIRONEENTRYSTRUCT *psdE, void *pCustom);
*/
typedef bool (*pForEachDirEntryU8) (SRDIRONEENTRYSTRUCT *psdE);

/*
	ForEachDirectoryEntryU8_Ex
	ForEachDirectoryEntryU8

	Enumerates the UTF-8 directory strPathU8 points to and calls the callback
	function fedEnt for each found file or folder entry.

	The function ForEachDirectoryEntryU8_Ex () uses a re-usable SMEMBUF structure for its
	internal heap allocations while ForEachDirectoryEntryU8 () does not, which makes
	ForEachDirectoryEntryU8_Ex () slightly faster when a directory contains many subfolders.

	strPathU8			The path as a UTF-8 string. This parameter is passed on to
						the Windows API FindFirstFileW () as parameter lpFileName and can
						contain wildcard characters.

	fedEnt				Pointer to the callback function. The function is called
						for each found entry.

	pCustom				Pointer to custom data that is passed on to the callback
						function.

	*pnSubLevels		A pointer to an unsigned int variable that contains the
						amount of subfolder levels to enumerate. If this parameter
						is NULL or points to a value of 0, only the folder in strPathU8
						is processed. Any other number specifies the amount of
						subfolders to be enumerated by recursively calling this
						function. The function uses the variable to count its
						recursion levels. This means if it is not NULL and points
						to a value greater than 0, the function alters it for
						each subfolder level. Make sure the value is correct each
						time before the function is called.

	pmb                 Function ForEachDirectoryEntryU8_Ex () only: A pointer to an
                        initialised SMEMBUF structure the function uses as a buffer
						to store the path of the directory to process when it calls
						itself recursively (when pnSubLevels is neihter NULL nor points
						to a value of 0).
                        If there are many subfolders to process, this can reduce the
						amount of required heap allocations significantly. The caller is
						responsible for initialising the structure before the call and
						deallocating its resources again after the call.

	The function returns the amount of entries processed. Since the callback function
	is not called for the "." and ".." directory entries, these are not included in
	the return value.

	Since the function does not indicate when or if an error occurred, the caller is
	advised to check with a call to GetLastError () if the function succeeded. Do not check
	for ERROR_SUCCESS. The function buffers the system error returned either by FindFirstFileU8 ()
	or by the very last call to FindNextFileW () so that the caller does not see the system
	error code returned by FindClose (), which would be of no use.

	If no files can be found, the function is assumed to have succeeded when GetLastError ()
	returns ERROR_FILE_NOT_FOUND. In case at least one file or folder is found, the function
	is assumed to have succeeded when GetLastError () returns a value of ERROR_NO_MORE_FILES.
	Hence, expect ERROR_FILE_NOT_FOUND when the function's return value is 0, and
	ERROR_NO_MORE_FILES for return values greater than 0.

	See
	https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findfirstfilew and
	https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findnextfilew for
	more information.

	The function can return early if the callback function fedEnt returns false. In this case
	the error retrieved by GetLastError () is whatever the callback function set it to. For
	instance, the callback function could call SetLastError (ERROR_OPERATION_ABORTED) before
	it returns false and SetLastError (ERROR_SUCCESS) before it returns true. Upon return of
	ForEachDirectoryEntryU8 (), the caller could then check GetLastError () for
	ERROR_OPERATION_ABORTED, which means the callback function returned false, for
	ERROR_FILE_NOT_FOUND, which would indicate that no files were found, and for
	ERROR_NO_MORE_FILES, indicating success.
*/
#ifdef HAVE_MEMBUF
size_t ForEachDirectoryEntryU8_Ex	(
				const char				*strPathU8,
				pForEachDirEntryU8		fedEnt,
				void					*pCustom,
				size_t					*pnSubLevels,
				SMEMBUF                 *pmb
									)
;
#endif
size_t	ForEachDirectoryEntryU8		(
				const char				*strPathU8,
				pForEachDirEntryU8		fedEnt,
				void					*pCustom,
				size_t					*pnSubLevels
									)
;

/*
	ForEachDirectoryEntryMaskU8

	Does not work! Do not use!

	This function exists to provide better compatibilibty between Windows and POSIX.
	Folder and file mask are split into two parameters.

	strFolderU8			The folder for which the function is to retrieve the directory
						listing. The folder name may end with a forward or backslash.
						This must be an absolute path. The folder cannot be relative, i.e.
						cannot contain path navigators ("..\") unless they can be resolved
						entirely, i.e it is someting like "/dir/dir/../file", which would
						resolve to "/dir/file".

	lenFolderU8			The length of strFolderU8, excluding a terminating NUL character.
						This parameter can be USE_STRLEN, which causes the function to invoke
						strlen () on strFolderU8 to obtain its length. If the length is
						provided instead of USE_STRLEN, the string does not have to be
						NUL-terminated.

	strMaskU8			The ask for the files or folders to call the callback
						function. It can contain wildcard characters to match the files for
						whom the callback function will be called.
						This parameter can be NULL, in which case the function calls the
						callback function on every single file found.
						This is not a simple "*" or "*.*" file mask as known from
						Windows or POSIX. See remarks below the parameter descriptions.

	lenMaskU8			The length of strFileMask, excluding a terminating NUL character.
						This parameter can be USE_STRLEN, which causes the function to invoke
						strlen () on strFileMask to obtain its length.
						The parameter is ignored if strFileMaskU8 is NULL.

	fedEntCB			Pointer to the callback function. The function is called
						for each found entry.

	pCustom				Pointer to custom data that is passed on to the callback
						function.

	*pnSubLevels		A pointer to an unsigned int variable that contains the
						amount of subfolder levels to enumerate. If this parameter
						is NULL or points to a value of 0, only the folder in strPathU8
						is processed. Any other number specifies the amount of
						subfolder levels to be enumerated by recursively calling this
						function. The function uses the variable to count its
						recursion levels. This means if it is not NULL and points
						to a value greater than 0, the function alters it for
						each subfolder level. Make sure the value is correct each
						time before the function is called.

	The function reads a base directory, which is strFolderU8. It ignores the "." and ".."
	folders returned by the file system but matches any other file or directory
	against strFileMaskU8. Matching starts with file or directory objects inside the folder
	strFolderU8, which is different from how operating systems and system utilities usually
	match wildcards and files or directories.

	If pnSubLevels is NULL or points to a value of 0, only files and folders (file objects)
	in strFolderU8 are matched, meaning known patterns like "???.txt" or "*" or "*.bmp"
	work as usual. However, since matching starts with file objects in strFolderU8,
	matching is different when pnSubLevels allows the function to climb further down a
	directory tree.

	<strFolderU8>/<objects in strFolderU8>/<more objects>
	.             ^
	.             !
	.             +-------- Matching against strFileMaskU8 starts here.

	If strFolderU8 is "/home/user", and the function should return text files in
	"/home/user/Downloads", strFileMaskU8 needs to be "Downloads/*.txt".
	If the function should return text files in any folder inside or below "/home/usr",
	strFileMaskU8 needs to be "**.txt".

	See description of the functions matchWildcardPattern () and/or matchWildcardPatternW ()
	in strwildcards.h on how patterns are created and matched.
*/
size_t ForEachDirectoryEntryMaskU8	(
				const char				*strFolderU8,
				size_t					lenFolderU8,
				const char				*strMaskU8,
				size_t					lenMaskU8,
				pForEachDirEntryU8		fedEntCB,
				void					*pCustom,
				size_t					*pnSubLevels
									)
;

EXTERN_C_END

#ifndef CUNILOG_BUILD_READDIR_TESTFNCT
//#define CUNILOG_BUILD_READDIR_TESTFNCT
#endif

/*
	Tests.
*/
#ifdef CUNILOG_BUILD_READDIR_TESTFNCT
	bool ForEachDirectoryEntryMaskU8TestFnct (void);
#else
	#define ForEachDirectoryEntryMaskU8TestFnct()	(true)
#endif

#endif														// Of #ifdef _WIN32.

#endif														// Of #ifndef WINAPI_READDIRFNCTS_H.
