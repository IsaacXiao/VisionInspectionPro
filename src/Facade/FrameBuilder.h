#ifndef FRAME_BUILDER_H
#define FRAME_BUILDER_H

#include "CommonInclude/TypeDefine.h"
#include "CommonInclude/PlatFormHead.h"

#include "Configure/Configure.hpp"
#include "ModuleFactory.hpp"

#include "../CameraGrabber/ICameraGrabber.h"
#include "../PlcAgent/IPlcAgent.h"
#include <tuple>

class FrameBuilder
{
	using CameraGrabberFactory = ModuleFactory<CameraGrabberPtr>;
	using PlcAgentFactory = ModuleFactory<PlcAgentPtr>;
private:
	Configure<FRAMWORK_PART::MAIN> main_cfg_{ GetModuleDirectory() + PathSeparator() + "Main.cfg" };
	//m表示module
	CameraGrabberFactory m_camera_grabber_;
	PlcAgentFactory m_plc_agent_;
	
public:
    FrameBuilder();

	PlcAgentPtr ConstructPlcAgent() { return m_plc_agent_.Create(main_cfg_.Param()["PlcAgent"]); }
	CameraGrabberPtr ConstructCameraGrabber() { return m_camera_grabber_.Create(main_cfg_.Param()["CameraGrabber"]); }

	void InitModule();


    ~FrameBuilder(){};
};

#endif 