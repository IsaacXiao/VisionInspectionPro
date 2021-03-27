#include "FrameBuilder.h"

FrameBuilder::FrameBuilder() :
	m_camera_grabber_(GetModuleDirectory() + PathSeparator() + "CameraGrabber"),
	m_plc_agent_(GetModuleDirectory() + PathSeparator() + "PlcAgent"),
	m_mediator_(GetModuleDirectory() + PathSeparator() + "Mediator")
{

}

void FrameBuilder::InitModule()
{
	//m_plc_agent_.Load();
	m_camera_grabber_.Load();
	m_mediator_.Load();
}

void FrameBuilder::BuildInspectionSystem()
{
	ConstructCameraGrabber();
	ConstructMediator();
	std::get<CAMERAGRABBER>(inspection_)->AttachMediator(std::get<MEDIATOR>(inspection_));
	std::get<MEDIATOR>(inspection_)->AttachCamera(std::get<CAMERAGRABBER>(inspection_));
}

void FrameBuilder::DestructModule()
{
	//这里无需reset或swap，智能指针真智能
}

