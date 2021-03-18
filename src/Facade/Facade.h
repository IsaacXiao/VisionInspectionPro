#ifndef FACADE_HEAD_H
#define FACADE_HEAD_H

#include "FrameBuilder.h"
#include "../Mediator/Mediator.hpp"
#include <utility>

class Facade
{
private:
    FrameBuilder builder_;
	//Mediator * img_manager_;
public:
    Facade();
    ~Facade();

	//有的相机采集的第三方库与界面耦合在一起了
	//多亏C++11开始有了可变长模板参数，可将相机采集做成通用的方案
	template<typename... Ts>
	void Run(Ts&&... params)
	{
		builder_.BuildInspectionSystem();
		auto camera_grabber = builder_.Part<CAMERAGRABBER>();
		camera_grabber->DisplayImg(std::forward<Ts>(params)...);
	}
};

#endif 