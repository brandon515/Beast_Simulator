#include "ProcManager.h"

bool ProcManager::addProcess(ProcessPtr obj, std::string group = "NONE")
{
    uint32_t hashGroup = CRC32(group.c_str(), group.length());
    ProcessMap::iterator it = processes.find(hashGroup);
    ProcessList *cur;
    if(it == std::map::end)
    {
        cur = new ProcessList();
        ProcessEnt ent(hashGroup, cur);
        ProcessRes res = processes.insert(ent);
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("New list added for group named: " + group)));
    }
    if(obj.get() == NULL)
    {
        return false;
    }
    cur->push_back(obj);
    return true;
}
