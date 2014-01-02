#include "ProcManager.h"

bool ProcManager::addProcess(ProcessPtr obj, std::string group = "NONE")
{
    uint32_t hashGroup = CRC32(group.c_str(), group.length());
    for(ProcessMap::iterator tempIt = processes.begin(); tempIt != processes.end(); tempIt++)
    {
        ProcessList pro = tempIt->second;
        for(ProcessList::iterator listIt = pro.begin(); listIt != pro.end(); listIt++)
        {
            if(listIt->name == obj->name)
            {
                Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("Proccess attempted to be added to two different groups")));
                return false;
            }
        }
    }
    ProcessMap::iterator it = processes.find(hashGroup);
    if(it == std::map::end)
    {
        ProcessEnt ent(hashGroup, ProcessList());
        ProcessRes res = processes.insert(ent);
        if(res->first && res->second != std::map::end)
            Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("New list added for group named: " + group)));
        else
        {
            Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("New Group was not created for " + group)));
            return false;
        }
        it = res->second;
    }
    ProcessList cur = it->second;
    if(obj.get() == NULL)
    {
        return false;
    }
    cur->push_back(obj);
    return true;
}

bool ProcManager::pauseProcess(std::string name)
{
    uint32_t hash = CRC32(name.c_str(), name.length());
    ProcessMap::iterator it;
    for(it = processes.begin(); it != processes.end(); it++)
    {
        ProcessList pro = it->second;
        for(ProcessList::iterator lit = pro.begin(); lit != pro.end(); lit++)
        {
            if(lit->name == hash)
            {
                lit->isPaused = true;
                return true;
            }
        }
    }
    return false;
}

void ProcManager::pauseAllProcesses()
{
    allPaused = true;
}

void ProcManager::pauseGroup(std::string groupName)
{
    uint32_t groupHash = CRC32(groupName.c_str(), groupName.length());
    GroupMap::iterator it = map.find(groupHash);
    it->second = false;
}

void ProcManager::tick()
{
    if(!allPaused)
    {
        for(ProcessMap::iterator it = processes.begin(); it != processes.end(); it++)
        {
            ProcessList pro = it->second;
            for(ProcessList::iterator lit = pro.begin(); lit != pro.end(); lit++)
            {
                if(!lit->isPaused)
                {
                    lit->tick();
                }
            }
        }
    }
}
