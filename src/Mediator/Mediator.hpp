#ifndef MEDIATOR_HPP
#define MEDIATOR_HPP

#include "ThreadSafe_Queue.hpp"
#include "../CameraGrabber/ICameraGrabber.h"

#include <utility>


namespace INSPECTION
{
	//TODO: 传给算法的Policy也作成模板参数
	template<typename ImgType, typename StorageT = ThreadSafe_Queue<ImgType>>
	class ImgMediator
	{
	private:
	    StorageT img_stash_;
	    CameraGrabberPtr camera_grabber_;
	public:
	    ImgMediator(/* args */)
	    {
	        
	    }
	    ~ImgMediator(){}
	
		auto GetImage()
		{
			VECTOR<STRING> filenames;
			BrowseFiles("D:\\WorkSpace\\Inspection\\Images\\jpg", "." + STRING("jpg"), filenames);
			//把STRING转成QImage
			for (auto &item: filenames)
			{
				img_stash_.push(QImage(item.c_str()));
			}
			return img_stash_;
		}

	    void BroadCastSend()
	    {
	        //获取图片用主线程存储
	        //卡界面了再用线程来存储
	        //先拿到图了再说
	        //img_stash_.Push(camera_grabber_->GetImage());
	        //3个函数分3路输出
	        //DisplayImage
	        //InspectImage
	        //SaveImage
	    }

		void DisplayImage()
		{

		}
	};
}


template<typename ImgType, typename StorageT>
using Mediator = INSPECTION::ImgMediator<ImgType, StorageT>;

template<typename ImgType, typename StorageT>
struct PointType<Mediator<ImgType, StorageT>>
{
	using Ptr = std::unique_ptr<Mediator<ImgType, StorageT>>;
};

#endif