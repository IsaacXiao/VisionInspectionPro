#ifndef FRAME_BUILDER_H
#define FRAME_BUILDER_H

#include "CommonInclude/TypeDefine.h"
#include "CommonInclude/PlatFormHead.h"

#include "Configure/Configure.hpp"
#include "ModuleFactory.hpp"

#include "../CameraGrabber/ICameraGrabber.h"
#include "../PlcAgent/IPlcAgent.h"
#include "../Mediator/IMediator.h"
#include <tuple>
#include <vector>

class FrameBuilder
{
	using CameraGrabberFactory = ModuleFactory<CameraGrabberOrg,CameraGrabberPtr>;
	using PlcAgentFactory = ModuleFactory<PlcAgentOrg,PlcAgentPtr>;
	using MediatorFactory = ModuleFactory<MediatorOrg, MediatorPtr>;
	using CameraGroup = VECTOR<CameraGrabberPtr>;
	using SystemFrame = std::tuple<CameraGroup,PlcAgentPtr,MediatorPtr>;
private:
	SystemFrame inspection_;
	USHORT camera_number_;

	Configure<FRAMWORK_PART::MAIN> main_cfg_{ GetModuleDirectory() + PathSeparator() + "Main.cfg" };
	//m表示module
	CameraGrabberFactory m_camera_grabber_;
	PlcAgentFactory m_plc_agent_;
	MediatorFactory m_mediator_;
	
	///等号会使智能指针第一次参与构造，后面的赋值操作会把之前的持有对象释放
	//void ConstructPlcAgent() { std::get<PLCAGENT>(inspection_) = m_plc_agent_.Create(main_cfg_.Param()["PlcAgent"]); }
	void ConstructMediator() { std::get<MEDIATOR>(inspection_) = m_mediator_.Create(main_cfg_.Param()["Mediator"]); }
	void ConstructCameraGrabber();

protected:

public:
    FrameBuilder();
	template<FRAMWORK_PART module>
	constexpr auto Part() const
	{
		return std::get<module>(inspection_);
	}

	unsigned short CameraNumber() const { return camera_number_;  }

	void InitModule();
	void BuildInspectionSystem();


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