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
	
	/// 等号会使std::shared_ptr第一次参与构造
	/// 而后面再运行=则是赋值操作，会把之前的持有对象释放
	/// 这样管理资源恰好符合用户的操作习惯
	/// 每次配置文件修改之后再次运行
	/// 就像图书馆借书看完后还想再看另外一本之前
	/// 先把之前的归还再借新的去
	//void ConstructPlcAgent() { std::get<PLCAGENT>(inspection_) = m_plc_agent_.Create(main_cfg_.Param()["PlcAgent"]); }
	void ConstructMediator() { std::get<MEDIATOR>(inspection_) = m_mediator_.Create(main_cfg_.Param()["Mediator"]); }
	void ConstructCameraGrabber();

protected:

public:
    FrameBuilder();
	//TODO：做成下标操作符可读性更好
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