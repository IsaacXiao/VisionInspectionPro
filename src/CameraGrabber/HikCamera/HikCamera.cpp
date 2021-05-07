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
	MV_CC_DestroyHandle(handle_);
	GlobalLogger::Record("HikCamera", LOG_LEVEL::TRACK, "Destroyed");
}

void HikCamera::OpenDevice()
{
	if (MV_OK != MV_CC_OpenDevice(handle_)) throw CameraGrabberException("Open Device fail!");

	InitSettings();

	if (MV_OK != MV_CC_SetEnumValue(handle_, "TriggerMode", trigger_mode_)) throw CameraGrabberException("Set Trigger Mode fail");
}

void HikCamera::CloseDevice()
{
	MV_CC_CloseDevice(handle_);
}

void HikCamera::StartGrabbing()
{
	user_data_ = new UserData(camera_id_, mediator_);
	if (MV_OK != MV_CC_RegisterImageCallBackEx(handle_, ImageCallBackEx, (void*)user_data_)); //throw CameraGrabberException("Register Image CallBack fail");
	if (MV_OK != MV_CC_RegisterExceptionCallBack(handle_, ExceptionCallBack, (void*)user_data_)); //throw CameraGrabberException("Register Image ExceptionCallBack fail");
	if (MV_OK != MV_CC_StartGrabbing(handle_))
	{
		//throw CameraGrabberException("Start Grabbing fail!");
	}
	else
	{
		GlobalLogger::Record("HikCamera", LOG_LEVEL::TRACK, "camera " + to_string(camera_id_) + " StartGrabbing");
	}
}

void HikCamera::StopGrabbing()
{
	MV_CC_StopGrabbing(handle_);
	DeletePtr(user_data_);
}

void HikCamera::SetMode(int mode)
{
	ICameraGrabber::SetMode(mode);
	MV_CC_SetEnumValue(handle_, "TriggerMode", trigger_mode_);
}

void HikCamera::SoftTrigger()
{
	MV_CC_SetEnumValue(handle_, "TriggerSource", MV_TRIGGER_SOURCE_SOFTWARE);
	MV_CC_SetCommandValue(handle_, "TriggerSoftware");
}

void HikCamera::SetId(USHORT id)
{
	memset(&stDeviceList_, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
	if (!is_enumed_)
	{
		if (MV_OK != MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &stDeviceList_)) throw CameraGrabberException("Enum Devices fail");

		for (USHORT i = 0; i < stDeviceList_.nDeviceNum; i++)
		{
			MV_CC_DEVICE_INFO* pDeviceInfo = stDeviceList_.pDeviceInfo[i];
			assert(pDeviceInfo->nTLayerType == MV_GIGE_DEVICE);

			int Ip1 = ((stDeviceList_.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0xff000000) >> 24);
			int Ip2 = ((stDeviceList_.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x00ff0000) >> 16);
			int Ip3 = ((stDeviceList_.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x0000ff00) >> 8);
			int Ip4 = (stDeviceList_.pDeviceInfo[i]->SpecialInfo.stGigEInfo.nCurrentIp & 0x000000ff);

			char strUserName[256] = { 0 };
			sprintf_s(strUserName, "%s %s (%s)", pDeviceInfo->SpecialInfo.stGigEInfo.chManufacturerName,
				pDeviceInfo->SpecialInfo.stGigEInfo.chModelName,
				pDeviceInfo->SpecialInfo.stGigEInfo.chSerialNumber);
			STRING&& Ip = to_string(Ip1) + "." + to_string(Ip2) + "." + to_string(Ip3) + "." + to_string(Ip4);
			STRING&& id_serial = STRING(strUserName) + ":" + Ip;
			id_serial_.emplace_back(id_serial);
		}

		is_enumed_ = true;
	}
	
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
