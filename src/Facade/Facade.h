#ifndef FACADE_HEAD_H
#define FACADE_HEAD_H

#include "FrameBuilder.h"
#include "../Mediator/Mediator.hpp"
#include <utility>
#include <queue>
#include <QImage>

#include "CameraShot.h"

class Facade
{
	using MediatorPtr = PointType<Mediator<QImage,std::queue<QImage>>>::Ptr;
private:
    FrameBuilder builder_;
	MediatorPtr  img_manager_;
public:
    Facade()
	{ 
		//builder_.InitModule();
		img_manager_ = std::make_unique<Mediator<QImage, std::queue<QImage>>>();
	}

	///这里不做资源释放
	///如果用户没有手动点击停止
	///让操作系统去自动释放
	//~Facade() 
	//{ 
	//	Stop();  
	//}

	template<typename... Ts>
	void Run(Ts&&... params)
	{
		//builder_.BuildInspectionSystem();
		//builder_.Part<CAMERAGRABBER>()->StartLive(std::forward<Ts>(params)...);

		//这个ui控件来自UI
		//在此处开线程去获取img
		CameraShot* shot_wnd = new CameraShot;
		auto img_queue = img_manager_->GetImage();

		auto img_raw = img_queue.front();
		QImage image_scale = img_raw.scaled(shot_wnd->width(), shot_wnd->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
		shot_wnd->setBackImage(image_scale);
		shot_wnd->show();

		while (!img_queue.empty())
		{
			auto img_raw = img_queue.front();
			img_queue.pop();
			QImage image_scale = img_raw.scaled(shot_wnd->width(), shot_wnd->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
			shot_wnd->setBackImage(image_scale);
			shot_wnd->update();
		}
	}

	void Stop() 
	{
		//builder_.Part<CAMERAGRABBER>()->StopLive();
		//builder_.DestructModule();
	}
};

template<>
struct PointType<Facade>
{
	using Ptr = std::unique_ptr<Facade>;
};

#endif 