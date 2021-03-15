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
	virtual void DisplayImg(HWND where, UINT width, UINT height) = 0;
};


using CameraGrabberPtr = PointType<ICameraGrabber>::Ptr;

#endif
