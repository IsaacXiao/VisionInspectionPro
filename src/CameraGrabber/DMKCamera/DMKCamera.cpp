// DMKCamera.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "DMKCamera.h"


DMKCamera::DMKCamera(const STRING & cfg) :dmk_cfg_(cfg)
{
	grabber_ = new DShowLib::Grabber();
}

DMKCamera::~DMKCamera()
{
	DeletePtr(grabber_);
}

void DMKCamera::InitCamera()
{
	//grabber_->showDevicePage();
	////参数为true则实时拍照false为触发拍照
	//grabber_->startLive(true);


}

void DMKCamera::DisplayImg(HWND where, UINT width, UINT height)
{
	// Show the device page.
	grabber_->showDevicePage();//bool类型，显示设备设置界面

	// Check if there is a valid device.
	if (grabber_->isDevValid())//如果有可获取的设备则开始显示
	{
		// Set the window that should display the live video.
		grabber_->setHWND(where);//指定窗口句柄

		/*setWindowSize()定义视频显示窗口的大小，setDefaultWindowPosition如果设为True，则
		视频只能按照真实大小显示，所以在改变视屏显示窗口大小时必须设置为false*/

		 //Enables or disables the default window size lock of the video window.
		grabber_->setDefaultWindowPosition(false);

		//Sets the size of the video window.
		grabber_->setWindowSize(width,height);

		// Start the live video.
		grabber_->startLive();
	}
	else
	{
		MessageBox(NULL, "warning", "No device was selected", MB_OK);
	}
}
