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
	virtual void InitCamera() = 0;
};


using CameraGrabberPtr = PointType<ICameraGrabber>::Ptr;

#endif
