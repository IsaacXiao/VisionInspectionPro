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

using AlgProcessorPtr = PointType<IAlgProcessor>::Ptr;

#endif