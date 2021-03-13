



#include "WindowsCore.h"
#include "CommonInclude/utility.hpp"

std::basic_string<WCHAR> GetModuleDirectoryW()
{
	 WCHAR slash[2] = { '\\' };
	 WCHAR cache[512];
	 ::GetModuleFileNameW( NULL, cache, 512 );
	 std::basic_string<WCHAR> dir( cache );
	 dir = dir.substr( 0, dir.find_last_of( slash ) );	
	 return dir;
}

void BrowseFiles( const STRING& ext, vector<STRING>& full_paths ) 
{	
	struct __finddata64_t	file;
	long long				handle;
	const int			MAX_PATH_SIZE = 256;	
	char				path[MAX_PATH_SIZE];

	handle = (long long)_findfirst64( "*", &file );
	if( handle == -1 )
		return;
	do
	{
		if(file.attrib & _A_SUBDIR ) //is dir
		{
			if( file.name[0] != '.') // dir name is '.' or  '..'
			{
				_chdir( file.name ); //enter path				
				BrowseFiles( ext, full_paths );//go on
				_chdir(".."); //return prev dir
			}
		}
		else
		{		
			if( !ext.empty() )
			{
				//if( NULL == strstr( file.name , ext.c_str() ) )
				STRING && reg_match = "^[a-zA-Z0-9_-]+\\" + ext + "$";
				if( !RegCheck(file.name,std::regex(reg_match)) )
					continue;
			}
			_getcwd( path, MAX_PATH_SIZE ); 
			strcat( path, "\\" ); 
			strcat( path, file.name );				
			full_paths.push_back( path ); 					
		}
	}while( !_findnext64( handle, &file ) );
	_findclose(handle);
}

void BrowseFiles( const STRING& dir, const STRING& ext, vector<STRING>& full_paths ) 
{
	auto res = _chdir( dir.c_str() );
	BrowseFiles( ext, full_paths );
	_chdir( ".." );
	if ( 0 == full_paths.size() )
	{
		throw FilePathException("Module Path does not exist!");
	}
}

void BrowseSubDir( vector<STRING>& dir_names, bool is_full_path )
{
	struct _finddata_t	file;
	long				handle = -1;
	const int			MAX_PATH_SIZE = 256;	
	char				path[MAX_PATH_SIZE];

	handle = (long)_findfirst( "*", &file );
	if( handle == -1 )
		return;
	do
	{
		if(file.attrib & _A_SUBDIR ) //is dir
		{
			if( file.name[0] != '.') // dir name is '.' or  '..'
			{
				if( is_full_path )
				{
					_getcwd( path, MAX_PATH_SIZE ); 
					strcat( path, "\\" ); 
					strcat( path, file.name );				
					dir_names.push_back( path ); 
				}
				else
				{
					dir_names.push_back( file.name );
				}
			}
		}	
	}while( ! _findnext( handle, &file ) );	
	_findclose(handle);
}

////
////
////
void BrowseSubDirs( const STRING& dir, vector<STRING>& dir_names, bool is_full_path )
{
	_chdir( dir.c_str() );
	BrowseSubDir( dir_names, is_full_path );
	_chdir( ".." );
}

time_t IntToCTime( int year, int month, int day, int hour, int mi, int ss )
{
	tm tmTmp;
	ZeroMemory( &tmTmp, sizeof(tm) );
	tmTmp.tm_year = year;
	tmTmp.tm_year = (tmTmp.tm_year - 1970 ) + 70;
	tmTmp.tm_mon  = month - 1;
	tmTmp.tm_mday = day;
	tmTmp.tm_hour = hour;
	tmTmp.tm_min  = mi;
	tmTmp.tm_sec  = ss;
	return mktime( &tmTmp );
}

int  GetFileLen(STRING file_name)
{
	FILE *fp;
	if((fp=fopen(file_name.c_str(),"r"))==NULL)
	{
		//fclose(fp);
		return 0;
	}
	int length = filelength(fileno(fp));    
	fclose(fp);
	return length;
}

bool FileReadOnly(STRING file_name, void* data, int& data_len, bool is_binary )
{
	//打开文件
	STRING file_mode;
	if ( is_binary )
		file_mode = "rb";
	else
		file_mode = "rt";
	FILE* hFile=fopen(file_name.c_str(),file_mode.c_str());
	if(hFile==NULL)
	{
		return false;
	}
	int read_size=0;//实际读入的字符数
	//循环读取文件字节数
	while(read_size<data_len)
	{
		int curr_read_size = 0;//当前循环写入的字节数
		curr_read_size = fread((char*)data+read_size, sizeof(unsigned char), data_len-read_size, hFile);
		if(curr_read_size == 0)
			break;
		read_size += curr_read_size;
	}
	data_len = read_size;
	fclose(hFile);
	return true;
}

bool FileWriteOnly(STRING file_name, void* data, int data_len, bool is_binary)
{
	//打开文件
	STRING file_mode;
	if ( is_binary )
		file_mode = "wb";
	else
		file_mode = "wt";
	FILE* hFile=fopen(file_name.c_str(),file_mode.c_str());
	if(hFile==NULL)
	{
		return false;
	}
	int write_size=0;//实际读入的字符数
	//循环读取文件字节数
	while(write_size<data_len)
	{
		int curr_write_size = 0;//当前循环写入的字节数
		curr_write_size = fwrite((char*)data+write_size, sizeof(unsigned char), data_len-write_size, hFile);
		if(curr_write_size == 0)
			break;
		write_size += curr_write_size;
	}
	fclose(hFile);
	return true;
}

time_t StrToTime( char * szTime,STRING time_format )  
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

bool SetSysTime( time_t t )
{
	struct tm* tmp = localtime( &t );
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

#if 0

void GetMacAddrList( vector<string>& vec )
{
	PIP_ADAPTER_INFO head = NULL;
	PIP_ADAPTER_INFO pIpAdapterInfo = (IP_ADAPTER_INFO *) malloc( sizeof(IP_ADAPTER_INFO) );    
	unsigned long stSize = sizeof(IP_ADAPTER_INFO);    
	int nRel = GetAdaptersInfo(pIpAdapterInfo,&stSize);    
	if (ERROR_BUFFER_OVERFLOW==nRel)    
	{    
		free(pIpAdapterInfo);
		pIpAdapterInfo = NULL;
		pIpAdapterInfo = (IP_ADAPTER_INFO *) malloc (stSize); 
		nRel=GetAdaptersInfo(pIpAdapterInfo,&stSize);        
	}  

	head = pIpAdapterInfo;
	if (ERROR_SUCCESS==nRel)   
	{        
		while (pIpAdapterInfo != NULL)    
		{     
			char pMacAddress[5] = "";
			string strMacAddress = "";
			for (UINT i = 0; i < pIpAdapterInfo->AddressLength; i++) 
			{
				sprintf_s(pMacAddress,5,"%02x", pIpAdapterInfo->Address[i]);
				strMacAddress += pMacAddress;
			}
			vec.push_back(strMacAddress);			
			pIpAdapterInfo = pIpAdapterInfo->Next;   			
		}     
	} 
	if ( head != NULL )           
		free(head) ;  		
}

#endif

