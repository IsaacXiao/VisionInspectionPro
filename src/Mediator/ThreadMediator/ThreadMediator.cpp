// ThreadMediator.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "ThreadMediator.h"
#include "../../Facade/Facade.h"


void ThreadMediator::StartDispatch()
{
	stop_dispatch_ = false;
	executors_ = new threadpool(stoi(cfg_.Param()["thread_number"]));
	for (USHORT i = 0; i < fifo_number_; i++)
	{
		img_stash_[i].StartWaiting();
	}
}

void ThreadMediator::StopDispatch()
{
	stop_dispatch_ = true;
	for (USHORT i = 0; i < fifo_number_; i++)
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

void ThreadMediator::StoreImage(USHORT camera_id, ImgType&& img)
{
	img_stash_[camera_id].push(img);
}

void ThreadMediator::FetchImgToWork(USHORT camera_id)
{
	executors_->commit([this,camera_id](){
		while (!stop_dispatch_)
		{
			ImgTypePtr img = img_stash_[camera_id].wait_and_pop();

			if (!img->mat_.empty())	//���һ֡�ǿյ�
			{
				//���UI
				facade_->DisplayImage(camera_id, img);

				//��ͼ��Ӳ��

				//���㷨���
			}
		}
		GlobalLogger::Record("ThreadMediator", LOG_LEVEL::TRACK, "Dispatch is stopped");
	});
}

void ThreadMediator::CameraOffLine(USHORT camera_id)
{
	GlobalLogger::Record("Camera " + to_string(camera_id), LOG_LEVEL::ERR, "disconnected,please check connection"/* + STRING("\nin ") + __FUNCTION__*/);
	facade_->CameraOffline(camera_id);
}
