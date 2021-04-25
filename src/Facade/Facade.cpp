#include "Facade.h"
#include "Logger/BroadCastLogger.hpp"
#include "CommonInclude/InspectException.h"

Facade::Facade()
{
	system_ = std::make_unique<FrameBuilder>();
	system_->InitModule();
}

void Facade::Run()
{
	try
	{
		system_->Part<MEDIATOR>()->StartDispatch();
		for (USHORT camera_id = 0; camera_id < system_->CameraNumber(); camera_id++)
		{
			system_->Part<CAMERAGRABBER>()[camera_id]->StartGrabbing();
			system_->Part<MEDIATOR>()->FetchImgToWork(camera_id);
		}
	}
	catch (const InspectException& e)
	{
		GlobalLogger::Record("main.exe", LOG_LEVEL::DEAD, e.what());
	}
}

void Facade::ReloadCfg()
{
	system_->BuildInspectionSystem();
	system_->Part<MEDIATOR>()->AttachFacade(this);
}

void Facade::Stop() const
{
	for (auto& camera : system_->Part<CAMERAGRABBER>())
	{
		camera->StopGrabbing();
	}
	system_->Part<MEDIATOR>()->StopDispatch();
}

void Facade::SoftTriggerGrab(USHORT camera_id) const
{
	system_->Part<CAMERAGRABBER>()[camera_id]->SoftTrigger();
}

