#include "Facade.h"
#include "Logger/BroadCastLogger.hpp"

Facade::Facade()
{
	system_ = std::make_unique<FrameBuilder>();
	system_->InitModule();
}

//TODO:需要加入相机是否掉线的判断
void Facade::Run()
{
	system_->Part<MEDIATOR>()->StartDispatch();
	for (USHORT camera_id = 0; camera_id < system_->CameraNumber(); camera_id++)
	{
		system_->Part<CAMERAGRABBER>()[camera_id]->StartGrabbing();
		system_->Part<MEDIATOR>()->FetchImgToWork(camera_id);
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

