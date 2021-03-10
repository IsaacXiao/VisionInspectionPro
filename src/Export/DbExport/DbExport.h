#ifndef DB_EXPORT_H
#define DB_EXPORT_H

#include "../IExport.h"
#include "Configure/Configure.hpp"
#include "CommonInclude/TypeDefine.h"

class DbExport : public IExport
{
private:
    Configure<FRAMWORK_PART::EXPORT> db_cfg_;
public:
    DbExport(const STRING & cfg);
    ~DbExport();
    static constexpr const char* Name()
    {		
		return "DbExport";
	}
};


#endif