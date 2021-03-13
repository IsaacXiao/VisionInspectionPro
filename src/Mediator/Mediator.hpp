#ifndef MEDIATOR_HPP
#define MEDIATOR_HPP

#include "ThreadSafe_Queue.hpp"
#include "../CameraGrabber/ICameraGrabber.h"

//TODO: 传给算法的Policy也作成模板参数
template<typename ImgType, typename StorageT = ThreadSafe_Queue<ImgType>>
class Mediator
{
private:
    StorageT img_stash_;
    CameraGrabberPtr camera_grabber_;
public:
    Mediator(/* args */)
    {
        
    }
    ~Mediator(){}

	///
	///在设计BroadCastSend函数的时候,参数类型是值得思考的.
	///第一方案是表列所有目前能够考虑周全的参数.
	///这种方案不具备可扩充性与效率.
	///第二种方案是,采用传递对象的方式,传递对象
	///马上就会想到该对象的生命期问题.
	///所以为了保证数据在任何转手后的地方均有效,
	///要么采用值拷贝方式,要么采用共享指针方式.
	///在这里类型是个模板参数,但是在后面的设计中更
	///认可的方式是共享指针.
	///
    void BroadCastSend(ImgType img)
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
};


#endif