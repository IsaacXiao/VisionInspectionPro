// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#include "dllmain.h"
#include "CommonInclude/Memory.hpp"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

////
////通过名称Id创建对象
////
extern "C" DMK_CAMERA_API CameraGrabberPtr Create(const char* name_ptr, const char* config_path)
{
	if (0 == strcmp(name_ptr, DMKCamera::Name()))
	{
		return new DMKCamera(config_path);
	}
	return nullptr;
}

////
////获取所提供的名称Id数量
////
extern "C" DMK_CAMERA_API short Number()
{
	return 1;
}

////
////获取名称Id列表
////
extern "C" DMK_CAMERA_API void Names(char** names_ptr)
{
	strcpy(names_ptr[0], DMKCamera::Name());
}

////
////保证谁创建谁释放的原理释放对象空间.
////
extern "C" DMK_CAMERA_API void Remove(CameraGrabberPtr ptr)
{
	DeletePtr(ptr);
}
