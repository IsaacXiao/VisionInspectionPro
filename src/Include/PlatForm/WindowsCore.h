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
#include <regex>

typedef HINSTANCE DLL_HANDLE;
#define FILE_NAME_MAX_LENGTH 256;
typedef HMODULE   MODULE_HANDLE;

#pragma warning(disable : 4996)


#include "CommonInclude/InspectException.h"
#include "CommonInclude/utility.hpp"

namespace
{
	std::basic_string<WCHAR> GetModuleDirectoryW()
	{
		WCHAR slash[2] = { '\\' };
		WCHAR cache[512];
		::GetModuleFileNameW(NULL, cache, 512);
		std::basic_string<WCHAR> dir(cache);
		dir = dir.substr(0, dir.find_last_of(slash));
		return dir;
	}
	
	void BrowseFiles(const STRING& ext, vector<STRING>& full_paths)
	{
		struct __finddata64_t	file;
		long long				handle;
		const int			MAX_PATH_SIZE = 256;
		char				path[MAX_PATH_SIZE];
	
		handle = (long long)_findfirst64("*", &file);
		if (handle == -1)
			return;
		do
		{
			if (file.attrib & _A_SUBDIR) //is dir
			{
				if (file.name[0] != '.') // dir name is '.' or  '..'
				{
					_chdir(file.name); //enter path				
					BrowseFiles(ext, full_paths);//go on
					_chdir(".."); //return prev dir
				}
			}
			else
			{
				if (!ext.empty())
				{
					//if( NULL == strstr( file.name , ext.c_str() ) )
					STRING&& reg_match = "^[a-zA-Z0-9_-]+\\" + ext + "$";
					if (!RegCheck(file.name, std::regex(reg_match)))
						continue;
				}
				_getcwd(path, MAX_PATH_SIZE);
				strcat(path, "\\");
				strcat(path, file.name);
				full_paths.push_back(path);
			}
		} while (!_findnext64(handle, &file));
		_findclose(handle);
	}
	
	void BrowseFiles(const STRING& dir, const STRING& ext, vector<STRING>& full_paths)
	{
		auto res = _chdir(dir.c_str());
		BrowseFiles(ext, full_paths);
		_chdir("..");
		if (0 == full_paths.size())
		{
			throw FilePathException("Module Path does not exist!");
		}
	}
	
	void BrowseSubDir(vector<STRING>& dir_names, bool is_full_path)
	{
		struct _finddata_t	file;
		long				handle = -1;
		const int			MAX_PATH_SIZE = 256;
		char				path[MAX_PATH_SIZE];
	
		handle = (long)_findfirst("*", &file);
		if (handle == -1)
			return;
		do
		{
			if (file.attrib & _A_SUBDIR) //is dir
			{
				if (file.name[0] != '.') // dir name is '.' or  '..'
				{
					if (is_full_path)
					{
						_getcwd(path, MAX_PATH_SIZE);
						strcat(path, "\\");
						strcat(path, file.name);
						dir_names.push_back(path);
					}
					else
					{
						dir_names.push_back(file.name);
					}
				}
			}
		} while (!_findnext(handle, &file));
		_findclose(handle);
	}
	
	void BrowseSubDirs(const STRING& dir, vector<STRING>& dir_names, bool is_full_path)
	{
		_chdir(dir.c_str());
		BrowseSubDir(dir_names, is_full_path);
		_chdir("..");
	}
	
	time_t IntToCTime(int year, int month, int day, int hour, int mi, int ss)
	{
		tm tmTmp;
		ZeroMemory(&tmTmp, sizeof(tm));
		tmTmp.tm_year = year;
		tmTmp.tm_year = (tmTmp.tm_year - 1970) + 70;
		tmTmp.tm_mon = month - 1;
		tmTmp.tm_mday = day;
		tmTmp.tm_hour = hour;
		tmTmp.tm_min = mi;
		tmTmp.tm_sec = ss;
		return mktime(&tmTmp);
	}
	
	
	int GetFileLen(STRING file_name)
	{
		FILE* fp;
		if ((fp = fopen(file_name.c_str(), "r")) == NULL)
		{
			//fclose(fp);
			return 0;
		}
		int length = filelength(fileno(fp));
		fclose(fp);
		return length;
	}
	
	bool FileReadOnly(STRING file_name, void* data, int& data_len, bool is_binary = false )
	{
		//打开文件
		STRING file_mode;
		if (is_binary)
			file_mode = "rb";
		else
			file_mode = "rt";
		FILE* hFile = fopen(file_name.c_str(), file_mode.c_str());
		if (hFile == NULL)
		{
			return false;
		}
		int read_size = 0;//实际读入的字符数
		//循环读取文件字节数
		while (read_size < data_len)
		{
			int curr_read_size = 0;//当前循环写入的字节数
			curr_read_size = fread((char*)data + read_size, sizeof(unsigned char), data_len - read_size, hFile);
			if (curr_read_size == 0)
				break;
			read_size += curr_read_size;
		}
		data_len = read_size;
		fclose(hFile);
		return true;
	}
	
	
	bool FileWriteOnly(STRING file_name, void* data, int data_len, bool is_binary = false)
	{
		//打开文件
		STRING file_mode;
		if (is_binary)
			file_mode = "wb";
		else
			file_mode = "wt";
		FILE* hFile = fopen(file_name.c_str(), file_mode.c_str());
		if (hFile == NULL)
		{
			return false;
		}
		int write_size = 0;//实际读入的字符数
		//循环读取文件字节数
		while (write_size < data_len)
		{
			int curr_write_size = 0;//当前循环写入的字节数
			curr_write_size = fwrite((char*)data + write_size, sizeof(unsigned char), data_len - write_size, hFile);
			if (curr_write_size == 0)
				break;
			write_size += curr_write_size;
		}
		fclose(hFile);
		return true;
	}
	
