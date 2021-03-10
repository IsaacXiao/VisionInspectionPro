#include "CommonInclude/TypeDefine.h"
#include "Logger/BroadCastLogger.hpp"
#include "Facade/Facade.h"

int main()
{
    Logger::Record("main.exe",LOG_LEVEL::TRACK,"this is a maomaochong");
    Facade facade;
    facade.Run(); 

    return 0;
}