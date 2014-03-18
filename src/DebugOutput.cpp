#include "DebugOutput.h"

DebugOutput::DebugOutput()
{}

bool DebugOutput::handleEvent(Event const & event)
{
    if(event.getType() == MsgEvt().getType())
    {
        std::cout << event.getDataPtr<Evt_MsgData>()->output;
        return true;
    }
    else if(event.getType() == Evt_Move().getType())
    {
        Evt_MoveData *dat = event.getDataPtr<Evt_MoveData>();
        std::string msg = MsgEvt("Move Event recieved with following parameters:\n\tname: " + dat->name + "\n\tx: " + boost::lexical_cast<std::string>(dat->x) + "\n\ty: " + boost::lexical_cast<std::string>(dat->y)).getDataPtr<Evt_MsgData>()->output;
        std::cout << msg;
        return true;
    }
    else if(event.getType() == Evt_CloseApplication().getType())
    {
        
    }
    else if(event.getType() == Evt_CloseWindow().getType())
    {
        
    }
    else if(event.getType() == Evt_JoystickAxis().getType())
    {
        
    }
    else if(event.getType() == Evt_JoystickButton().getType())
    {
        
    }
    else if(event.getType() == Evt_Keyboard().getType())
    {
        
    }
    else if(event.getType() == Evt_WindowFocus().getType())
    {
        
    }
    return false;
}
