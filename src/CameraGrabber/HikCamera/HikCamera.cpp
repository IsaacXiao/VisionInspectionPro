// HikCamera.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "HikCamera.h"

HikCamera::HikCamera(const STRING& cfg) :
	ICameraGrabber(cfg)
{
	MV_CC_DestroyHandle(handle_);
}

HikCamera::~HikCamera()
{
	GlobalLogger::Record("HikCamera", LOG_LEVEL::TRACK, "Destroyed");
}

void HikCamera::OpenDevice()
{
	if (MV_OK != MV_CC_OpenDevice(handle_)) throw CameraGrabberException("Open Device fail!");

	InitSettings();

	if (MV_OK != MV_CC_SetEnumValue(handle_, "TriggerMode", /*MV_TRIGGER_MODE_ON*/MV_TRIGGER_MODE_OFF)) throw CameraGrabberException("Set Trigger Mode fail");
}

void HikCamera::CloseDevice()
{
	MV_CC_CloseDevice(handle_);
	
	callback_registered_ = false;
}

void HikCamera::StartGrabbing()
{
	user_data_ = new UserData(camera_id_, mediator_);
	if (MV_OK != MV_CC_RegisterImageCallBackEx(handle_, ImageCallBackEx, (void*)user_data_)) throw CameraGrabberException("Register Image CallBack fail");
	if (MV_OK != MV_CC_RegisterExceptionCallBack(handle_, ExceptionCallBack, (void*)user_data_)) throw CameraGrabberException("Register Image ExceptionCallBack fail");
	//if (!callback_registered_)
	//{
	//	MV_CC_RegisterImageCallBackEx(handle_, ImageCallBackEx, (void*)user_data_);
	//	MV_CC_RegisterExceptionCallBack(handle_, ExceptionCallBack, (void*)user_data_);
	//	callback_registered_ = true;
	//} 

	auto nRet = MV_CC_StartGrabbing(handle_);
	if (MV_OK != nRet)
	{
		printf("Get Trigger Mode fail! nRet [0x%x]\n", nRet);
		throw CameraGrabberException("Start Grabbing fail!");
	}
}

void HikCamera::StopGrabbing()
{
	MV_CC_StopGrabbing(handle_);
	DeletePtr(user_data_);
}

void HikCamera::SoftTrigger()
{
	MV_CC_SetCommandValue(handle_, "TriggerSoftware");
}

void HikCamera::SetId(USHORT id)
{
	memset(&stDeviceList_, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
	if (MV_OK != MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &stDeviceList_)) throw CameraGrabberException("Enum Devices fail");

	// ch:选择设备并创建句柄 | Select device and create handle
	if (MV_OK != MV_CC_CreateHandle(&handle_, stDeviceList_.pDeviceInfo[id])) throw CameraGrabberException("Create Handle fail");

	camera_id_ = id;
}

void HikCamera::InitSettings()
{
	// ch:探测网络最佳包大小(只对GigE相机有效) | en:Detection network optimal package size(It only works for the GigE camera)
	if (stDeviceList_.pDeviceInfo[camera_id_]->nTLayerType == MV_GIGE_DEVICE)
	{
		int nPacketSize = MV_CC_GetOptimalPacketSize(handle_);
		if (nPacketSize > 0) MV_CC_SetIntValue(handle_, "GevSCPSPacketSize", nPacketSize);
	}
}

float HikCamera::GetFloatValue(const char* what) const
{
	MVCC_FLOATVALUE stFloatVal;
	memset(&stFloatVal, 0, sizeof(MVCC_FLOATVALUE));
	if (MV_OK != MV_CC_GetFloatValue(handle_, what, &stFloatVal))
		throw CameraGrabberException("Get float value fail!");
	return stFloatVal.fCurValue;
}

void HikCamera::SetFloatValue(const char* what, float fValue)
{
	MV_CC_SetFloatValue(handle_, what, fValue);
}

UINT HikCamera::GetIntValue(const char* what) const
{
	MVCC_INTVALUE stIntVal;
	memset(&stIntVal, 0, sizeof(MVCC_INTVALUE));
	if (MV_OK != MV_CC_GetIntValue(handle_, what, &stIntVal))
		throw CameraGrabberException("Get int value fail!");
	return stIntVal.nCurValue;
}

void HikCamera::SetIntValue(const char* what, UINT iValue)
{
	MV_CC_SetIntValue(handle_, what, iValue);
}