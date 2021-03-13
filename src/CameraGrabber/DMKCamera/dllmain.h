#pragma once

#include "DMKCamera.h"

#ifdef _WIN64
#define DMK_CAMERA_API __declspec(dllexport)
#else
#define DMK_CAMERA_API
#endif

#include "DMKCamera.h"


////
////通过名称Id创建对象
////
extern "C" DMK_CAMERA_API CameraGrabberPtr Create(const char* name_ptr, const char* config_path);

////
////获取所提供的名称Id数量
////
extern "C" DMK_CAMERA_API short Number();

////
////获取名称Id列表
////
extern "C" DMK_CAMERA_API void Names(char** names_ptr);

////
////保证谁创建谁释放的原理释放对象空间.
////
extern "C" DMK_CAMERA_API void Remove(CameraGrabberPtr ptr);