// ThreadMediator.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "ThreadMediator.h"

ThreadMediator::ThreadMediator(const STRING & cfg):IMediator(cfg),executors_(stoi(cfg_.Param()["thread_number"]))
{

}

ThreadMediator::~ThreadMediator()
{

}