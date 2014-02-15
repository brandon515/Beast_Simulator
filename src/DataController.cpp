#include "DataController.h"
 
DataController::DataController(DataModelPtr data):
    model(data)
{
    currentFocusID = 0;
}

bool DataController::handleEvent(Event const & event)
{
    if(event.getType() == Evt_CloseWindow().getType())
    {
        uint32_t id = event.getDataPtr<Evt_CloseWindowData>()->id;
        if(id == 0)
            return false;
        model->removeView(id);
        return true;
    }
    else if(event.getType() == Evt_WindowFocus().getType())
    {
        uint32_t id = event.getDataPtr<Evt_WindowFocusData>()->id;
        currentFocusID = id;
        return true;
    }
    else if(event.getType() == Evt_Keyboard().getType())
    {
        Evt_KeyboardData *dat = event.getDataPtr<Evt_KeyboardData>();
        if(dat->key == VirtualKeyboard::getSingleton().getKeyInt("exit") && !dat->keyDown)
        {
            model->removeView(currentFocusID);
            return true;
        }
    }
    return false;
}
