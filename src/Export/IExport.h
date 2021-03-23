#ifndef IEXPORT_H
#define IEXPORT_H

#include "CommonInclude/TypeDefine.h"

class IExport
{
private:
    /* data */
public:
    IExport(/* args */){}
    ~IExport(){}
};

template<>
struct PointType<IExport>
{
	using Org = IExport*;
	using Ptr = std::shared_ptr<IExport>;
};

using ExportPtr = PointType<IExport>::Ptr;

#endif
