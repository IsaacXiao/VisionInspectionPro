#ifndef DMK_CAMERA_H
#define DMK_CAMERA_H

#include "../ICameraGrabber.h"
#include "Configure/Configure.hpp"
#include "CommonInclude/PlatFormHead.h"
#include "Logger/BroadCastLogger.hpp"

#include "tisudshl.h"

#include "CommonInclude/Memory.hpp"
#include "CommonInclude/TypeDefine.h"

#include <windows.h>
#include <memory>

namespace
{
	//TODO: 等文本日志加入后验证是否真的释放了资源，or程序结束操作系统自动释放资源
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
	using Ptr = std::unique_ptr<DShowLib::Grabber, decltype(&del_grab)>;
};

class DMKCamera : public ICameraGrabber
{
	using GrabberPtr = PointType<DShowLib::Grabber>::Ptr;
private:
	Configure<FRAMWORK_PART::CAMERAGRABBER> dmk_cfg_;
	GrabberPtr grabber_;
public:
	DMKCamera(const STRING & cfg);
	static const char* Name()
	{
		return "DMKCamera";
	}
	void StartLive(HWND where) override;
	void StopLive() { assert(grabber_->stopLive());  }
	const STRING& Id() { return Name(); }
};

#endif
