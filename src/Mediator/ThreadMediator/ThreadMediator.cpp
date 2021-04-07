// ThreadMediator.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "ThreadMediator.h"
#include "../../Facade/Facade.h"

void ThreadMediator::Dispatch(size_t camera_id)
{
	while (!stop_dispatch_)
	{
		ImgTypePtr img = img_stash_[camera_id].wait_and_pop();
		//输出UI
		facade_->DisplayImage(camera_id, img);
		if (!img->empty())	//最后一帧是空的
		{

			//存图到硬盘

			//给算法检测
		}
	}
	GlobalLogger::Record("ThreadMediator", LOG_LEVEL::TRACK, "Dispatch is stopped");
}

void ThreadMediator::StartDispatch()
{
	stop_dispatch_ = false;
	executors_ = new threadpool(stoi(cfg_.Param()["thread_number"]));
}

void ThreadMediator::StopDispatch()
{
	stop_dispatch_ = true;
	for (size_t i = 0; i < fifo_number_; i++)
	{
		img_stash_[i].StopWaiting();
	}
	/// <summary>
	/// 手动delete析构
	/// 使得底层join等待线程拿完最后一帧
	/// 它拿完后还想拿时发现运行标记位已是false
	/// 就会自行结束了，最棒的是：
	/// 线程和堆内存资源也能随运行停止而释放
	/// 需要注意的是，如果用户没有点击停止就退程序
	/// 资源就让操作系统自动去释放了
	/// 这样管理资源恰好符合用户的操作习惯
	/// 就像图书馆借书看完后还想再看另外一本之前
	/// 先把之前的归还再借新的去
	/// </summary>
	DeletePtr(executors_);
}

void ThreadMediator::StoreImage(size_t camera_id, ImgType&& img)
{
	img_stash_[camera_id].push(std::forward<ImgType>(img));
}

void ThreadMediator::FetchImgToWork(size_t camera_id)
{
	executors_->commit(std::bind(&ThreadMediator::Dispatch, this, camera_id));
}
