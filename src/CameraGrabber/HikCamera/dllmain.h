#pragma once

#include "HikCamera.h"

#ifdef _WIN64
#define Hik_CAMERA_API __declspec(dllexport)
#else
#define Hik_CAMERA_API
#endif

#include "HikCamera.h"


////
////ͨ������Id��������
////
extern "C" Hik_CAMERA_API CameraGrabberOrg Create(const char* name_ptr, const char* config_path);

////
////��ȡ���ṩ������Id����
////
extern "C" Hik_CAMERA_API short Number();

////
////��ȡ����Id�б�
////
extern "C" Hik_CAMERA_API void Names(char** names_ptr);

////
////��֤˭����˭�ͷŵ�ԭ���ͷŶ���ռ�.
////
extern "C" Hik_CAMERA_API void Remove(CameraGrabberOrg ptr);