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
};


using CameraGrabberPtr = PointType<ICameraGrabber>::Ptr;

#endif
