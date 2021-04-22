#ifndef FACADE_HEAD_H
#define FACADE_HEAD_H

#include "FrameBuilder.h"
#include <utility>
#include "../Mediator/IMediator.h"

#include "../UI/IForDisplay.h"


///���Facade����Ӧ�ó�������й���
///�������κε��������UI��
///����QT����MFC��������������
///ֻ���ù����̳���IForDisplay
///��дDisplayImage����������ʾ
///��Ϊû�мƻ��ñ�ı���������������Facade
///�Ͳ������������Dll����So��ȥ�� 
class Facade 
{
private:
	FrameBuilderPtr system_{nullptr};
	IForDisplay* ui_{nullptr};
public:
	Facade();

	void AttachUI(IForDisplay * ui) { ui_ = ui;  }
	void DisplayImage(USHORT camera_id, ImgTypePtr img){ ui_->DisplayImage(camera_id, img); }

	/*���������ʾ�޷����²��������
	ֻ�������ÿɱ䳤ģ��������ż���QLable���ھ�����²�ļ���Camera�ﴫ��ȥ
	template<typename... Ts>
	void Run(Ts&&... params)
	{
		//system_->Part<CAMERAGRABBER>()->StartLive(std::forward<Ts>(params)...);
	}*/
	void Run();

	void ReloadCfg();

	void Stop() const;

	void SoftTriggerGrab(USHORT camera_id) const;

	void CameraOffline(USHORT camera_id) const
	{
		if (!system_->Part<CAMERAGRABBER>()[camera_id]->IsStoped())
		{
			//Stop();����֪ͨ�û�ȥ���ֹͣ����Ҫ��������ã����̳߳��ظ��ͷ���Դ���ϡ��
		}
	}
};

//template<>
//struct PointType<Facade>
//{
//	using Org = Facade*;
//	using Ptr = std::unique_ptr<Facade>;
//};

using FacadePtr = PointType<Facade>::Ptr;

#endif 