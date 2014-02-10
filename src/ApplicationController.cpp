#include "ApplicationController.h"

ApplicationController::ApplicationController(DataModelPtr dat)
{
    model = dat;
    shutOff = false;
}

bool ApplicationController::handleEvent(Event const & event)
{
    if(event.getType() == Evt_CloseApplication().getType())
    {
        shutOff = true;
    }
    else if(event.getType() == Evt_CloseWindow().getType())
    {
        model->removeView(event.getDataPtr<Evt_CloseWindowData>()->id);
    }
    return false;
}

bool ApplicationController::shutdown()
{
    return shutOff;
}
