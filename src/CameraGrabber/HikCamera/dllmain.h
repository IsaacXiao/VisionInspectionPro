#pragma once

#include "HikCamera.h"

#ifdef _WIN64
#define Hik_CAMERA_API __declspec(dllexport)
#else
#define Hik_CAMERA_API
#endif

#include "HikCamera.h"


////
////通过名称Id创建对象
////
extern "C" Hik_CAMERA_API CameraGrabberOrg Create(const char* name_ptr, const char* config_path);

////
////获取所提供的名称Id数量
////
extern "C" Hik_CAMERA_API short Number();

////
////获取名称Id列表
////
extern "C" Hik_CAMERA_API void Names(char** names_ptr);

////
////保证谁创建谁释放的原理释放对象空间.
////
extern "C" Hik_CAMERA_API void Remove(CameraGrabberOrg ptr);