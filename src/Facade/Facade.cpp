#include "Facade.h"
#include "Logger/BroadCastLogger.hpp"

Facade::Facade():
    m_camera_grabber_(GetModuleDirectory() + PathSeparator() + "CameraGrabber"),
    m_plc_agent_(GetModuleDirectory() + PathSeparator() + "PlcAgent")
{
    //m_plc_agent_.Init();
    m_camera_grabber_.Init();       
}

Facade::~Facade()
{
}

void Facade::Run()
{
    //PlcAgentPtr plc_agent = PlcAgent();
    //std::cout << plc_agent->ShotTriggered() << endl;
	GlobalLogger::Record("Main", LOG_LEVEL::TRACK, "VisionInspection Begin");
	auto camera_grabber = CameraGrabber();
	camera_grabber->InitCamera();
}