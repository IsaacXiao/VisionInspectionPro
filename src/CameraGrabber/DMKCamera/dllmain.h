#pragma once

#include "DMKCamera.h"

#ifdef _WIN64
#define DMK_CAMERA_API __declspec(dllexport)
#else
#define DMK_CAMERA_API
#endif

#include "DMKCamera.h"


////
////ͨ������Id��������
////
extern "C" DMK_CAMERA_API CameraGrabberPtr Create(const char* name_ptr, const char* config_path);

////
////��ȡ���ṩ������Id����
////
extern "C" DMK_CAMERA_API short Number();

////
////��ȡ����Id�б�
////
extern "C" DMK_CAMERA_API void Names(char** names_ptr);

////
////��֤˭����˭�ͷŵ�ԭ���ͷŶ���ռ�.
////
extern "C" DMK_CAMERA_API void Remove(CameraGrabberPtr ptr);