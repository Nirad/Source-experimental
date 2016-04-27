/**
* @file CSFileList.cpp
*/

#include <time.h>
#if defined(_WIN32)
	#include <io.h> 		// findfirst
	#include "../../sphere/threads.h"
#else	// LINUX
	#include <sys/stat.h>
	#include <dirent.h>
#endif
#include "CSFileList.h"
#include "../../common/CLog.h"
#include "../../sphere/threads.h"
#include "../common.h"

// Similar to the MFC CFileFind
bool CSFileList::ReadFileInfo( lpctstr pszFilePath, time_t & dwDateChange, dword & dwSize ) // static
{
	ADDTOCALLSTACK("CSFileList::ReadFileInfo");
#ifdef _WIN32
	// WIN32
	struct _finddata_t fileinfo;
	fileinfo.attrib = _A_NORMAL;
	intptr_t lFind = _findfirst( pszFilePath, &fileinfo );

	if ( lFind == -1 )
#else
	// LINUX
	struct stat fileStat;
	if ( stat( pszFilePath, &fileStat) == -1 )
#endif
	{
		DEBUG_ERR(( "Can't open input dir [%s]\n", pszFilePath ));
		return false;
	}

#ifdef _WIN32
	// WIN32
	dwDateChange = fileinfo.time_write;
	dwSize = fileinfo.size;
	_findclose( lFind );
#else
	// LINUX
	dwDateChange = fileStat.st_mtime;
	dwSize = fileStat.st_size;
#endif

	return true;
}

int CSFileList::ReadDir( lpctstr pszFileDir, bool bShowError )
{
	ADDTOCALLSTACK("CSFileList::ReadDir");
	// NOTE: It seems NOT to like the trailing \ alone
	tchar szFileDir[_MAX_PATH];
	size_t len = strcpylen(szFileDir, pszFileDir);
#ifdef _WIN32
	if ( len > 0 )
	{
		len--;
		if ( szFileDir[len] == '\\' || szFileDir[len] == '/' )
			strcat( szFileDir, "*.*" );
	}
#endif

#ifdef _WIN32
	struct _finddata_t fileinfo;
	intptr_t lFind = _findfirst(szFileDir, &fileinfo);

	if ( lFind == -1 )
#else
	char szFilename[_MAX_PATH];
	// Need to strip out the *.scp part
	for ( size_t i = len; i > 0; i-- )
	{
		if ( szFileDir[i] == '/' )
		{
			szFileDir[i+1] = 0x00;
			break;
		}
	}
	
	DIR* dirp = opendir(szFileDir);
	struct dirent * fileinfo = NULL;

	if ( !dirp )
#endif
	{
		if (bShowError == true)
		{
			DEBUG_ERR(("Unable to open directory %s\n", szFileDir));
		}
		return -1;
	}

	do
	{
#if defined(_WIN32)
		if ( fileinfo.name[0] == '.' )
			continue;
		AddHead(fileinfo.name);
#else
		fileinfo = readdir(dirp);
		if ( !fileinfo )
			break;
		if ( fileinfo->d_name[0] == '.' )
			continue;

		sprintf(szFilename, "%s%s", szFileDir, fileinfo->d_name);
		len = strlen(szFilename);
		if ( len > 4 && !strcmpi(&szFilename[len - 4], SPHERE_SCRIPT) )
			AddHead(fileinfo->d_name);
#endif
	}
#if defined(_WIN32)
	while ( !_findnext(lFind, &fileinfo));

	_findclose(lFind);
#else
	while ( fileinfo != NULL );

	closedir(dirp);
#endif
	return (int)(GetCount());
}

