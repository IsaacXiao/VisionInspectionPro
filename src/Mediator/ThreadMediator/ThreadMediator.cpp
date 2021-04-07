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
		//���UI
		facade_->DisplayImage(camera_id, img);
		if (!img->empty())	//���һ֡�ǿյ�
		{

			//��ͼ��Ӳ��

			//���㷨���
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
	/// �ֶ�delete����
	/// ʹ�õײ�join�ȴ��߳��������һ֡
	/// �����������ʱ�������б��λ����false
	/// �ͻ����н����ˣ�������ǣ�
	/// �̺߳Ͷ��ڴ���ԴҲ��������ֹͣ���ͷ�
	/// ��Ҫע����ǣ�����û�û�е��ֹͣ���˳���
	/// ��Դ���ò���ϵͳ�Զ�ȥ�ͷ���
	/// ����������Դǡ�÷����û��Ĳ���ϰ��
	/// ����ͼ��ݽ��鿴������ٿ�����һ��֮ǰ
	/// �Ȱ�֮ǰ�Ĺ黹�ٽ��µ�ȥ
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
