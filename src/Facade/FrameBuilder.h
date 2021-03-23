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
	using CameraGrabberFactory = ModuleFactory<CameraGrabberOrg,CameraGrabberPtr>;
	using PlcAgentFactory = ModuleFactory<PlcAgentOrg,PlcAgentPtr>;
	using SystemFrame = std::tuple<CameraGrabberPtr,PlcAgentPtr>;
private:
	SystemFrame inspection_;

	Configure<FRAMWORK_PART::MAIN> main_cfg_{ GetModuleDirectory() + PathSeparator() + "Main.cfg" };
	//m表示module
	CameraGrabberFactory m_camera_grabber_;
	PlcAgentFactory m_plc_agent_;
	
	//void ConstructPlcAgent() { std::get<PLCAGENT>(inspection_) = m_plc_agent_.Create(main_cfg_.Param()["PlcAgent"]); }
	void ConstructCameraGrabber() { std::get<CAMERAGRABBER>(inspection_) = m_camera_grabber_.Create(main_cfg_.Param()["CameraGrabber"]); }
public:
    FrameBuilder();

	template<FRAMWORK_PART module>
	constexpr auto Part()
	{
		return std::get<module>(inspection_);
	}

	void InitModule();
	void BuildInspectionSystem();
	void DestructModule();

    ~FrameBuilder(){};
};

template<>
struct PointType<FrameBuilder>
{
	using Org = FrameBuilder*;
	using Ptr = std::shared_ptr<FrameBuilder>;
};

using FrameBuilderOrg = PointType<FrameBuilder>::Org;
using FrameBuilderPtr = PointType<FrameBuilder>::Ptr;

#endif 