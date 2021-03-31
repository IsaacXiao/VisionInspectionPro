#pragma once

#include "../IMediator.h"
#include "CommonInclude/thread_pool.h"

class ThreadMediator : public IMediator
{
private:
	//TODO: 这个1做成从配置文件中读
	threadpool executors_;
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
		for ( size_t i = 0; i < camera_group_.size(); i++ )
		{
			auto camera_grabber = camera_group_[i].lock();
			camera_grabber->StartGrabbing();
			//executors_.commit(std::bind(&ICameraGrabber::StartGrabbing, camera_grabber));
		}
	}

	virtual void StoreImage(size_t id, ImgType img) override
	{
		executors_.commit(std::bind(&StorageType::push, &img_stash_[id], img));
		//img_stash_[id].push(img);
	}

	virtual void Stop() override
	{
		for (size_t i = 0; i < camera_group_.size(); i++)
		{
			auto camera_grabber = camera_group_[i].lock();
			camera_grabber->StopGrabbing();
		}
	}
};

