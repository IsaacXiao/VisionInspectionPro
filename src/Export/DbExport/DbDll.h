#ifndef DB_DLL_H
#define DB_DLL_H

#ifdef WIN32
	#define DB_EXPORT_API __declspec(dllexport)
#else
	#define DB_EXPORT_API
#endif

#include "DbExport.h"

////
////通过名称Id创建对象
////
extern "C" DB_EXPORT_API ExportPtr Create( const char* name_ptr, const char* config_path );

////
////获取所提供的名称Id数量
////
extern "C" DB_EXPORT_API short Number();

////
////获取名称Id列表
////
extern "C" DB_EXPORT_API void Names( char** names_ptr );

////
////保证谁创建谁释放的原理释放对象空间.
////
extern "C" DB_EXPORT_API void Remove( ExportPtr ptr );

#endif