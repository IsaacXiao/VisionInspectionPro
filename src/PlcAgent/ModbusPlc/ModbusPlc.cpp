#include "ModbusPlc.h"
#include "Logger/BroadCastLogger.hpp"

ModbusPlc::ModbusPlc(const STRING & cfg):modbus_cfg_(cfg)
{
}

ModbusPlc::~ModbusPlc()
{
}

auto ModbusPlc::ShotTriggered() ->size_t
{
    Logger::Record("ModbusPlc dll",LOG_LEVEL::TRACK,modbus_cfg_.Param()["param1"]);
    return 7777;
}