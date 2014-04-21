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
/*    else if(event.getType() == Evt_Keyboard().getType())
    {
        Evt_KeyboardData *dat = event.getDataPtr<Evt_KeyboardData>();
        if(dat->key == VirtualKeyboard::getSingleton().getKeyInt("exit") && !dat->keyDown)
        {
            model->removeView(currentFocusID);
            return true;
        }
        return false;
    }*/
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
/*    else if(event.getType() == Evt_JoystickButton().getType())
    {
        Evt_JoystickButtonData *id = event.getDataPtr<Evt_JoystickButtonData>();
        if(id->isPressed)
        {
            if(id->button == 0)
                std::cout << "ho ho ho\n";
        }
        return true;
    }
    else if(event.getType() == Evt_JoystickAxis().getType())
    {
        Evt_JoystickAxisData *dat = event.getDataPtr<Evt_JoystickAxisData>();
        if(dat->pos > 30000 || dat->pos < -30000)
        {
            Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("Joystick axis: " + boost::lexical_cast<std::string>(dat->axis) + "\nJoystick pos: " + boost::lexical_cast<std::string>(dat->pos))));
        }
    }*/
    return false;
}
