#ifndef PLATFORM_HEAD_H
#define PLATFORM_HEAD_H

/// �κ�.Dll��.So����Ҫʹ��ȫ�ֵ���־
/// ȫ�ֵ���־Record����Configure
/// ��Ҫ�õ���������ϵͳƽ̨�ĺ���
/// ���б��뵥Ԫ�����ܿ�����Щ�����Ķ���
/// ������inlineд��cpp��������鷳�ö�
/// ����һ�ֽ�������������Ͷ��嶼д.h��
/// ��namespace��һ��
/// ��������������namespace�����ַ����
/// �Ͳ��ᱻ���Ӵ���������

#ifdef _WIN64 //|| WIN32 
#include "PlatForm/WindowsCore.h"
#else
#include "PlatForm/LinuxCore.h"
#endif

#endif

