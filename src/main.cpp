#include "CommonInclude/TypeDefine.h"
#include "Logger/BroadCastLogger.hpp"
#include "Facade/Facade.h"

#include "Mediator/Mediator.hpp"

int main()
{
    Facade facade;
    facade.Run();
    Mediator<EmptyClass> mediator; 

    return 0;
}