#ifndef FACADE_HEAD_H
#define FACADE_HEAD_H

#include "FrameBuilder.h"
#include <utility>
#include <queue>
#include <QObject>
#include "CameraShot.h"
#include "../Mediator/IMediator.h"

class Facade 
{
private:
	FrameBuilderPtr builder_;
public:
    Facade()
	{ 
		builder_ = std::make_unique<FrameBuilder>();
		builder_->InitModule();
	}

	MediatorPtr Dispatcher() const { return builder_->Part<MEDIATOR>(); }

	/*template<typename... Ts>
	void Run(Ts&&... params)
	{
	//builder_->Part<CAMERAGRABBER>()->StartLive(std::forward<Ts>(params)...);
	}*/

	void BuildSystem() { builder_->BuildInspectionSystem(); }

	void Run() const
	{
		builder_->Part<MEDIATOR>()->StartDispatch();
		for ( USHORT camera_id = 0; camera_id < builder_->CameraNumber(); camera_id++ )
		{
			builder_->Part<CAMERAGRABBER>()[camera_id]->StartGrabbing();
			builder_->Part<MEDIATOR>()->FetchImgToWork(camera_id);
		}
	}

	void Stop()  const
	{
		for (auto & camera : builder_->Part<CAMERAGRABBER>())
		{
			camera->StopGrabbing();
		}
		builder_->Part<MEDIATOR>()->StopDispatch();
	}

	ImgTypePtr SoftTriggerGrab()
	{
		//assert(!builder_->Part<CAMERAGRABBER>()->IsStoped());
		//builder_->Part<CAMERAGRABBER>()->SoftTrigger();
		//return consumer_->FetchImage();
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