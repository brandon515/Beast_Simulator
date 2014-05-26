#include "EventParser.h"

namespace EventParser{
/************************
*   FUNCTION NAME: parseEvent
*   PARAMATERS: string
*   Takes event string and parses it into an event that the function fires off in the event_system
*   if the string does not have enough arguments or no arguments at all it should return false and
*   and fire off a MsgEvt to inform the program. 
*   any arguments after the required amount are ignored and do no matter
*   if the event name does not match any that are parsed a MsgEvt should be fired off informing 
*   the program as such
************************/
bool parseEvent(std::string evt)
{
    size_t pos1 =  evt.find(" ");
    if(pos1 == std::string::npos)
    {
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("Event Parser","no spaces in event: " + evt)));
        return false;
    }
    std::string evtName = evt.substr(0, pos1);
    if(evtName.compare("move") == 0)
    {
        std::string nameStr, xStr, yStr;
        pos1 += 1;
        size_t pos2 = evt.find(" ", pos1);
        if(pos2 == std::string::npos)
        {
            Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("Event Parser","move event does not have enough arguments")));
            return false;
        }
        nameStr = evt.substr(pos1, (pos2-pos1));
        pos2 += 1;
        pos1 = evt.find(" ", pos2);
        if(pos1 == std::string::npos)
        {
            Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("Event Parser","move event does not have enough arguments")));
            return false;
        }
        xStr = evt.substr(pos2, (pos1-pos2));
        pos1 += 1;
        pos2 = evt.find(" ", pos1);
        if(pos2 == std::string::npos)
            yStr = evt.substr(pos1, (evt.length()-pos1));
        else
            yStr = evt.substr(pos1, (pos2-pos1));
        int x = stoi(xStr);
        int y = stoi(yStr);
        Event_System::getSingleton().queueEvent(EventPtr(new Evt_Move(x, y, nameStr)));
        return true;
    }
    return false;
}

bool parseEvent(lua_State *l)
{
    return false;
}}
