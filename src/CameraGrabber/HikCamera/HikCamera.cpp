// HikCamera.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "HikCamera.h"

HikCamera::HikCamera(const STRING& cfg) :
	ICameraGrabber(cfg)
{
}

HikCamera::~HikCamera()
{
}

void HikCamera::StartGrabbing()
{
	if (MV_OK != MV_CC_OpenDevice(handle_)) throw CameraGrabberException("Open Device fail!");
	InitSettings();

	if (MV_OK != MV_CC_SetEnumValue(handle_, "TriggerMode", /*MV_TRIGGER_MODE_ON*/MV_TRIGGER_MODE_OFF)) throw CameraGrabberException("Set Trigger Mode fail");
	user_data_ = new UserData(camera_id_, mediator_);
	if (MV_OK != MV_CC_RegisterImageCallBackEx(handle_, ImageCallBackEx, (void*)user_data_)) throw CameraGrabberException("Register Image CallBack fail");
	MV_CC_RegisterExceptionCallBack(handle_, ExceptionCallBack, (void*)user_data_);

	if (MV_OK != MV_CC_StartGrabbing(handle_)) throw CameraGrabberException("Start Grabbing fail!");
}

void HikCamera::StopGrabbing()
{
	MV_CC_StopGrabbing(handle_);
	MV_CC_CloseDevice(handle_);
	MV_CC_DestroyHandle(handle_);
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
