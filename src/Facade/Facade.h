#ifndef FACADE_HEAD_H
#define FACADE_HEAD_H

#include "CommonInclude/TypeDefine.h"
#include "CommonInclude/PlatFormHead.h"

#include "Configure/Configure.hpp"
#include "ModuleFactory.hpp"

#include "../CameraGrabber/ICameraGrabber.h"
#include "../PlcAgent/IPlcAgent.h"

//TODO: 去掉FrameBuilder类，建造者模式用不上
//#include "FrameBuilder.h"
//在程序停止运行的时候清理Dll里所有资源

class Facade
{
    using CameraGrabberFactory = ModuleFactory<CameraGrabberPtr>;
	using PlcAgentFactory = ModuleFactory<PlcAgentPtr>;
private:
    //FrameBuilder builder_;
    Configure<FRAMWORK_PART::MAIN> main_cfg_{GetModuleDirectory()+PathSeparator()+"Main.cfg"};
	//m表示module
	CameraGrabberFactory m_camera_grabber_;
	PlcAgentFactory m_plc_agent_;
    //TODO: 用tuple来管理几大模块
public:
    Facade();
    ~Facade();
    PlcAgentPtr PlcAgent(){ return m_plc_agent_.Create( main_cfg_.Param()["PlcAgent"] ); }
    CameraGrabberPtr CameraGrabber(){ return m_camera_grabber_.Create( main_cfg_.Param()["CameraGrabber"] ); } 
    void Run();
};


#endif 