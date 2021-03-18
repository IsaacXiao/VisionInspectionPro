#ifndef DMK_CAMERA_H
#define DMK_CAMERA_H

#include "../ICameraGrabber.h"
#include "Configure/Configure.hpp"
#include "CommonInclude/PlatFormHead.h"
#include "Logger/BroadCastLogger.hpp"

#include "tisudshl.h"

#include "CommonInclude/Memory.hpp"

#include <windows.h>
#include <memory>

namespace
{
	//TODO: 有待验证是否真的释放了资源，or程序结束操作系统自动释放资源
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

class DMKCamera : public ICameraGrabber
{
private:
	Configure<FRAMWORK_PART::CAMERAGRABBER> dmk_cfg_;
	std::unique_ptr<DShowLib::Grabber, decltype(&del_grab)> grabber_;
public:
	DMKCamera(const STRING & cfg);
	static const char* Name()
	{
		return "DMKCamera";
	}
	void StartLive(HWND where,UINT width,UINT height) override;
	void StopLive() { assert(grabber_->stopLive());  }
	const STRING& Id() { return Name(); }
};

#endif
