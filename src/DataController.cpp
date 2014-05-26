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
    else if(event.getType() == Evt_Menu().getType())
    {
        Evt_MenuData *dat = event.getDataPtr<Evt_MenuData>();
        if(dat->open)
        {
            model->showMenu();
        }
        else
        {
            model->hideMenu();
        }
        return true;
    }
    else if(event.getType() == Evt_Move().getType())
    {
        Evt_MoveData *dat = event.getDataPtr<Evt_MoveData>();
        DataPacketPtr obj = model->getObject(dat->ID);
        if(obj.get() == NULL)
        {
            Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("Data Controller", "Moving invalid object")));
            return true;
        }
        int x = obj->getInt("x");
        if(x == INT_MAX)
        {
            Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("Data Controller", "Attempting to move immovable object, perhaps with an unstoppable force?")));
            return true;
        }
        int y = obj->getInt("y");
        if(y == INT_MAX)
        {
            Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("Data Controller", "Attempting to move immovable object, perhaps with an unstoppable force?")));
            return true;
        }
        obj->set("x", x+dat->x);
        obj->set("y", y+dat->y);
        return true;
    }
    return false;
}
