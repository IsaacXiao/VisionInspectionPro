#pragma once

#include "../IMediator.h"
#include "Configure/Configure.hpp"

class ThreadMediator : public IMediator
{
private:
	Configure<FRAMWORK_PART::MEDIATOR> thread_cfg_;
public:
	ThreadMediator(const STRING & cfg);
	~ThreadMediator();

	static const char* Name()
	{
		return "ThreadMediator";
	}
	const STRING& Id() { return Name(); }
};

