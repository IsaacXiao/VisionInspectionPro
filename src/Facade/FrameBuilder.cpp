#include "FrameBuilder.h"

FrameBuilder::FrameBuilder() :
	m_camera_grabber_(GetModuleDirectory() + PathSeparator() + "CameraGrabber"),
	m_plc_agent_(GetModuleDirectory() + PathSeparator() + "PlcAgent"),
	m_mediator_(GetModuleDirectory() + PathSeparator() + "Mediator")
{
	number_ = stoi(main_cfg_.Param()["CameraNumber"]);
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

	for ( size_t i = 0; i < number_; i++ )
	{
		auto &camera = std::get<CAMERAGRABBER>(inspection_)[i];
		camera->SetId(i);
		camera->AttachMediator(std::get<MEDIATOR>(inspection_));
	}
}

void FrameBuilder::DestructModule()
{
	//这里无需reset或swap，智能指针真智能
}

