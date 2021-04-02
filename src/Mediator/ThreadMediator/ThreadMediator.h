#pragma once

#include "../IMediator.h"
#include "thread_pool.h"
#include "CommonInclude/InspectException.h"

#include "../../Facade/Facade.h"


class ThreadMediator :public IMediator
{
private:
	threadpool executors_;
	void Dispatch(size_t camera_id)
	{
		while (!stop_dispatch_)
		{
			ImgTypePtr img = img_stash_[camera_id].wait_and_pop();
			//���UI
			facade_->DisplayImage(camera_id, img);

			//��ͼ��Ӳ��

			//���㷨���


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
		//����ʹ�õ���ͬ�������첽д�����ָ����д�����
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

