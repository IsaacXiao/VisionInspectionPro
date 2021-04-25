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
	USHORT camera_id_;
	std::weak_ptr<IMediator> mediator_;
public:
    ICameraGrabber(const STRING & cfg):cfg_(cfg){}
    virtual ~ICameraGrabber(){}
	void AttachMediator(std::weak_ptr<IMediator> mediator) { mediator_ = mediator;  }
	bool IsStoped() const { return stop_; }
	virtual void OpenDevice() = 0;
	virtual void CloseDevice() = 0;
	virtual void StartGrabbing() = 0;
	virtual void StopGrabbing() = 0;
	virtual void SoftTrigger() = 0;
	virtual void SetId(USHORT id) = 0;
	virtual float GetFloatValue(const char* what) const = 0;
	virtual void SetFloatValue(const char* what, float fValue) = 0;
	virtual UINT GetIntValue(const char* what) const = 0;
	virtual void SetIntValue(const char* what, UINT iValue) = 0;
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
