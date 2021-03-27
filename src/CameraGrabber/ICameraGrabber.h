#ifndef ICAMERA_GRABBER_H
#define ICAMERA_GRABBER_H

#include "CommonInclude/TypeDefine.h"
#include <memory>
//#include "../Mediator/IMediator.h"
#include "Configure/Configure.hpp"

class IMediator;

class ICameraGrabber
{
private:

protected:
	bool stop_{ true };
	Configure<FRAMWORK_PART::CAMERAGRABBER> cfg_;
	std::weak_ptr<IMediator> mediator_;
	void AttachMediator(std::weak_ptr<IMediator> mediator) { mediator_ = mediator; }
public:
    ICameraGrabber(const STRING & cfg):cfg_(cfg){}
    virtual ~ICameraGrabber(){}
	bool IsStoped() const { return stop_; }
	virtual void StartGrabbing() = 0;
	virtual void StopGrabbing() = 0;
	virtual const STRING& Id() = 0;
	virtual void SoftTrigger() = 0;
	virtual void PlcTrigger() = 0;
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
