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
public:
	IMediator(const STRING & cfg):cfg_(cfg)
	{
		size_t n = stoi(cfg_.Param()["fifo_number"]);
		for ( size_t i = 0; i < n; i++ )
		{
			img_stash_.emplace_back(StorageType());
		}
	}
	virtual ~IMediator(){}
	virtual void StoreImage(size_t id, ImgType&& img) = 0;
	virtual ImgTypePtr FetchToBroadCast(size_t id) = 0;
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