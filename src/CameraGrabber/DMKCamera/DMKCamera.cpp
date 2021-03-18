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

void DMKCamera::StartLive(HWND where, UINT width, UINT height)
{
	// Show the device page.
	grabber_->showDevicePage();//bool类型，显示设备设置界面

	if (grabber_->isDevValid())
	{
		grabber_->setHWND(where);
		grabber_->setDefaultWindowPosition(false);
		grabber_->setWindowSize(width,height);

		// Start the live video.
		grabber_->startLive();
	}
	else
	{
		//TODO: 用异常和日志来写这里
		MessageBox(NULL, "warning", "No device was selected", MB_OK);
	}
}
