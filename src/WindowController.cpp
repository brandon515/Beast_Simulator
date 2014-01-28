#include "WindowController.h"

WindowController::WindowController(DataModelPtr pModel)
{
    model = pModel;
}

bool WindowController::handleEvent(Event const & event)
{
    if(Event.getType() == Evt_CloseWindow().getType())
    {
        Evt_CloseWindowData *dat = Event.getDataPtr<Evt_CloseWindowData>();
        model->removeView(dat->id);
        return true;
    }
    return false;
}
