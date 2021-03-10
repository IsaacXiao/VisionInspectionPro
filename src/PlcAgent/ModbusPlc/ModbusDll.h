#ifndef MODBUS_DLL_H
#define MODBUS_DLL_H

#ifdef WIN32
	#define MODBUS_PLC_API __declspec(dllexport)
#else
	#define MODBUS_PLC_API
#endif

#include "ModbusPlc.h"


////
////通过名称Id创建对象
////
extern "C" MODBUS_PLC_API PlcAgentPtr Create( const char* name_ptr, const char* config_path );

////
////获取所提供的名称Id数量
////
extern "C" MODBUS_PLC_API short Number();

////
////获取名称Id列表
////
extern "C" MODBUS_PLC_API void Names( char** names_ptr );

////
////保证谁创建谁释放的原理释放对象空间.
////
extern "C" MODBUS_PLC_API void Remove( PlcAgentPtr ptr );

#endif
