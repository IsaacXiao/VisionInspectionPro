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

#include "../../Mediator/IMediator.h"

#include "CommonInclude/InspectException.h"


using namespace _DSHOWLIB_NAMESPACE;

namespace
{
	//TODO: ���ı���־�������֤�Ƿ�����ͷ�����Դ��or�����������ϵͳ�Զ��ͷ���Դ
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

		virtual void frameReady(DShowLib::Grabber& caller, smart_ptr<DShowLib::MemBuffer> pBuffer, DWORD FrameNumber) override
		{
			auto img = ImgTypeOrg(caller.getAcqSizeMaxY(), caller.getAcqSizeMaxX(), CV_8UC3, (BYTE*)pBuffer->getPtr());
			mediator_.lock()->StoreImage(camera_id_, std::move(img));
		}
	};

private:
	GrabberPtr grabber_;
	CameraListener	 listener_;
	tFrameHandlerSinkPtr sink_;
	tIVCDPropertyItemsPtr			property_;
	tIVCDSwitchPropertyPtr			triggerswitch_;  //��������
	tIVCDButtonPropertyPtr			softtrigger_;    //�������
	tIVCDPropertyInterfacePtr		property_interface_;
	STRING which_{"test"};	//TODO: ��д����test�����ɿ����
public:
	DMKCamera(const STRING & cfg);
	~DMKCamera();
	static const char* Name() { return "DMKCamera"; }
	void InitSettings();
	virtual void StartGrabbing() override;
	virtual void StopGrabbing() override;
	virtual void AttachMediator(std::weak_ptr<IMediator> mediator) override
	{
		
		listener_.mediator_ = mediator;
	}
	virtual void SoftTrigger() override 
	{ 
		assert(IsStoped());
		assert(!IsNull(softtrigger_)); 
		softtrigger_->push();
	}
};

#endif
