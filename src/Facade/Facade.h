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
///因为没有计划让别的编程语言来调用这个Facade
///就不把这个类做到Dll或者So中去了 
class Facade 
{
private:
	FrameBuilderPtr system_{nullptr};
	IForDisplay* ui_{nullptr};
public:
	Facade();

	void AttachUI(IForDisplay * ui) { ui_ = ui;  }
	void DisplayImage(USHORT camera_id, ImgTypePtr img){ ui_->DisplayImage(camera_id, img); }

	/*如果界面显示无法和下层的类解耦合
	只能这样用可变长模板参数拖着几个QLable窗口句柄往下层的几个Camera里传过去
	template<typename... Ts>
	void Run(Ts&&... params)
	{
		//system_->Part<CAMERAGRABBER>()->StartLive(std::forward<Ts>(params)...);
	}*/
	void Run();

	void ReloadCfg();

	void Stop() const;

	void SoftTriggerGrab(USHORT camera_id) const;

	void CameraOffline(USHORT camera_id) const
	{
		if (!system_->Part<CAMERAGRABBER>()[camera_id]->IsStoped())
		{
			//Stop();界面通知用户去点击停止，不要在这里调用，怕线程池重复释放资源会出稀奇
		}
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