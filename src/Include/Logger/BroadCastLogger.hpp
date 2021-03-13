//  (C) Copyright XiaoRong 2021.
//  composited logger with policy .
//  Software License, Version 1.0.0

#ifndef BROADCAST_LOGGER_HPP
#define BROADCAST_LOGGER_HPP

#include "CommonInclude/TypeDefine.h"
#include "CommonInclude/PlatFormHead.h"
#include "CommonInclude/utility.hpp"
#include "Configure/Configure.hpp"

#include "UI_Logger.h"
#include "Text_Logger.h"
#include "Console_Logger.h"

template<typename Simple_LoggerT, typename UI_LoggerT,typename Text_LoggerT>
class BroadCastLogger final
{
private:
	BroadCastLogger() = delete;
	BroadCastLogger(const BroadCastLogger&) = delete;
	BroadCastLogger & operator=(const BroadCastLogger&) = delete;
	//两个移动的操作不会自动生成
	// BroadCastLogger(BroadCastLogger&&) = delete;
	// BroadCastLogger & operator=(BroadCastLogger&&) = delete;
public:
	~BroadCastLogger(){}

	///
	///日志记录		 效仿linux的系统日志记录方式，但免去了name这个字段
	///
	///who			: 类别id: 比如 "Algorithm"代表日志源为算法相关操作."CameraGrabber"代表日志源为相机抓图相关操作
	///level		: 警告级别
	///msg			: 描叙	
	///time			: 时间
	///
	static void Record( STRING&& who, LOG_LEVEL which_level, const STRING& msg )
    {
		constexpr const char* level_[5]  { "Track", "Warning", "HighWarning", "Error", "DEAD" };

		STRING cur_time;
		Time2Str( TimeInt32(), cur_time );
		STRING && info = "DateTime:" + cur_time + "-----------------------\nwho: " + who
			+ " Level: " + level_[EnumToInt(which_level)] + " Desc: " + msg + "\n";

		static auto where = GetModuleDirectory() + PathSeparator() + "Logger.cfg";
		static Configure<FRAMWORK_PART::LOGGER> cfg_{ where };

		bool ui_show = StrToBool(cfg_.Param()["Ui_Logger"]);
		bool text_show = StrToBool(cfg_.Param()["Text_Logger"]);
		bool simple_show = StrToBool(cfg_.Param()["Simple_Logger"]);

		UI_LoggerT::Record( which_level, info, ui_show );
		Text_LoggerT::Record( which_level, info, text_show );
		Simple_LoggerT::Record( which_level, info, simple_show ); 
	}
};

using GlobalLogger = BroadCastLogger<Console_Logger,UI_Logger,Text_Logger>;

#endif