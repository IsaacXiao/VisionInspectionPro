#pragma once

#include "../IMediator.h"
#include "thread_pool.h"

#include <QtCore/QObject>

class ThreadMediator : public QObject, public IMediator
{
	Q_OBJECT
signals :
	void SigChangeBack(unsigned short, ImgTypePtr) const;
private:
	threadpool executors_;
public:
	ThreadMediator::ThreadMediator(const STRING & cfg) :IMediator(cfg), executors_(stoi(cfg_.Param()["thread_number"]))
	{

	}

	static const char* Name()
	{
		return "ThreadMediator";
	}

	virtual void StoreImage(size_t id, ImgType&& img) override
	{
		executors_.commit(std::bind(&StorageType::push, &img_stash_[id], std::forward<ImgType>(img)));
	}

	virtual ImgTypePtr FetchToBroadCast(size_t id) override
	{
		return img_stash_[id].wait_and_pop();
	}
};

