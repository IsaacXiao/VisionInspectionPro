#ifndef CONSOLE_LOGGER_H
#define CONSOLE_LOGGER_H

#include <iostream>
#include "CommonInclude/TypeDefine.h"

class Console_Logger
{
private:
    /* data */
public:
    Console_Logger() = default;
    ~Console_Logger(){}
    
    static void Record( LOG_LEVEL which_level, const STRING& info, bool is_show )
	{
        if (is_show)
        {
            std::cout << info;
        }
	}
};


#endif