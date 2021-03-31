#pragma once

#include "../IMediator.h"
#include "CommonInclude/thread_pool.h"

class ThreadMediator : public IMediator
{
private:
	threadpool executors_;
public:
	ThreadMediator(const STRING & cfg);
	~ThreadMediator();

	static const char* Name()
	{
		return "ThreadMediator";
	}

	virtual void StoreImage(size_t id, ImgType&& img) override
	{
		executors_.commit(std::bind(&StorageType::push, &img_stash_[id], std::forward<ImgType>(img)));

	}

	virtual ImgTypePtr FetchImage(size_t id) override
	{
		return img_stash_[id].wait_and_pop();
	}
};

