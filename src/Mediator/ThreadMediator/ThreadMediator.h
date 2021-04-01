#pragma once

#include "../IMediator.h"
#include "thread_pool.h"
#include "CommonInclude/InspectException.h"
#include <QtCore/QObject>

/************************************************************************/
/* 
为了满足用户的需求，把图像用QT界面显示
解耦实在不易
把ui指针通过facade的run函数带到线程里来显示味道更坏
不管如何，写起来都长得丑
目前这个做法是为最佳方案留后路：
在1个Dll里把显示实时采集给做了（不带到主窗口去！！）
*/
/************************************************************************/

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
			//输出UI
			//TODO: 可以进一步改进，让facade持有ui层
			//让mediator持有facade
			//便可以在此处调用facade->DisplayImage
			//让facade调用ui->ChangeBackGround
			emit SigChangeBack(camera_id, img);
			//存图到硬盘

			//给算法检测
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

	virtual void StoreImage(size_t camera_id, ImgType&& img) override
	{
		//这里使用的是同步而非异步写，哪种更好有待测试
		if ( "sync" == cfg_.Param()["grabber_pattern"] )
		{
			img_stash_[camera_id].push(std::forward<ImgType>(img));
		} 
		else if("async" == cfg_.Param()["grabber_pattern"])
		{
			executors_.commit(std::bind(&StorageType::push, &img_stash_[camera_id], std::forward<ImgType>(img)));
		}
		else
		{
			throw CfgException("Mediator Configure error!");
		}
	}

	virtual void FetchImgToWork(size_t camera_id) override
	{
		executors_.commit(std::bind(&ThreadMediator::Dispatch,this,camera_id));
	}
};

