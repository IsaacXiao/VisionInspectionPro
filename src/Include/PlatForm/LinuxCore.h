#ifndef LINUX_PLATFORM_HEAD_H
#define LINUX_PLATFORM_HEAD_H

#include <string>
#include <vector>
using namespace std;
typedef std::string STRING;
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <fstream>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
//#include <dlfcn.h>

//#include "utility/Convertor.hpp"
//#include "codeconverter.h"
//
typedef void* DLL_HANDLE;
//#define FILE_NAME_MAX_LENGTH 256;
//typedef HMODULE   MODULE_HANDLE;

#include "CommonInclude/InspectException.h"

namespace
{
	void BrowseFiles( const STRING& dir, const STRING& ext, vector<STRING>& full_paths ) //throw(FilePathException)
	{
		typedef STRING::value_type CharT;
	
		//if( ext.empty() )
		//	return;
		DIR *pDir = opendir( dir.c_str() );
		if( pDir == NULL )
			return;
	
		chdir( dir.c_str() );
		const int			MAX_PATH_SIZE = 256;
		char				path[MAX_PATH_SIZE];
	
		struct dirent* 	ent = NULL;
		struct stat 	statbuf;
		while ( NULL != ( ent = readdir( pDir ) ) )
		{
			lstat( ent->d_name, &statbuf );
			if( S_ISDIR( statbuf.st_mode ) ){
				if( strcmp( ".", ent->d_name ) == 0 || strcmp( "..", ent->d_name ) == 0 )
					continue;
				BrowseFiles( ent->d_name, ext, full_paths );
			}
			else{
				CharT * find_str = NULL;
				///none ext name
				if( !ext.empty() ){
					if( NULL == ( find_str = strstr( ent->d_name , ext.c_str() ) ) )
						continue;
					if( strlen( find_str ) != ext.size() )
						continue;
				}
	
				getcwd( path, MAX_PATH_SIZE );
				strcat( path, "/");
				strcat( path, ent->d_name );
				full_paths.push_back( path );
			}
		}
		chdir( ".." );
		closedir( pDir );
	
		if ( 0 == full_paths.size() )
		{
			throw FilePathException("Module Path does not exist!");
		}
	}
	
	void BrowseSubDirs( const STRING& dir, vector<STRING>& dir_names, bool is_full_path ){
		typedef STRING::value_type CharT;
	
		DIR *pDir = opendir( dir.c_str() );
		if( pDir == NULL )
			return;
	
		chdir( dir.c_str() );
		const int			MAX_PATH_SIZE = 256;
		char				path[MAX_PATH_SIZE];
	
		struct dirent* 	ent = NULL;
		struct stat 	statbuf;
		while ( NULL != ( ent = readdir( pDir ) ) )
		{
			lstat( ent->d_name, &statbuf );
			if( S_ISDIR( statbuf.st_mode ) ){
				if( strcmp( ".", ent->d_name ) == 0 || strcmp( "..", ent->d_name ) == 0 )
					continue;
				if( is_full_path ){
					getcwd( path, MAX_PATH_SIZE );
					strcat( path, "/");
					strcat( path, ent->d_name );
					dir_names.push_back( path );
				}
				else
					dir_names.push_back( ent->d_name );
			}
		}
		chdir( ".." );
		closedir( pDir );
	}
	//
	bool CreateDir( const STRING& path ){
		//mode_t   mode = 0755
		return 0 == mkdir( path.c_str(), 0755 );
	}
	
	bool RemoveDir( const STRING& path ){
		return 0 == remove( path.c_str() );
	}
	
	bool RemoveFile( const STRING& path ){
		return 0 == remove( path.c_str() );
	}
	
	DLL_HANDLE LoadDll( const STRING& file_name ){
	//#ifdef ARM_LINUX
		//return dlopen( file_name.c_str(), /*RTLD_LAZY/*RTLD_NOW*/RTLD_LAZY|RTLD_GLOBAL|RTLD_DEEPBIND ); //tiny6410
	//	return dlopen( file_name.c_str(), /*RTLD_LAZY/*RTLD_NOW*/RTLD_LAZY|RTLD_GLOBAL );//mini2440
	//#else
		return dlopen( file_name.c_str(), /*RTLD_LAZY/*RTLD_NOW*/RTLD_LAZY );
	//#endif
	}
	
	void FreeDll( DLL_HANDLE handle ){
		dlclose( handle );
	}
	
	void* GetFuncAddress( DLL_HANDLE handle, const STRING& func_name ){
		return dlsym( handle, func_name.c_str() );
	}
	
	bool IsValid( DLL_HANDLE handle ){
		return handle != NULL;
	}
	
	STRING PathSeparator(){
		return "/";
	}
	
	STRING DllExt(){
		return "so";
	}
	
	struct DllManager
	{
		DllManager( const STRING& file_name ) : file_name_( file_name ){
				handle_ = LoadDll( file_name );
			}
	
