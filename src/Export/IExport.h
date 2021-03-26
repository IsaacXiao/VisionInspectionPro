#ifndef IEXPORT_H
#define IEXPORT_H

#include "CommonInclude/TypeDefine.h"

class IExport
{
private:
    /* data */
public:
    IExport(/* args */){}
	virtual ~IExport(){}
};

template<>
struct PointType<IExport>
{
	using Org = IExport*;
	using Ptr = std::shared_ptr<IExport>;
};

using ExportOrg = PointType<IExport>::Org;
using ExportPtr = PointType<IExport>::Ptr;

#endif
