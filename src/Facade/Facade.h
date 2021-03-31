#ifndef FACADE_HEAD_H
#define FACADE_HEAD_H

#include "FrameBuilder.h"
#include <utility>
#include <queue>
#include <QObject>
#include "CameraShot.h"
#include "../Mediator/IMediator.h"

class Facade : public QObject
{
	Q_OBJECT
signals :
	void SigChangeBack(unsigned short, ImgTypePtr) const;
private:
	FrameBuilderPtr builder_;

	void DisplayImg(USHORT n) const
	{
		while (!builder_->Part<CAMERAGRABBER>()[n]->IsStoped)
		{
			ImgTypePtr img = builder_->Part<MEDIATOR>()->FetchImage(n);
			emit SigChangeBack(n, img);
		}
	}
public:
    Facade()
	{ 
		builder_ = std::make_unique<FrameBuilder>();
		builder_->InitModule();
	}

	/*template<typename... Ts>
	void Run(Ts&&... params)
	{
	//builder_->Part<CAMERAGRABBER>()->StartLive(std::forward<Ts>(params)...);
	}*/

	void Run() const
	{
		builder_->BuildInspectionSystem();
		
		for ( USHORT i = 0; i < builder_->CameraNumber(); i++ )
		{
			builder_->Part<CAMERAGRABBER>()[i]->StartGrabbing();
			DisplayImg(i);
			//builder_->Part<MEDIATOR>()->
			//executor_.commit(std::bind(&Facade::DisplayImg, this, i));
		}
	}

	void Stop()  const
	{
		for (auto & camera : builder_->Part<CAMERAGRABBER>())
		{
			camera->StopGrabbing();
		}
	}

	ImgTypePtr SoftTriggerGrab()
	{
		//assert(!builder_->Part<CAMERAGRABBER>()->IsStoped());
		//builder_->Part<CAMERAGRABBER>()->SoftTrigger();
		//return consumer_->FetchImage();
	}

	ImgTypePtr PlcTriggerGrab()
	{
		assert(!builder_->Part<CAMERAGRABBER>()->IsStoped());
		//return consumer_->FetchImage();
	}
};

/*template<>
struct PointType<Facade>
{
	using Org = Facade*;
	using Ptr = std::unique_ptr<Facade>;
};*/

using FacadePtr = PointType<Facade>::Ptr;

#endif 