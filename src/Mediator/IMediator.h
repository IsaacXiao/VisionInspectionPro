#ifndef IMEDIATOR_H
#define IMEDIATOR_H

#include "ThreadSafe_Queue.hpp"
#include "CommonInclude/TypeDefine.h"
#include "Configure/Configure.hpp"
#include <memory>
#include "opencv2/opencv.hpp"
#include "../CameraGrabber/ICameraGrabber.h"


//#include "../Facade/Facade.h"
class Facade;

/// <summary>
/// �н���ģʽ����
/// Ϊ�������û������治����
/// Ҫ��ͼƬ���߳������ȥ
/// ���õ����ò�ȥ��UI��ʾ
/// ���������ϲ�Facade*
/// </summary>

class IMediator
{
private:
	
protected:
	using StorageType = ThreadSafe_Queue<ImgType>;
	VECTOR<StorageType> img_stash_;
	Configure<FRAMWORK_PART::MEDIATOR> cfg_;
	
	Facade* facade_;
	size_t fifo_number_;
public:
	IMediator(const STRING & cfg):cfg_(cfg)
	{
		fifo_number_ = stoi(cfg_.Param()["fifo_number"]);
		for ( size_t i = 0; i < fifo_number_; i++ )
		{
			img_stash_.emplace_back(StorageType());
		}
	}
	void AttachFacade(Facade * facade)  { facade_ = facade; }
	virtual void StartDispatch() = 0;
	virtual void StopDispatch() = 0;
	virtual ~IMediator(){}
	virtual void StoreImage(size_t camera_id, ImgType&& img) = 0;
	virtual void FetchImgToWork(size_t camera_id) = 0;
};

template<>
struct PointType<IMediator>
{
	using Org = IMediator*;
	using Ptr = std::shared_ptr<IMediator>;
};

using MediatorOrg = PointType<IMediator>::Org;
using MediatorPtr = PointType<IMediator>::Ptr;

#endif