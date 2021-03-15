#ifndef DMK_CAMERA_H
#define DMK_CAMERA_H

#include "../ICameraGrabber.h"
#include "Configure/Configure.hpp"
#include "CommonInclude/PlatFormHead.h"
#include "Logger/BroadCastLogger.hpp"

#include "tisudshl.h"

#include "CommonInclude/Memory.hpp"

#include <windows.h>

class DMKCamera : public ICameraGrabber
{
private:
	Configure<FRAMWORK_PART::CAMERAGRABBER> dmk_cfg_;
	DShowLib::Grabber* grabber_;
public:
	DMKCamera(const STRING & cfg);
	~DMKCamera();
	static const char* Name()
	{
		return "DMKCamera";
	}
	void InitCamera();
	void DisplayImg(HWND where,UINT width,UINT height) override;
};

#endif
