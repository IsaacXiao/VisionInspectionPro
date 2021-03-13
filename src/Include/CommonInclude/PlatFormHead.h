#ifndef PLATFORM_HEAD_H
#define PLATFORM_HEAD_H


#ifdef _WIN64 //|| WIN32 
#include "PlatForm/Windows/WindowsCore.h"
#else
#include "PlatForm/Linux/LinuxCore.h"
#endif

#endif

