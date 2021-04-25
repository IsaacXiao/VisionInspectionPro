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
	cv::Mat Convert2Mat(MV_FRAME_OUT_INFO_EX* pstImageInfo, unsigned char* pData)
	{
		cv::Mat srcImage;
		if (pstImageInfo->enPixelType == PixelType_Gvsp_Mono8)
		{
			srcImage = cv::Mat(pstImageInfo->nHeight, pstImageInfo->nWidth, CV_8UC1, pData);
		}
		else if (pstImageInfo->enPixelType == /*PixelType_Gvsp_BayerRG8*/PixelType_Gvsp_RGB8_Packed)
		{
			RGB2BGR(pData, pstImageInfo->nWidth, pstImageInfo->nHeight);
			srcImage = cv::Mat(pstImageInfo->nHeight, pstImageInfo->nWidth, CV_8UC3, pData);
		}
		else
		{
			throw CameraGrabberException("unsupported pixel format");
		}
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
		//�˴�����MV_CC_ConvertPixelType����ת�����ظ�ʽ��ConvertPixelType.cpp
		ImgTypeOrg img;
		img.mat_ = Convert2Mat(pFrameInfo, pData);
		img.num_ = pFrameInfo->nFrameNum;
		UserData* user_data = (UserData*)pUser;
		user_data->mediator_.lock()->StoreImage(user_data->camera_id_, std::move(img));
		
		//�������֡��Ϣ��ChunkData.cpp
	}

	void __stdcall ExceptionCallBack(unsigned int nMsgType, void* pUser)
	{
		if (nMsgType == MV_EXCEPTION_DEV_DISCONNECT)
		{
			UserData* user_data = (UserData*)pUser;
			user_data->mediator_.lock()->CameraOffLine(user_data->camera_id_);
		}
		else
		{
			GlobalLogger::Record("HikCamera", LOG_LEVEL::HIGH_WARN, "Unknown exception");
		}
	}
}

//�������ü�CamLBasicDemo.cpp
class HikCamera: public ICameraGrabber
{
	using CameraHandle = void*;
public:
	HikCamera(const STRING& cfg);
	~HikCamera();

	static const char* Name() { return "HikCamera"; }

	virtual void OpenDevice() override;
	virtual void CloseDevice() override;
	virtual void StartGrabbing() override;
	virtual void StopGrabbing() override;
	virtual void SoftTrigger() override;
	virtual void SetId(USHORT id) override;
	virtual float GetFloatValue(const char* what) const override;
	virtual void SetFloatValue(const char* what, float fValue) override;
	virtual UINT GetIntValue(const char* what) const override;
	virtual void SetIntValue(const char* what, UINT iValue) override;
private:
	MV_CC_DEVICE_INFO_LIST stDeviceList_;
	CameraHandle handle_{nullptr};
	UserData* user_data_{nullptr};
	bool callback_registered_{ false };
	void InitSettings();
};



#endif // !HIK_CAMERA_H
