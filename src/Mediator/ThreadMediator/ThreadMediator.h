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
	void Dispatch(size_t camera_id)
	{
		while (!stop_dispatch_)
		{
			ImgTypePtr img = img_stash_[camera_id].wait_and_pop();
			emit SigChangeBack(camera_id, img);
		}
	}
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
		尝试不做commit直接同步写入队列看会卡界面不
		executors_.commit(std::bind(&StorageType::push, &img_stash_[id], std::forward<ImgType>(img)));
	}

	virtual void FetchImgToWork(size_t camera_id) override
	{
		executors_.commit(std::bind(&ThreadMediator::Dispatch,this,camera_id));
	}
};

