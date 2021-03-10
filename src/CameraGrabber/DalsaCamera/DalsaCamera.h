#ifndef DALSA_CAMERA_H
#define DALSA_CAMERA_H

#include "../ICameraGrabber.h"
#include "Configure/Configure.hpp"
#include "CommonInclude/PlatFormHead.h"

class DalsaCamera : public ICameraGrabber
{
private:
    Configure<FRAMWORK_PART::CAMERAGRABBER> dalsa_cfg_;
public:
    DalsaCamera(STRING && cfg);
    ~DalsaCamera();
	static const char* Name()
    {		
		return "DalsaCamera";
	}
};

#endif