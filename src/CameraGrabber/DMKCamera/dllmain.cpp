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
extern "C" DMK_CAMERA_API CameraGrabberPtr Create(const char* name_ptr, const char* config_path)
{
	if (0 == strcmp(name_ptr, DMKCamera::Name()))
	{
		return new DMKCamera(config_path);
	}
	return nullptr;
}

////
////��ȡ���ṩ������Id����
////
extern "C" DMK_CAMERA_API short Number()
{
	return 1;
}

////
////��ȡ����Id�б�
////
extern "C" DMK_CAMERA_API void Names(char** names_ptr)
{
	strcpy(names_ptr[0], DMKCamera::Name());
}

////
////��֤˭����˭�ͷŵ�ԭ���ͷŶ���ռ�.
////
extern "C" DMK_CAMERA_API void Remove(CameraGrabberPtr ptr)
{
	DeletePtr(ptr);
}
