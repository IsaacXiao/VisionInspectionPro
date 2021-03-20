#ifndef ICAMERA_GRABBER_H
#define ICAMERA_GRABBER_H

#include "CommonInclude/TypeDefine.h"

class ICameraGrabber
{
private:
    /* data */
public:
    ICameraGrabber(/* args */){}
    virtual ~ICameraGrabber(){}
	virtual void StartLive(HWND where) = 0;
	virtual void StopLive() = 0;
	virtual const STRING& Id() = 0;
};


using CameraGrabberPtr = PointType<ICameraGrabber>::Ptr;

#endif
