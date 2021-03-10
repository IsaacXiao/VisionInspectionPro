#ifndef MODBUS_PLC_H
#define MODBUS_PLC_H

#include "../IPlcAgent.h"
#include "Configure/Configure.hpp"
#include "CommonInclude/TypeDefine.h"

class ModbusPlc : public IPlcAgent
{
private:
    Configure<FRAMWORK_PART::PLCAGENT> modbus_cfg_;
public:
    ModbusPlc(const STRING & cfg);
    ~ModbusPlc();
    static constexpr const char* Name()
    {		
		return "ModbusPlc";
	}
    virtual auto ShotTriggered() ->size_t override;
};


#endif