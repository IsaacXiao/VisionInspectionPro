#pragma once

#include "ThreadMediator.h"

#ifdef _WIN64
#define THREAD_MEDIATOR_API __declspec(dllexport)
#else
#define THREAD_MEDIATOR_API
#endif

#include "ThreadMediator.h"


////
////ͨ������Id��������
////
extern "C" THREAD_MEDIATOR_API MediatorOrg Create(const char* name_ptr, const char* config_path);

////
////��ȡ���ṩ������Id����
////
extern "C" THREAD_MEDIATOR_API short Number();

////
////��ȡ����Id�б�
////
extern "C" THREAD_MEDIATOR_API void Names(char** names_ptr);

////
////��֤˭����˭�ͷŵ�ԭ���ͷŶ���ռ�.
////
extern "C" THREAD_MEDIATOR_API void Remove(MediatorOrg ptr);
