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
	VECTOR<std::weak_ptr<ICameraGrabber>> camera_group_;
public:
	IMediator(const STRING & cfg):cfg_(cfg)
	{
	        
	}
	virtual ~IMediator(){}
	void AttachCamera(std::weak_ptr<ICameraGrabber> camera_grabber)
	{
		img_stash_.emplace_back(StorageType());
		camera_group_.emplace_back(camera_grabber);
	}
	virtual void GetImage() = 0;
		
	virtual void Stop() = 0;

	virtual void StoreImage(size_t id, ImgType img) = 0;

	ImgTypePtr FetchImage(size_t id)
	{
		return img_stash_[id].wait_and_pop();
	}
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