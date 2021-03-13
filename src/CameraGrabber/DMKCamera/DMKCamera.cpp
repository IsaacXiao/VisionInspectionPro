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
	//参数为true则实时拍照false为触发拍照
	grabber_->startLive(true);
}
