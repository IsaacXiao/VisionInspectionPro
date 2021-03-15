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
	////����Ϊtrue��ʵʱ����falseΪ��������
	//grabber_->startLive(true);


}

void DMKCamera::DisplayImg(HWND where, UINT width, UINT height)
{
	// Show the device page.
	grabber_->showDevicePage();//bool���ͣ���ʾ�豸���ý���

	// Check if there is a valid device.
	if (grabber_->isDevValid())//����пɻ�ȡ���豸��ʼ��ʾ
	{
		// Set the window that should display the live video.
		grabber_->setHWND(where);//ָ�����ھ��

		/*setWindowSize()������Ƶ��ʾ���ڵĴ�С��setDefaultWindowPosition�����ΪTrue����
		��Ƶֻ�ܰ�����ʵ��С��ʾ�������ڸı�������ʾ���ڴ�Сʱ��������Ϊfalse*/

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
