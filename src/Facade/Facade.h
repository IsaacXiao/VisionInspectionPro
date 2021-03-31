#ifndef FACADE_HEAD_H
#define FACADE_HEAD_H

#include "FrameBuilder.h"
#include <utility>
#include <queue>
#include <QObject>
#include "CameraShot.h"
#include "../Mediator/IMediator.h"

#include "CommonInclude/thread_pool.h"

class Facade : public QObject
{
	Q_OBJECT
private:
	FrameBuilderPtr builder_;
	MediatorPtr consumer_;
	threadpool executor_{ 2 };
signals:
	void SigChangeBack(unsigned short, ImgTypePtr);	//信号函数不需要实现
public:
    Facade()
	{ 
		builder_ = std::make_unique<FrameBuilder>();
		builder_->InitModule();
		qRegisterMetaType<ImgTypePtr>("ImgTypePtr");
	}

	///这里不做资源释放
	///如果用户没有手动点击停止
	///让操作系统去自动释放
	//~Facade() 
	//{ 
	//
	//}

	/*template<typename... Ts>
	void Run(Ts&&... params)
	{
		//builder_->Part<CAMERAGRABBER>()->StartLive(std::forward<Ts>(params)...);
	}*/

	void DisplayImg( unsigned short n )
	{
		ImgTypePtr img = consumer_->FetchImage(n);
		emit SigChangeBack(n, img);
	}

	void Run()
	{
		builder_->BuildInspectionSystem();
		consumer_ = builder_->Part<MEDIATOR>();
		consumer_->GetImage();
		
		for (unsigned short i = 0; i < builder_->Number(); i++ )
		{
			executor_.commit(std::bind(&Facade::DisplayImg, this,i));
		}
	}

	void Stop() 
	{
		consumer_->Stop();
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