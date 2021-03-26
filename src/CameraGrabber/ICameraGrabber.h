#ifndef ICAMERA_GRABBER_H
#define ICAMERA_GRABBER_H

#include "CommonInclude/TypeDefine.h"
#include <memory>
#include "../Mediator/IMediator.h"
#include "Configure/Configure.hpp"
#include "opencv2/opencv.hpp"

class ICameraGrabber
{
private:

protected:
	bool stop_{ false };
	Configure<FRAMWORK_PART::CAMERAGRABBER> cfg_;
public:
    ICameraGrabber(const STRING & cfg):cfg_(cfg){}
    virtual ~ICameraGrabber(){}
	bool IsStoped() const { return stop_; }
	void StopGrabbing() { stop_ = true; }
	virtual const STRING& Id() = 0;
	virtual void SoftTrigger() = 0;
	virtual void AttachMediator(MediatorPtr mediator) = 0;
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
