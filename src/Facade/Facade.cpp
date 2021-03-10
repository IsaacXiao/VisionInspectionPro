#include "Facade.h"

Facade::Facade():
    m_camera_grabber_(GetModuleDirectory() + PathSeparator() + "CameraGrabber"),
    m_plc_agent_(GetModuleDirectory() + PathSeparator() + "PlcAgent")
{
    m_plc_agent_.Init();
    m_camera_grabber_.Init();       
}

Facade::~Facade()
{
}

void Facade::Run()
{
    PlcAgentPtr plc_agent = PlcAgent();
    std::cout << plc_agent->ShotTriggered() << endl;
}