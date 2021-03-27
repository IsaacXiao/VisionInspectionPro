#pragma once

#include "../IMediator.h"
#include "thread_pool.h"

class ThreadMediator : public IMediator
{
private:
	//TODO: ���1���ɴ������ļ��ж�
	threadpool executor{ 1 };
public:
	ThreadMediator(const STRING & cfg);
	~ThreadMediator();

	static const char* Name()
	{
		return "ThreadMediator";
	}
	const STRING& Id() { return Name(); }

	virtual ImgTypePtr Do() override
	{
		auto camera_grabber = camera_grabber_.lock();
		camera_grabber->StartGrabbing();
		camera_grabber->PlcTrigger();
		FetchImage();
	}

	virtual void Stop() override
	{
		auto camera_grabber = camera_grabber_.lock();
		camera_grabber->StopGrabbing();
	}
};