	time_t StrToTime( char * szTime,STRING time_format = "%4d-%2d-%2d %2d:%2d:%2d")
	{
		struct tm tm1;
		time_t t;
		memset(&tm1, 0, sizeof(tm));		//给tm结构赋初值，防止传入字符串不合法报错
		sscanf(szTime, time_format.c_str(),
			&tm1.tm_year,
			&tm1.tm_mon,
			&tm1.tm_mday,
			&tm1.tm_hour,
			&tm1.tm_min,
			&tm1.tm_sec);
		tm1.tm_year -= 1900;
		tm1.tm_mon--;
		tm1.tm_isdst = -1;
		t = mktime(&tm1);
		return t;
	}
	
	bool SetSysTime( time_t t )
	{
		struct tm* tmp = localtime(&t);
		SYSTEMTIME systm;
		systm.wYear = tmp->tm_year + 1900;
		systm.wMonth = tmp->tm_mon + 1;
		systm.wDay = tmp->tm_mday;
		systm.wHour = tmp->tm_hour;
		systm.wMinute = tmp->tm_min;
		systm.wSecond = tmp->tm_sec;
		systm.wMilliseconds = 0;
		return SetLocalTime(&systm);
	}
	
	/*[[gnu::always_inline]]*/ inline bool IsDirExist(STRING szDirectory)
	{
		DWORD dwAttr=GetFileAttributesA(szDirectory.c_str());
		if(0xFFFFFFFF==dwAttr)
			return false;
		return (FILE_ATTRIBUTE_DIRECTORY&dwAttr)!=0;
	}
	
	auto CreateDir( const STRING& path )
	{
		Sleep( 100 );
		return CreateDirectoryA( path.c_str(), NULL );
	}
	
	
	auto GetModuleDirectory()
	{
		CHAR cache[256];
		::GetModuleFileNameA( NULL, cache, 256 );
		STRING dir( cache );
		return dir.substr( 0, dir.find_last_of( "\\" ) );
	}
	void Time2Str( time_t t, STRING& str_time, STRING time_format = "%Y-%m-%d %H:%M:%S" )
	{
		static const int N = 80;
		if( t < 0 ) t = 0;
		struct tm* tmp = localtime( &t );
		char buffer [N];
		strftime( buffer, N, time_format.c_str(), tmp );
		str_time.assign( buffer );
	}
	
	auto RemoveDir( const STRING& path )
	{
		Sleep( 100 );
		int result = RemoveDirectoryA( path.c_str() );	
		return result;
	}
	
	auto RemoveFile( const STRING& path )
	{
		Sleep( 100 );
		return DeleteFileA( path.c_str() );
	}
	
	DLL_HANDLE LoadDll( const STRING& file_name )
	{
		return LoadLibraryA( file_name.c_str() );
		//return LoadLibraryW(file_name.c_str());
	}
	
	void FreeDll( DLL_HANDLE handle )
	{
		FreeLibrary( handle );
	}
	
	void* GetFuncAddress( DLL_HANDLE handle, const STRING& func_name )
	{
		return (void*)GetProcAddress( handle, func_name.c_str() );
	}
	
	bool IsValid( DLL_HANDLE handle )
	{
		return handle != NULL;
	}
	
	STRING PathSeparator()
	{
		return "\\";
	}
	
	STRING DllExt()
	{
		return "dll";
	}
	
	long TimeInt32()
	{
		static time_t cur_time;
		time( &cur_time );
		return (long)cur_time;
	}
	
	void FileTimeToTime_t(  FILETIME  ft,  time_t  *t  )  
	{   
	   ULARGE_INTEGER            ui;  
	   ui.LowPart            =  ft.dwLowDateTime;  
	   ui.HighPart            =  ft.dwHighDateTime;  
	   //LONGLONG ll            =  ft.dwHighDateTime  <<  ( 32 + ft.dwLowDateTime );  
	   *t            =  ((LONGLONG)(ui.QuadPart  -  116444736000000000)  /  10000000);  
	}
	
	bool FileExist( const STRING& file_path )
	{
		_WIN32_FIND_DATAA find_file_data;
		memset( &find_file_data, 0, sizeof( find_file_data ) );	
		return INVALID_HANDLE_VALUE != FindFirstFileA( file_path.c_str(), &find_file_data );
	}
	
	auto FileCopy( const STRING& desc_file_path, const STRING& res_file_name )
	{
		return CopyFileA( desc_file_path.c_str(), res_file_name.c_str(), true );
	}
	
	template<typename T>
	inline void RelpaceVector( const vector<T>& source, vector<T>& desc )
	{
		desc.resize( source.size() );                            
		memcpy( &desc[0], &source[0], sizeof(T) * source.size() );
	}
	
	void MemoryZero( void* p, int length )
	{	
		memset( p, 0, length );
	}
	
	void ThreadSleep(int ms)
	{
		Sleep(ms);
	}
	
	std::string ErrMsg()
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
}

#endif