			bool IsValid(){
				return ::IsValid( handle_ );
			}
	
			void* GetFunc( const STRING& func_name ){
				return GetFuncAddress( handle_, func_name );
			}
	
			const STRING& FileName() const{
				return file_name_;
			}
	
			~DllManager(){
				FreeDll( handle_ );
			}
	
		private:
			DLL_HANDLE	handle_;
			STRING		file_name_;
	};
	
	long TimeInt32(){
		static time_t cur_time;
		time( &cur_time );
		return (long)cur_time;
	}
	
	STRING GetModuleDirectory(){
		static int const MAXBUFSIZE = 1024;
		char buf[ MAXBUFSIZE ];
		int count = readlink( "/proc/self/exe", buf, MAXBUFSIZE );
		if ( count < 0 || count >= MAXBUFSIZE ){
			return "";
		}
		buf[ count ] = '\0';
		STRING path( buf );
		path = path.substr( 0, path.find_last_of( "/" ) );
		return path;
	}
	
	///
	/// wait modify!
	///
	STRING GetModuleDirectoryW(){
		return GetModuleDirectory();
	}
	
	void Time2Str( time_t t, STRING& str_time, STRING time_format = "%Y-%m-%d %H:%M:%S" ){
		static const int N = 80;
		struct tm* tmp = localtime( &t );
		char buffer [N];
		strftime( buffer, N, time_format.c_str(), tmp );
		str_time.assign( buffer );
	}
	
	time_t IntToCTime( int year, int month, int day, int hour, int mi, int ss ){
		tm tmTmp;
		memset( &tmTmp, 0, sizeof(tm) );
		tmTmp.tm_year = year;
		tmTmp.tm_year = (tmTmp.tm_year - 1970 ) + 70;
		tmTmp.tm_mon  = month - 1;
		tmTmp.tm_mday = day;
		tmTmp.tm_hour = hour;
		tmTmp.tm_min  = mi;
		tmTmp.tm_sec  = ss;
		return mktime( &tmTmp );
	}
	
	
	time_t StrToTime(char * szTime,STRING time_format = "%4d-%2d-%2d %2d:%2d:%2d")  
	{  
		struct tm tm1;  
		time_t t;  
		memset(&tm1,0,sizeof(tm));		//给tm结构赋初值，防止传入字符串不合法报错
		sscanf(szTime,time_format.c_str() ,     
			&tm1.tm_year,  
			&tm1.tm_mon,  
			&tm1.tm_mday,  
			&tm1.tm_hour,  
			&tm1.tm_min,  
			&tm1.tm_sec);               
		tm1.tm_year -= 1900;  
		tm1.tm_mon --;  
		tm1.tm_isdst=-1;    
		t = mktime(&tm1);  
		return t;  
	} 
	
	bool FileExist( const STRING& file_path ){
		return 0 == access( file_path.c_str(), F_OK );
	}
	
	bool FileCopy( const STRING& res_file_path, const STRING& desc_file_path ){
		STRING command = "cp -f " + res_file_path + " " + desc_file_path;
		return system( command.c_str() );  //ls -l
	}
	//
	template<typename T>
	void RelpaceVector( const vector<T>& source, vector<T>& desc ){
		desc.resize( source.size() );
		memcpy( &desc[0], &source[0], sizeof(T) * source.size() );
	}
	
	void MemoryZero( void* p, int length ){
		memset( p, 0, length );
	}
	
	void ThreadSleep( int ms ){
		usleep( ms * 1000 );
	}
	
	std::vector<unsigned char> CurrentTime(){
		time_t t;
		time( &t );
		tm *p = localtime( &t );
	
		std::vector<unsigned char> data;
		unsigned char msec[2];
		int ms = p->tm_sec * 1000;//
		DtxyNet::Utility::IToA<int,unsigned char>( ms, msec, 2);
	
		data.push_back( msec[1] ); //m_second
		data.push_back( msec[0] ); //m_second
		data.push_back( p->tm_min ); //m_second
		data.push_back( p->tm_hour ); //m_second
		data.push_back( p->tm_mday ); //m_second
		data.push_back( p->tm_mon + 1 ); //m_second
		data.push_back( p->tm_year - 100 ); //m_second
	
		return data;
	}
	
	STRING UTF_8ToANSI( const char* ptrUTF)
	{
		CodeConverter codeCon;
		char* str = NULL;
		codeCon.Utf8ToGB2312((char*)ptrUTF,strlen(ptrUTF),&str);
		STRING result( str );	
		delete[] str;
		return result;
	}
	
	
	bool SetSysTime( time_t t ){
		struct timeval tv;
		struct timezone tz;
		tz.tz_minuteswest = 0;
		tz.tz_dsttime = 0;
		tv.tv_sec = t;
	    tv.tv_usec = 0;
		return settimeofday (&tv , &tz) == 0;		//成功执行时，返回0
	}
}

#endif