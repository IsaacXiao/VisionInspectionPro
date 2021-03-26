#ifndef IMEDIATOR_H
#define IMEDIATOR_H

#include "ThreadSafe_Queue.hpp"
#include "CommonInclude/TypeDefine.h"
#include "Configure/Configure.hpp"
#include <memory>
#include "opencv2/opencv.hpp"

class IMediator
{
	using ImgType = cv::Mat;
	using StorageType = ThreadSafe_Queue<ImgType>;
private:
	StorageType img_stash_;
protected:
	Configure<FRAMWORK_PART::MEDIATOR> cfg_;
public:
	IMediator(const STRING & cfg):cfg_(cfg)
	{
	        
	}
	virtual ~IMediator(){}

	void Do()
	{
		//实际上是用相机指针调用这个函数
		//1. GetImage();
		/*threadpool executor{ 1 };
		ICameraGrabber * camera = new DMKCamera;
		std::future<void> res = executor.commit(std::bind(&ICameraGrabber::GetImage, camera));*/
		//2. BroadCastSend();
		
		//DisplayImage(/*尽量不要传ui*/);
		//SaveImage(const STRING& path)
		//InspectImage(alg) XinXing的代码里，算法函数依赖具体的相机，可以把算法函数作为相机的类成员
	}

	void FetchImage(ImgType img)
	{
		img_stash_.push(img);
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