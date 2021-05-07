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

/*!
 * \class classname
 *
 * \brief 
 * 
 * 调用端使用方法
 * 
	for ( size_t i = 0; i < camera_number_; i++ )
	{
		ICameraGrabber *camera = new HikCamera;
		//1.设置ID，枚举设备会在第一次调用时自动完成
		camera->SetId(i);
		//2. 保存中介者类的指针
		camera->AttachMediator(...);
	}
	相机接口如函数名所示
    void OpenDevice();
	void StartGrabbing()
 *
 * \author XR
 * \date ���� 2021
 */


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
	//获取图像回调函数
	void __stdcall ImageCallBackEx(unsigned char* pData, MV_FRAME_OUT_INFO_EX* pFrameInfo, void* pUser)
	{
		//此处调用MV_CC_ConvertPixelType可以转换像素格式见ConvertPixelType.cpp
		ImgTypeOrg img;
		img.mat_ = Convert2Mat(pFrameInfo, pData);
		img.num_ = pFrameInfo->nFrameNum;
		UserData* user_data = (UserData*)pUser;
		user_data->mediator_.lock()->StoreImage(user_data->camera_id_, std::move(img));
		
		//还需更多帧信息见ChunkData.cpp
	}
	//异常回调 
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

//参数设置见CamLBasicDemo.cpp
class HikCamera: public ICameraGrabber
{
	using CameraHandle = void*;
public:
	HikCamera(const STRING& cfg);
	~HikCamera();

	static const char* Name() { return "HikCamera"; }
	//1.设置ID，枚举设备会在第一次调用时自动完成
	virtual void SetId(USHORT id) override;
	//2.打开设备
	virtual void OpenDevice() override;
	virtual void CloseDevice() override;
	virtual void StartGrabbing() override;
	virtual void StopGrabbing() override;
	virtual void SoftTrigger() override;

	virtual float GetFloatValue(const char* what) const override;
	virtual void SetFloatValue(const char* what, float fValue) override;
	virtual UINT GetIntValue(const char* what) const override;
	virtual void SetIntValue(const char* what, UINT iValue) override;
	virtual void SetMode(int mode);
private:
	MV_CC_DEVICE_INFO_LIST stDeviceList_;
	bool is_enumed_{false};
	CameraHandle handle_{nullptr};
	UserData* user_data_{nullptr};
	void InitSettings();
};



#endif // !HIK_CAMERA_H
