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
    return false;
}
