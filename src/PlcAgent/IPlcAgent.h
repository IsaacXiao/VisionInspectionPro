#ifndef IPLCAGENT_H
#define IPLCAGENT_H

#include "CommonInclude/TypeDefine.h"
#include <memory>

class IPlcAgent
{
private:
    /* data */
public:
    IPlcAgent(/* args */){}
    virtual ~IPlcAgent(){}
    virtual auto ShotTriggered() ->size_t = 0;
};

template<>
struct PointType<IPlcAgent>
{
	using Org = IPlcAgent*;
	using Ptr = std::shared_ptr<IPlcAgent>;
}; 

using PlcAgentOrg = PointType<IPlcAgent>::Org;
using PlcAgentPtr = PointType<IPlcAgent>::Ptr;

#endif