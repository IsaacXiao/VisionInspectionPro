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