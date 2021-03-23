#ifndef IALG_PROCESSOR_H
#define IALG_PROCESSOR_H

#include "CommonInclude/TypeDefine.h"

class IAlgProcessor
{
private:
    /* data */
public:
    IAlgProcessor(/* args */){}
    virtual ~IAlgProcessor(){}
};

template<>
struct PointType<IAlgProcessor>
{
	using Org = IAlgProcessor*;
	using Ptr = std::shared_ptr<IAlgProcessor>;
};

using AlgProcessorPtr = PointType<IAlgProcessor>::Ptr;

#endif