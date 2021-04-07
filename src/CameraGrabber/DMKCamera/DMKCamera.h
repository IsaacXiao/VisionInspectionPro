#ifndef DMK_CAMERA_H
#define DMK_CAMERA_H


#include "../ICameraGrabber.h"
#include "CommonInclude/PlatFormHead.h"
#include "Logger/BroadCastLogger.hpp"

#include "tisudshl.h"

#include "CommonInclude/Memory.hpp"
#include "CommonInclude/TypeDefine.h"

#include <memory>

#include "udshl/FrameHandlerSink.h"
//#include "VCDPropertyDef.h"
#include "udshl/VCDPropertyID.h"

#include "../../Mediator/IMediator.h"

#include "CommonInclude/InspectException.h"
#include "CommonInclude/utility.hpp"


using namespace _DSHOWLIB_NAMESPACE;

namespace
{
	void del_grab(DShowLib::Grabber* grabber)
	{
		grabber->closeDev();
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
		std::weak_ptr<IMediator> mediator_;
		size_t camera_id_;
		bool is_multicolour_{true};

		virtual void frameReady(DShowLib::Grabber& caller, smart_ptr<DShowLib::MemBuffer> pBuffer, DWORD FrameNumber) override
		{
			//黑白CV_8UC1，彩色CV_8UC3
			auto img = ImgTypeOrg(caller.getAcqSizeMaxY(), caller.getAcqSizeMaxX(), is_multicolour_ ? CV_8UC3: CV_8UC1, (BYTE*)pBuffer->getPtr());
			mediator_.lock()->StoreImage(camera_id_, std::move(img));
		}
	};

private:
	GrabberPtr grabber_;
	CameraListener	 listener_;
	tFrameHandlerSinkPtr sink_{nullptr};
	tIVCDPropertyItemsPtr			property_{ nullptr };
	tIVCDSwitchPropertyPtr			triggerswitch_{ nullptr };  //触发开关
	tIVCDButtonPropertyPtr			softtrigger_{ nullptr };    //软件触发
	tIVCDPropertyInterfacePtr		property_interface_{ nullptr };
	STRING which_{"test"};	//TODO: 先写死了test再做成可配的
public:
	DMKCamera(const STRING & cfg);
	~DMKCamera();
	static const char* Name() { return "DMKCamera"; }
	void InitSettings();
	virtual void StartGrabbing() override;
	virtual void StopGrabbing() override;
	virtual void SoftTrigger() override { assert(!IsNull(softtrigger_)); softtrigger_->push(); }
};

#endif
