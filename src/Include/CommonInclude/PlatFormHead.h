#ifndef PLATFORM_HEAD_H
#define PLATFORM_HEAD_H

/// 任何.Dll或.So都需要使用全局的日志
/// 全局的日志Record依赖Configure
/// 需要用到依赖操作系统平台的函数
/// 所有编译单元必须能看到这些函数的定义
/// 不做成inline写到cpp里搞起来麻烦得多
/// 另外一种解决方案是声明和定义都写.h里
/// 用namespace包一下
/// 这样编译器遇到namespace做名字粉碎后
/// 就不会被链接错误困扰了

#ifdef _WIN64 //|| WIN32 
#include "PlatForm/WindowsCore.h"
#else
#include "PlatForm/LinuxCore.h"
#endif

#endif

