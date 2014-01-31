#include "WindowController.h"

WindowController::WindowController(DataModelPtr pModel)
{
    model = pModel;
}

bool WindowController::handleEvent(Event const & event)
{
    if(event.getType() == Evt_CloseWindow().getType())
    {
        Evt_CloseWindowData *dat = event.getDataPtr<Evt_CloseWindowData>();
        model->removeView(dat->id);
        return true;
    }
    return false;
}
