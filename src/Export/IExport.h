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

using ExportPtr = PointType<IExport>::Ptr;

#endif
