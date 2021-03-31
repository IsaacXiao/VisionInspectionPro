#ifndef IMEDIATOR_H
#define IMEDIATOR_H

#include "ThreadSafe_Queue.hpp"
#include "CommonInclude/TypeDefine.h"
#include "Configure/Configure.hpp"
#include <memory>
#include "opencv2/opencv.hpp"
#include "../CameraGrabber/ICameraGrabber.h"


class IMediator
{
private:
	
protected:
	using StorageType = ThreadSafe_Queue<ImgType>;
	VECTOR<StorageType> img_stash_;
	Configure<FRAMWORK_PART::MEDIATOR> cfg_;
	bool stop_dispatch_{true};
public:
	IMediator(const STRING & cfg):cfg_(cfg)
	{
		size_t n = stoi(cfg_.Param()["fifo_number"]);
		for ( size_t i = 0; i < n; i++ )
		{
			img_stash_.emplace_back(StorageType());
		}
	}
	void StartDispatch() { stop_dispatch_ = false;  }
	void StopDispatch() { stop_dispatch_ = true;  }
	virtual ~IMediator(){}
	virtual void StoreImage(size_t id, ImgType&& img) = 0;
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