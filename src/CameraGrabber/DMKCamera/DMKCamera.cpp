// DMKCamera.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "DMKCamera.h"
#include "CommonInclude/TypeDefine.h"
#include "Logger/BroadCastLogger.hpp"

DMKCamera::DMKCamera(const STRING & cfg):
	ICameraGrabber(cfg), grabber_(CreateGrabber())
{
	DShowLib::InitLibrary();
}

DMKCamera::~DMKCamera()
{
	StopGrabbing();
	DShowLib::ExitLibrary();
}

void DMKCamera::InitSettings()
{
	listener_.camera_id_ = camera_id_;
	listener_.mediator_ = mediator_;
	bool is_multicolour = StrToBool(cfg_.Param()["is_multicolour"]);
	listener_.is_multicolour_ = is_multicolour;
	const STRING cfg = "camera" + to_string(camera_id_) + ".xml";
	if (!grabber_->loadDeviceStateFromFile(cfg))
	{
		while(!grabber_->showDevicePage());
		
		grabber_->saveDeviceStateToFile(cfg);
	}
	
	//黑白eY800，彩色eRGB24
	sink_ = FrameHandlerSink::create( is_multicolour ? eRGB24 : eY800, 1 );
	sink_->setSnapMode(false);
	grabber_->setSinkType(sink_);
	
	property_ = grabber_->getAvailableVCDProperties();

	if (!IsNull(property_) && (property_interface_ = property_->findInterface(VCDID_TriggerMode, VCDElement_Value, VCDInterface_Switch)) != 0)
	{
		property_interface_->QueryInterface(triggerswitch_);
		triggerswitch_->setSwitch(true);
	}//触发开关 end

	if (!IsNull(property_) && (property_interface_ = property_->findInterface(VCDID_TriggerMode, VCDElement_SoftwareTrigger, VCDInterface_Button)) != 0)
	{
		property_interface_->QueryInterface(softtrigger_);
	}//软件触发
}

void DMKCamera::StartGrabbing()
{
	InitSettings();
	stop_ = false;
	grabber_->addListener(&listener_, GrabberListener::eFRAMEREADY);//注册回调
	grabber_->startLive(false);
}

void DMKCamera::StopGrabbing()
{
	if (grabber_->isLive())
	{
		grabber_->stopLive();
	}
	stop_ = true;
	grabber_->removeListener(&listener_, DShowLib::GrabberListener::eFRAMEREADY);
}



