#pragma once

#include "../IMediator.h"
#include "thread_pool.h"

class ThreadMediator : public IMediator
{
private:
	
public:
	ThreadMediator(const STRING & cfg);
	~ThreadMediator();

	static const char* Name()
	{
		return "ThreadMediator";
	}
	const STRING& Id() { return Name(); }
};

