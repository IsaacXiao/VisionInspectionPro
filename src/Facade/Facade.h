#ifndef FACADE_HEAD_H
#define FACADE_HEAD_H

#include "FrameBuilder.h"
#include <utility>
#include <queue>
#include <QImage>

#include "CameraShot.h"
#include "../Mediator/IMediator.h"

class Facade
{
private:
	FrameBuilderPtr builder_;
	MediatorPtr control_center_;
public:
    Facade()
	{ 
		builder_ = std::make_unique<FrameBuilder>();
		builder_->InitModule();
	}

	///这里不做资源释放
	///如果用户没有手动点击停止
	///让操作系统去自动释放
	//~Facade() 
	//{ 
	//
	//}

	template<typename... Ts>
	void Run(Ts&&... params)
	{
		builder_->BuildInspectionSystem();
		//builder_->Part<CAMERAGRABBER>()->StartLive(std::forward<Ts>(params)...);
		control_center_ = builder_->Part<MEDIATOR>();
		//builder_->Part<CAMERAGRABBER>()->StartGrabbing();
		control_center_->Do();
	}

	void Stop() 
	{
		control_center_->Stop();
	}

	ImgTypePtr SoftTriggerGrab()
	{
		assert(!builder_->Part<CAMERAGRABBER>()->IsStoped());
		builder_->Part<CAMERAGRABBER>()->SoftTrigger();
		return control_center_->FetchImage();
	}

	ImgTypePtr PlcTriggerGrab()
	{
		assert(!builder_->Part<CAMERAGRABBER>()->IsStoped());
		return control_center_->FetchImage();
	}
};

template<>
struct PointType<Facade>
{
	using Org = Facade*;
	using Ptr = std::unique_ptr<Facade>;
};

using FacadePtr = PointType<Facade>::Ptr;

#endif 