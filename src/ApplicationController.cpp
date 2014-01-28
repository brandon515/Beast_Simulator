#include "ApplicationController.h"

ApplicationController::ApplicationController()
{
    shutOff = false;
}

bool ApplicationController::handleEvent(Event const & event)
{
    if(Event.getType() == Evt_CloseApplication().getType())
    {
        shutOff = true;
    }
    return false;
}

bool ApplicationController::shutdown()
{
    return shutOff;
}
