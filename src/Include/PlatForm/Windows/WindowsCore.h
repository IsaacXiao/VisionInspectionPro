#ifndef WINDOWS_PLATFORM_HEAD_H
#define WINDOWS_PLATFORM_HEAD_H

#include <string>
#include <vector>
using namespace std;
typedef std::string STRING;
#include <windows.h>
#include <direct.h>
#include <stdio.h>
#include <io.h> 
#include <time.h>


#include <fstream>
#include <assert.h>


typedef HINSTANCE DLL_HANDLE;
#define FILE_NAME_MAX_LENGTH 256;
typedef HMODULE   MODULE_HANDLE;

#pragma warning(disable : 4996)


#include "CommonInclude/InspectException.h"

void BrowseFiles( const STRING& ext, vector<STRING>& full_paths );
void BrowseFiles( const STRING& dir, const STRING& ext, vector<STRING>& full_paths );

void BrowseSubDir( vector<STRING>& dir_names, bool is_full_path );
void BrowseSubDirs( const STRING& dir, vector<STRING>& dir_names, bool is_full_path );

time_t IntToCTime( int year, int month, int day, int hour, int mi, int ss );
int  GetFileLen(STRING file_name);
bool FileReadOnly(STRING file_name, void* data, int& data_len, bool is_binary = false );
bool FileWriteOnly(STRING file_name, void* data, int data_len, bool is_binary = false);
time_t StrToTime( char * szTime,STRING time_format = "%4d-%2d-%2d %2d:%2d:%2d");

bool SetSysTime( time_t t );

/*[[gnu::always_inline]]*/ inline bool IsDirExist(STRING szDirectory)
{
	DWORD dwAttr=GetFileAttributesA(szDirectory.c_str());
	if(0xFFFFFFFF==dwAttr)
		return false;
	return (FILE_ATTRIBUTE_DIRECTORY&dwAttr)!=0;
}

inline auto CreateDir( const STRING& path )
{
	Sleep( 100 );
	return CreateDirectoryA( path.c_str(), NULL );
}

//任何Dll都需要使用全局的日志
//全局的日志Record依赖Configure，需要用到下面2个函数
//所以Dll编译单元必须能看到这2个函数的定义
//不做成inline写到cpp里搞起来麻烦得多
inline auto GetModuleDirectory()
{
	CHAR cache[256];
	::GetModuleFileNameA( NULL, cache, 256 );
	STRING dir( cache );
	return dir.substr( 0, dir.find_last_of( "\\" ) );
}
inline void Time2Str( time_t t, STRING& str_time, STRING time_format = "%Y-%m-%d %H:%M:%S" )
{
	static const int N = 80;
	if( t < 0 ) t = 0;
	struct tm* tmp = localtime( &t );
	char buffer [N];
	strftime( buffer, N, time_format.c_str(), tmp );
	str_time.assign( buffer );
}

std::basic_string<WCHAR> GetModuleDirectoryW();

inline auto RemoveDir( const STRING& path )
{
	Sleep( 100 );
	int result = RemoveDirectoryA( path.c_str() );	
	return result;
}

inline auto RemoveFile( const STRING& path )
{
	Sleep( 100 );
	return DeleteFileA( path.c_str() );
}

inline DLL_HANDLE LoadDll( const STRING& file_name )
{
	return LoadLibraryA( file_name.c_str() );
	//return LoadLibraryW(file_name.c_str());
}

inline void FreeDll( DLL_HANDLE handle )
{
	FreeLibrary( handle );
}

inline void* GetFuncAddress( DLL_HANDLE handle, const STRING& func_name )
{
	return (void*)GetProcAddress( handle, func_name.c_str() );
}

inline bool IsValid( DLL_HANDLE handle )
{
	return handle != NULL;
}

inline STRING PathSeparator()
{
	return "\\";
}

inline STRING DllExt()
{
	return "dll";
}

inline long TimeInt32()
{
	static time_t cur_time;
	time( &cur_time );
	return (long)cur_time;
}

inline void FileTimeToTime_t(  FILETIME  ft,  time_t  *t  )  
{   
   ULARGE_INTEGER            ui;  
   ui.LowPart            =  ft.dwLowDateTime;  
   ui.HighPart            =  ft.dwHighDateTime;  
   //LONGLONG ll            =  ft.dwHighDateTime  <<  ( 32 + ft.dwLowDateTime );  
   *t            =  ((LONGLONG)(ui.QuadPart  -  116444736000000000)  /  10000000);  
}

inline bool FileExist( const STRING& file_path )
{
	_WIN32_FIND_DATAA find_file_data;
	memset( &find_file_data, 0, sizeof( find_file_data ) );	
	return INVALID_HANDLE_VALUE != FindFirstFileA( file_path.c_str(), &find_file_data );
}

inline auto FileCopy( const STRING& desc_file_path, const STRING& res_file_name )
{
	return CopyFileA( desc_file_path.c_str(), res_file_name.c_str(), true );
}

template<typename T>
inline void RelpaceVector( const vector<T>& source, vector<T>& desc )
{
	desc.resize( source.size() );                            
	memcpy( &desc[0], &source[0], sizeof(T) * source.size() );
}

inline void MemoryZero( void* p, int length )
{	
	memset( p, 0, length );
}

inline void ThreadSleep( int ms )
{
	Sleep( ms );
}

/*[[gnu::always_inline]]*/ inline std::string ErrMsg()
{
	 char lpMsgBuf[100];
	FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        GetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (lpMsgBuf),
        0, NULL );
	return std::string(lpMsgBuf);
}


struct DllManager
{
	DllManager( const STRING& file_name ) : file_name_( file_name )
	{
		handle_ = LoadDll( file_name );
		if ( NULL == handle_ )
		{
			throw DllException(ErrMsg());
		}
	}

	bool IsValid(){
		return ::IsValid( handle_ );
	}

	void* GetFunc( const STRING& func_name )
	{
		auto pFn = GetFuncAddress( handle_, func_name );
		if ( nullptr == pFn )
		{
			throw DllException(ErrMsg());
		}
		else
		{
			return pFn;
		}
	}

	const STRING& FileName() const{
		return file_name_;
	}

	~DllManager()
	{
		assert(IsValid());
		FreeDll( handle_ );
	}

private:
	DLL_HANDLE	handle_;
	STRING		file_name_;
};

#endif