#ifndef HIK_CAMERA_H
#define HIK_CAMERA_H

#include "../ICameraGrabber.h"
#include "CommonInclude/PlatFormHead.h"
#include "Logger/BroadCastLogger.hpp"


#include "CommonInclude/Memory.hpp"
#include "CommonInclude/TypeDefine.h"


#include "../../Mediator/IMediator.h"

#include "CommonInclude/InspectException.h"
#include "CommonInclude/utility.hpp"

#include <conio.h>
#include "MvCameraControl.h"


namespace
{
	int RGB2BGR(unsigned char* pRgbData, unsigned int nWidth, unsigned int nHeight)
	{
		if (NULL == pRgbData)
		{
			return MV_E_PARAMETER;
		}

		for (unsigned int j = 0; j < nHeight; j++)
		{
			for (unsigned int i = 0; i < nWidth; i++)
			{
				unsigned char red = pRgbData[j * (nWidth * 3) + i * 3];
				pRgbData[j * (nWidth * 3) + i * 3] = pRgbData[j * (nWidth * 3) + i * 3 + 2];
				pRgbData[j * (nWidth * 3) + i * 3 + 2] = red;
			}
		}

		return MV_OK;
	}

	// convert data stream in Mat format
	ImgTypeOrg Convert2Mat(MV_FRAME_OUT_INFO_EX* pstImageInfo, unsigned char* pData)
	{
		ImgTypeOrg srcImage;
		if (pstImageInfo->enPixelType == PixelType_Gvsp_Mono8)
		{
			srcImage = cv::Mat(pstImageInfo->nHeight, pstImageInfo->nWidth, CV_8UC1, pData);
		}
		else if (pstImageInfo->enPixelType == PixelType_Gvsp_RGB8_Packed)
		{
			RGB2BGR(pData, pstImageInfo->nWidth, pstImageInfo->nHeight);
			srcImage = cv::Mat(pstImageInfo->nHeight, pstImageInfo->nWidth, CV_8UC3, pData);
		}
		//else
		//{
		//	throw CameraGrabberException("unsupported pixel format");
		//}
		return srcImage;
	}

	struct UserData
	{
		USHORT camera_id_;
		std::weak_ptr<IMediator> mediator_;
		UserData( USHORT camera_id, std::weak_ptr<IMediator> mediator ):camera_id_(camera_id), mediator_(mediator){}
	};

	void __stdcall ImageCallBackEx(unsigned char* pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser)
	{
		ImgTypeOrg img = Convert2Mat(pFrameInfo, pData);
		UserData* user_data = (UserData*)pUser;
		user_data->mediator_.lock()->StoreImage(user_data->camera_id_, std::move(img));
	}
}

class HikCamera: public ICameraGrabber
{
	using CameraHandle = void*;
public:
	HikCamera(const STRING& cfg);
	~HikCamera();

	static const char* Name() { return "HikCamera"; }

	virtual void StartGrabbing() override
	{
		// ch:打开设备 | Open device
		if (MV_OK != MV_CC_OpenDevice(handle_))
		{
			throw CameraGrabberException("Open Device fail!");
		}

		InitSettings();

		// ch:设置触发模式为on | eb:Set trigger mode as on
		if (MV_OK != MV_CC_SetEnumValue(handle_, "TriggerMode", /*MV_TRIGGER_MODE_ON*/MV_TRIGGER_MODE_OFF))
		{
			throw CameraGrabberException("Set Trigger Mode fail");
		}

		// ch:注册抓图回调 | en:Register image callback
		user_data_ = new UserData(camera_id_, mediator_);
		if (MV_OK != MV_CC_RegisterImageCallBackEx(handle_, ImageCallBackEx, (void*)user_data_))
		{
			throw CameraGrabberException("Register Image CallBack fail");
		}

		// ch:开始取流 | en:Start grab image
		if (MV_OK != MV_CC_StartGrabbing(handle_))
		{
			throw CameraGrabberException("Start Grabbing fail!");
		}
	}
	virtual void StopGrabbing() override
	{
		// ch:停止取流 | en:Stop grab image
		MV_CC_StopGrabbing(handle_);

		// ch:关闭设备 | en:Close device
		MV_CC_CloseDevice(handle_);

		// ch:销毁句柄 | en:Destroy handle
		MV_CC_DestroyHandle(handle_);

		DeletePtr(user_data_);
	}
	virtual void SoftTrigger() override
	{

	}
	virtual void SetId(USHORT id) override
	{
		// ch:枚举设备 | Enum device
		memset(&stDeviceList_, 0, sizeof(MV_CC_DEVICE_INFO_LIST));
	
		if (MV_OK != MV_CC_EnumDevices(MV_GIGE_DEVICE | MV_USB_DEVICE, &stDeviceList_))
		{
			throw CameraGrabberException("Enum Devices fail");
		}

		// ch:选择设备并创建句柄 | Select device and create handle
		if (MV_OK != MV_CC_CreateHandle(&handle_, stDeviceList_.pDeviceInfo[id]))
		{
			throw CameraGrabberException("Create Handle fail");
		}

		camera_id_ = id;
	}
private:
	MV_CC_DEVICE_INFO_LIST stDeviceList_;
	CameraHandle handle_{nullptr};
	UserData* user_data_{nullptr};

	void InitSettings()
	{
		// ch:探测网络最佳包大小(只对GigE相机有效) | en:Detection network optimal package size(It only works for the GigE camera)
		if (stDeviceList_.pDeviceInfo[camera_id_]->nTLayerType == MV_GIGE_DEVICE)
		{
			int nPacketSize = MV_CC_GetOptimalPacketSize(handle_);
			if (nPacketSize>0) MV_CC_SetIntValue(handle_, "GevSCPSPacketSize", nPacketSize);
		}
	}
};



#endif // !HIK_CAMERA_H
