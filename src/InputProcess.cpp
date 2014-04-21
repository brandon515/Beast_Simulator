#include "InputProcess.h"

InputProcess::InputProcess():
    Process("InputProcess")
{}

bool InputProcess::init()
{
    return true;
}

void InputProcess::tick()
{
    for(KeyBoolMap::iterator it = states.begin(); it != states.end(); it++)
    {
        if(it->second)
        {
            KeyEventMap::iterator event = events.find(it->first);
            if(event == events.end())
            {
                Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("Event is not binded to anything")));
            }
            EventParser::parseEvent(event->second);
        }
    }
}

bool InputProcess::registerState(std::string name, std::string eventStr)
{
    uint32_t hash = CRC32(name.c_str(), name.length());
    KeyEventEnt eventEnt(hash, eventStr);
    KeyBoolEnt boolEnt(hash, false);
    KeyEventRes eventRes = events.insert(eventEnt);
    if(eventRes.first == events.end() || !eventRes.second)
    {
        return false;
    }
    KeyBoolRes boolRes = states.insert(boolEnt);
    if(boolRes.first == states.end() || !boolRes.second)
    {
        events.erase(eventRes.first);
        return false;
    }
    return true;
}

void InputProcess::setState(std::string name, bool state)
{
    
}

bool InputProcess::getState(std::string name)
{
    return false;
}

void InputProcess::fireEvent(std::string eventStr)
{
    EventParser::parseEvent(eventStr);
}
