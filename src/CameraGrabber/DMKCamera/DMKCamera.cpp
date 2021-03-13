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
	//grabber_->showDevicePage()
	//����Ϊtrue��ʵʱ����falseΪ��������
	grabber_->startLive(true);
}
