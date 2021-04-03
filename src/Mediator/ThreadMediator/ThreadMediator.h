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
			//���UI
			facade_->DisplayImage(camera_id, img);
			if (!img->empty())
			{

				//��ͼ��Ӳ��

				//���㷨���
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
		/// �ֶ�����ʹ�õײ�join�ȴ��߳��������һ֡
		/// �����������ʱ�������б��λ����false
		/// �ͻ����н����ˣ�������ǣ�
		/// �̺߳Ͷ��ڴ���ԴҲ��������ֹͣ���ͷ�
		/// ��Ҫע����ǣ�����û�û�е��ֹͣ���˳���
		/// ��Դ���ò���ϵͳ�Զ�ȥ�ͷ���
		/// </summary>
		DeletePtr(executors_);
	}

	virtual void StoreImage(size_t camera_id, ImgType&& img) override
	{
		//TODO�������ڴ�����У�飬��PLC��ȡУ����Ϣ��������������д

		//����ʹ�õ���ͬ�������첽д�����ָ����д�����
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

