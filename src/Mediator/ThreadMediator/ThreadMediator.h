#pragma once

#include "../IMediator.h"
#include "CommonInclude/thread_pool.h"

class ThreadMediator : public IMediator
{
private:
	//TODO: ���1���ɴ������ļ��ж�
	threadpool executor_{ 1 };
public:
	ThreadMediator(const STRING & cfg);
	~ThreadMediator();

	static const char* Name()
	{
		return "ThreadMediator";
	}
	const STRING& Id() { return Name(); }

	virtual void GetImage() override
	{
		auto camera_grabber = camera_grabber_.lock();
		executor_.commit(std::bind(&ICameraGrabber::StartGrabbing, camera_grabber));
	}

	virtual void Stop() override
	{
		auto camera_grabber = camera_grabber_.lock();
		camera_grabber->StopGrabbing();
	}
};

