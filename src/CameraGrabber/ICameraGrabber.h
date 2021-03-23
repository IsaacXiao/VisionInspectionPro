#ifndef ICAMERA_GRABBER_H
#define ICAMERA_GRABBER_H

#include "CommonInclude/TypeDefine.h"
#include <memory>

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

template<>
struct PointType<ICameraGrabber>
{
	using Org = ICameraGrabber*;
	using Ptr = std::shared_ptr<ICameraGrabber>;
};

using CameraGrabberOrg = PointType<ICameraGrabber>::Org;
using CameraGrabberPtr = PointType<ICameraGrabber>::Ptr;

#endif
