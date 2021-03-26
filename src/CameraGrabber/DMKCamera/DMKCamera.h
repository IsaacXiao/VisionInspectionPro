#ifndef DMK_CAMERA_H
#define DMK_CAMERA_H

#include "../ICameraGrabber.h"
#include "CommonInclude/PlatFormHead.h"
#include "Logger/BroadCastLogger.hpp"

#include "tisudshl.h"

#include "CommonInclude/Memory.hpp"
#include "CommonInclude/TypeDefine.h"

#include <windows.h>
#include <memory>

#include "udshl/FrameHandlerSink.h"
//#include "VCDPropertyDef.h"
#include "udshl/VCDPropertyID.h"

using namespace _DSHOWLIB_NAMESPACE;

namespace
{
	//TODO: 等文本日志加入后验证是否真的释放了资源，or程序结束操作系统自动释放资源
	void del_grab(DShowLib::Grabber* grabber)
	{
		if (grabber->isLive())
		{
			grabber->stopLive();
			grabber->closeDev();
		}

		GlobalLogger::Record("DShowLib::Grabber", LOG_LEVEL::TRACK, "camera device closed, now destroying");
		DeletePtr(grabber);
	};
	auto CreateGrabber()
	{
		std::unique_ptr<DShowLib::Grabber, decltype(&del_grab)> grabber(new DShowLib::Grabber(), &del_grab);
		return grabber;
	}
}

template<>
struct PointType<DShowLib::Grabber>
{
	using Org = DShowLib::Grabber*;
	using Ptr = std::unique_ptr<DShowLib::Grabber, decltype(&del_grab)>;
};

class DMKCamera : public ICameraGrabber
{
	using GrabberPtr = PointType<DShowLib::Grabber>::Ptr;
	struct CameraListener : public DShowLib::GrabberListener
	{
		MediatorPtr mediator_;
		virtual void frameReady(DShowLib::Grabber& caller, smart_ptr<DShowLib::MemBuffer> pBuffer, DWORD FrameNumber) override
		{
			cv::Mat img(caller.getAcqSizeMaxY(), caller.getAcqSizeMaxX(), CV_8UC3, (BYTE*)pBuffer->getPtr());
			mediator_->FetchImage(img.clone());
		}
	};

private:
	GrabberPtr grabber_;
	CameraListener	 listener_;
	tFrameHandlerSinkPtr sink_;
	tIVCDPropertyItemsPtr			property_;
	tIVCDSwitchPropertyPtr			triggerswitch_;  //触发开关
	tIVCDButtonPropertyPtr			softtrigger_;    //软件触发
	tIVCDPropertyInterfacePtr		property_interface_;
	STRING which_{"test"};
public:
	DMKCamera(const STRING & cfg);
	~DMKCamera();
	static const char* Name() { return "DMKCamera"; }
	virtual const STRING& Id() override { return Name(); }
	void InitSettings();
	virtual void SoftTrigger() override { assert(IsNull(softtrigger_)); softtrigger_->push(); }
	virtual void AttachMediator(MediatorPtr mediator) { listener_.mediator_ = mediator; }
};

#endif
