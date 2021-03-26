#pragma once

#include "ThreadMediator.h"

#ifdef _WIN64
#define THREAD_MEDIATOR_API __declspec(dllexport)
#else
#define THREAD_MEDIATOR_API
#endif

#include "ThreadMediator.h"


////
////通过名称Id创建对象
////
extern "C" THREAD_MEDIATOR_API MediatorOrg Create(const char* name_ptr, const char* config_path);

////
////获取所提供的名称Id数量
////
extern "C" THREAD_MEDIATOR_API short Number();

////
////获取名称Id列表
////
extern "C" THREAD_MEDIATOR_API void Names(char** names_ptr);

////
////保证谁创建谁释放的原理释放对象空间.
////
extern "C" THREAD_MEDIATOR_API void Remove(MediatorOrg ptr);
