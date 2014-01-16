#include "Logging.h"

Logging::Logging()
{
    file.open("DebugOutput", std::ios::out);
}

Logging::~Logging()
{
    file.close();
}

bool Logging::handleEvent(Event const & event)
{
    if(event.getType() == MsgEvt().getType())
    {
        std::string msg = event.getDataPtr<Evt_MsgData>()->output;
        file << msg << "\n";
        return true;
    }
    return false;
}
