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
private:
	FrameBuilderPtr builder_;
	MediatorPtr control_center_;
signals:
	void SigChangeBack(ImgTypePtr);	//信号函数不需要实现
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

	/*template<typename... Ts>
	void Run(Ts&&... params)
	{
		//builder_->Part<CAMERAGRABBER>()->StartLive(std::forward<Ts>(params)...);
	}*/


	void Run()
	{
		builder_->BuildInspectionSystem();
		control_center_ = builder_->Part<MEDIATOR>();
		control_center_->GetImage();
		ImgTypePtr img = control_center_->FetchImage();
		emit SigChangeBack(img);
		//while (true/*!builder_->Part<CAMERAGRABBER>()->IsStoped()*/)
		//{
		//	ImgTypePtr img = control_center_->FetchImage();
		//	emit SigChangeBack(img);
		//}
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

/*template<>
struct PointType<Facade>
{
	using Org = Facade*;
	using Ptr = std::unique_ptr<Facade>;
};*/

using FacadePtr = PointType<Facade>::Ptr;

#endif 