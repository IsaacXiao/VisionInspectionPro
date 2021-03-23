#include "FrameBuilder.h"

FrameBuilder::FrameBuilder() :
	m_camera_grabber_(GetModuleDirectory() + PathSeparator() + "CameraGrabber"),
	m_plc_agent_(GetModuleDirectory() + PathSeparator() + "PlcAgent")
{

}

void FrameBuilder::InitModule()
{
	//m_plc_agent_.Load();
	m_camera_grabber_.Load();
}

void FrameBuilder::BuildInspectionSystem()
{
	ConstructCameraGrabber();
}

void FrameBuilder::DestructModule()
{
	Part<CAMERAGRABBER>().swap((CameraGrabberPtr)nullptr);
}

