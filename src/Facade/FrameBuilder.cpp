#include "FrameBuilder.h"

void FrameBuilder::ConstructCameraGrabber()
{
	std::get<CAMERAGRABBER>(inspection_).clear();
	for (size_t i = 0; i < camera_number_; i++)
	{
		std::get<CAMERAGRABBER>(inspection_).emplace_back(m_camera_grabber_.Create(main_cfg_.Param()["CameraGrabber"]));
	}
}

FrameBuilder::FrameBuilder() :
	m_camera_grabber_(GetModuleDirectory() + PathSeparator() + "CameraGrabber"),
	m_plc_agent_(GetModuleDirectory() + PathSeparator() + "PlcAgent"),
	m_mediator_(GetModuleDirectory() + PathSeparator() + "Mediator")
{
	camera_number_ = stoi(main_cfg_.Param()["CameraNumber"]);
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

	for ( size_t i = 0; i < camera_number_; i++ )
	{
		auto &camera = std::get<CAMERAGRABBER>(inspection_)[i];
		camera->SetId(i);
		camera->AttachMediator(std::get<MEDIATOR>(inspection_));
	}
}


