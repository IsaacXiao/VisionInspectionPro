#ifndef FACADE_HEAD_H
#define FACADE_HEAD_H

#include "FrameBuilder.h"
#include "../Mediator/Mediator.hpp"

class Facade
{
private:
    FrameBuilder builder_;
	//Mediator * img_manager_;
public:
    Facade();
    ~Facade();
	//template<typename T, typename... Ts>
	//void Run(Ts&&... params)
	//{
	//	//PlcAgentPtr plc_agent = PlcAgent();
	//	//std::cout << plc_agent->ShotTriggered() << endl;
	//	GlobalLogger::Record("Main", LOG_LEVEL::TRACK, "VisionInspection Begin");
	//	auto camera_grabber = CameraGrabber();
	//	camera_grabber->InitCamera();
	//}
	
	//#include <windows.h>无需包含
	void Run(HWND where, UINT width, UINT height)
	{
		auto camera_grabber = builder_.ConstructCameraGrabber();
		camera_grabber->DisplayImg(where,width,height);
	}
};

#endif 