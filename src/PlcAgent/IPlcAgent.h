#ifndef IPLCAGENT_H
#define IPLCAGENT_H

#include "CommonInclude/TypeDefine.h"

class IPlcAgent
{
private:
    /* data */
public:
    IPlcAgent(/* args */){}
    virtual ~IPlcAgent(){}
    virtual auto ShotTriggered() ->size_t = 0;
};

using PlcAgentPtr = PointType<IPlcAgent>::Ptr;

#endif