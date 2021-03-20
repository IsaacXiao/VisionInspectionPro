// DMKCamera.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "DMKCamera.h"
#include "CommonInclude/TypeDefine.h"
#include "Logger/BroadCastLogger.hpp"

DMKCamera::DMKCamera(const STRING & cfg):
	dmk_cfg_(cfg), grabber_(CreateGrabber())
{
}



void DMKCamera::StartLive(HWND where)
{
	//TODO: 把根据窗口句柄转换宽和高做成函数
	RECT rctA;
	GetWindowRect(where, &rctA);
	int width = rctA.right - rctA.left;   
	int height = rctA.bottom - rctA.top; 

	grabber_->showDevicePage();
	if (grabber_->isDevValid())
	{
		grabber_->setHWND(where);
		grabber_->setDefaultWindowPosition(false);
		grabber_->setWindowSize(width,height);

		grabber_->startLive();
	}
	else
	{
		//TODO: 用异常和日志来写这里
		MessageBox(NULL, "warning", "No device was selected", MB_OK);
	}
}
