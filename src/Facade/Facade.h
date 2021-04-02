#ifndef FACADE_HEAD_H
#define FACADE_HEAD_H

#include "FrameBuilder.h"
#include <utility>
#include "../Mediator/IMediator.h"

#include "../UI/IForDisplay.h"


///这个Facade代表应用程序的所有功能
///不依赖任何第三方库的UI类
///不论QT还是MFC或是其他界面类
///只需拿过来继承自IForDisplay
///重写DisplayImage函数即可显示
class Facade 
{
private:
	FrameBuilderPtr builder_;
	IForDisplay * ui_;
public:
    Facade()
	{ 
		builder_ = std::make_unique<FrameBuilder>();
		builder_->InitModule();
	}
	~Facade() { Stop();  }

	void AttachUI(IForDisplay * ui) { ui_ = ui;  }
	void DisplayImage(USHORT camera_id, ImgTypePtr img)
	{
		ui_->DisplayImage(camera_id, img);
	}

	MediatorPtr Dispatcher() const { return builder_->Part<MEDIATOR>(); }

	/*template<typename... Ts>
	void Run(Ts&&... params)
	{
	//builder_->Part<CAMERAGRABBER>()->StartLive(std::forward<Ts>(params)...);
	}*/

	void ReloadCfg() 
	{ 
		builder_->BuildInspectionSystem(); 
		builder_->Part<MEDIATOR>()->AttachFacade(this);
	}

	void Run()
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

	void SoftTriggerGrab( USHORT camera_id ) const
	{
		builder_->Part<CAMERAGRABBER>()[camera_id]->SoftTrigger();
	}
};

//template<>
//struct PointType<Facade>
//{
//	using Org = Facade*;
//	using Ptr = std::unique_ptr<Facade>;
//};

using FacadePtr = PointType<Facade>::Ptr;

#endif 