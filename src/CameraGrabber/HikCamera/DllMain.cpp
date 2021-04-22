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
////ͨ������Id��������
////
extern "C" Hik_CAMERA_API CameraGrabberOrg Create(const char* name_ptr, const char* config_path)
{
	if (0 == strcmp(name_ptr, HikCamera::Name()))
	{
		return new HikCamera(config_path);
	}
	return nullptr;
}

////
////��ȡ���ṩ������Id����
////
extern "C" Hik_CAMERA_API short Number()
{
	return 1;
}

////
////��ȡ����Id�б�
////
extern "C" Hik_CAMERA_API void Names(char** names_ptr)
{
	strcpy(names_ptr[0], HikCamera::Name());
}

////
////��֤˭����˭�ͷŵ�ԭ���ͷŶ���ռ�.
////
extern "C" Hik_CAMERA_API void Remove(CameraGrabberOrg ptr)
{
	DeletePtr(ptr);
}