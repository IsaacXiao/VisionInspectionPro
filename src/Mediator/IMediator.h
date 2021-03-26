#ifndef IMEDIATOR_H
#define IMEDIATOR_H

#include "ThreadSafe_Queue.hpp"
#include "CommonInclude/TypeDefine.h"
#include <memory>


class IMediator
{
	//TODO: 把int替换成cv::mat类型
	using StorageType = ThreadSafe_Queue<int>;
private:
	
public:
	StorageType img_stash_;
	IMediator()
	{
	        
	}
	virtual ~IMediator(){}

	void Do()
	{
		//实际上是用相机指针调用这个函数
		//GetImage();
		//DisplayImage();
		//BroadCastSend();
		//SaveImage
		//InspectImage
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