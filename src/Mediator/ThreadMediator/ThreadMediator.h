#pragma once

#include "../IMediator.h"
#include "thread_pool.h"
#include "CommonInclude/InspectException.h"
#include "CommonInclude/Memory.hpp"

#include "Logger/BroadCastLogger.hpp"

class ThreadMediator :public IMediator
{
private:
	threadpool *executors_;
	bool stop_dispatch_{ true };

public:
	ThreadMediator::ThreadMediator(const STRING & cfg):IMediator(cfg),executors_(nullptr){}
	static const char* Name(){return "ThreadMediator";}

	void StartDispatch() override;

	void StopDispatch() override;

	virtual void StoreImage(USHORT camera_id, ImgType&& img) override;

	virtual void FetchImgToWork(USHORT camera_id) override;

	virtual void CameraOffLine(USHORT camera_id) override;
};

