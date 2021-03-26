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
	DShowLib::ExitLibrary();
}

void DMKCamera::InitSettings()
{
	const STRING cfg = "camera" + which_ + ".xml";

	if (!grabber_->loadDeviceStateFromFile(cfg))
	{
		grabber_->showDevicePage();
		grabber_->saveDeviceStateToFile(cfg);
	}
	
	sink_ = FrameHandlerSink::create(eRGB24, 1); //  eRGB24
												   //m_pSink = FrameHandlerSink::create(eY800, 1);
	sink_->setSnapMode(false);
	grabber_->setSinkType(sink_);
	grabber_->startLive(false);
	property_ = grabber_->getAvailableVCDProperties();

	if (!IsNull(property_) && (property_interface_ = property_->findInterface(VCDID_TriggerMode, VCDElement_Value, VCDInterface_Switch)) != 0)
	{
		property_interface_->QueryInterface(triggerswitch_);
		triggerswitch_->setSwitch(true);
	}//�������� end


	if (!IsNull(property_) && (property_interface_ = property_->findInterface(VCDID_TriggerMode, VCDElement_SoftwareTrigger, VCDInterface_Button)) != 0)
	{
		property_interface_->QueryInterface(softtrigger_);
	}//�������
}



