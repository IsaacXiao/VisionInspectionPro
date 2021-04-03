#pragma once

#include "../IMediator.h"
#include "thread_pool.h"
#include "CommonInclude/InspectException.h"
#include "CommonInclude/Memory.hpp"
#include "../../Facade/Facade.h"
#include "Logger/BroadCastLogger.hpp"

class ThreadMediator :public IMediator
{
private:
	threadpool *executors_;
	bool stop_dispatch_{ true };

	void Dispatch(size_t camera_id)
	{
		while ( !stop_dispatch_ )
		{
			ImgTypePtr img = img_stash_[camera_id].wait_and_pop();
			//输出UI
			facade_->DisplayImage(camera_id, img);
			if (!img->empty())
			{

				//存图到硬盘

				//给算法检测
			}
		}
		GlobalLogger::Record("ThreadMediator", LOG_LEVEL::TRACK, "Dispatch is stopped");
		return;
	}
public:
	ThreadMediator::ThreadMediator(const STRING & cfg):IMediator(cfg),executors_(nullptr)
	{
	}

	static const char* Name()
	{
		return "ThreadMediator";
	}

	void StartDispatch() override
	{ 
		stop_dispatch_ = false; 
		executors_ = new threadpool(stoi(cfg_.Param()["thread_number"]));
	}
	void StopDispatch() override
	{
		stop_dispatch_ = true;
		for (size_t i = 0; i < fifo_number_; i++)
		{
			img_stash_[i].StopWaiting();
		}
		/// <summary>
		/// 手动析构使得底层join等待线程拿完最后一帧
		/// 它拿完后还想拿时发现运行标记位已是false
		/// 就会自行结束了，最棒的是：
		/// 线程和堆内存资源也能随运行停止而释放
		/// 需要注意的是，如果用户没有点击停止就退程序
		/// 资源就让操作系统自动去释放了
		/// </summary>
		DeletePtr(executors_);
	}

	virtual void StoreImage(size_t camera_id, ImgType&& img) override
	{
		//TODO：考虑在此增加校验，从PLC获取校验信息后再往队列里面写

		//这里使用的是同步而非异步写，哪种更好有待测试
		if ( "sync" == cfg_.Param()["grabber_pattern"] )
		{
			img_stash_[camera_id].push(std::forward<ImgType>(img));
		} 
		else if("async" == cfg_.Param()["grabber_pattern"])
		{
			executors_->commit(std::bind(&StorageType::push, &img_stash_[camera_id], std::forward<ImgType>(img)));
		}
	}

	virtual void FetchImgToWork(size_t camera_id) override
	{
		executors_->commit(std::bind(&ThreadMediator::Dispatch,this,camera_id));
	}
};

