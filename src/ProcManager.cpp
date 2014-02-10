#include "ProcManager.h"

ProcManager::ProcManager()
{
    allPaused = false;
}

bool ProcManager::addProcess(ProcessPtr obj, std::string group)
{
    //Check ProcessMap to see if obj already exists
    uint32_t hashGroup = CRC32(group.c_str(), group.length());
    for(ProcessMap::iterator tempIt = processes.begin(); tempIt != processes.end(); tempIt++)
    {
        ProcessList pro = tempIt->second;
        for(ProcessList::iterator listIt = pro.begin(); listIt != pro.end(); listIt++)
        {
            if(listIt->get()->getHashName() == obj->getHashName())
            {
                Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("Proccess attempted to be added to two different groups")));
                return false;
            }
        }
    }
    //If it doesnt yet exist in the system, add it
    ProcessMap::iterator it = processes.find(hashGroup);
    if(it == processes.end())
    {
        //it's being added to a group that doesnt exist yet so we create a new group and add it to the ProcessMap
        ProcessRes res = processes.insert(ProcessEnt(hashGroup, ProcessList()));
        if(res.first == processes.end() || res.second == false)
        {
            Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("New Group was not created for " + group)));
            return false;
        }
        else
        {
            Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("New list added for group named: " + group)));
        }
        //add the group to the boolean map
        GroupEnt gEnt(hashGroup, true);
        GroupRes gRes = groups.insert(gEnt);
        if(gRes.first == groups.end() || gRes.second == false)
        {
            Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("Group boolen could not be added for group " + group)));
            processes.erase(res.second);
            return false;
        }
        it = res.first;
    }
    ProcessList &cur = (*it).second;
    //Add the process to the list
    if(obj.get() == NULL)
    {
        return false;
    }
    if(!obj->init())
    {
        return false;
    }
    cur.push_back(obj);
    return true;
}

bool ProcManager::pauseProcess(std::string processName)
{
    uint32_t hash = CRC32(processName.c_str(), processName.length());
    ProcessMap::iterator it;
    for(it = processes.begin(); it != processes.end(); it++)
    {
        ProcessList pro = it->second;
        for(ProcessList::iterator lit = pro.begin(); lit != pro.end(); lit++)
        {
            if(lit->get()->getHashName() == hash)
            {
                lit->get()->isPaused = true;
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
    GroupMap::iterator it = groups.find(groupHash);
    it->second = false;
}

bool ProcManager::detachProcess(std::string name)
{
    uint32_t hash = CRC32(name.c_str(), name.length());
    for(ProcessMap::iterator it = processes.begin(); it != processes.end(); it++)
    {
        ProcessList pro = it->second;
        for(ProcessList::iterator prit = pro.begin(); prit != pro.end(); prit++)
        {
            if(prit->get()->getHashName() == hash)
            {
                pro.erase(prit);
                return true;
            }
        }
    }
    return false;
}

void ProcManager::resumeAllProcesses()
{
    allPaused = false;
}

bool ProcManager::resumeGroup(std::string groupName)
{
    uint32_t hash = CRC32(groupName.c_str(), groupName.length());
    GroupMap::iterator it = groups.find(hash);
    if(it != groups.end())
    {
        it->second = true;
        return true;
    }
    else
    {
        return false;
    }
}

bool ProcManager::resumeProcess(std::string name)
{
    uint32_t hash = CRC32(name.c_str(), name.length());
    for(ProcessMap::iterator it = processes.begin(); it != processes.end(); it++)
    {
        ProcessList pro = it->second;
        for(ProcessList::iterator priat = pro.begin(); priat != pro.end(); priat++)
        {
            if(priat->get()->getHashName() == hash)
            {
                priat->get()->isPaused = false;
                return true;
            }
        }
    }
    return false;
}

void ProcManager::tick()
{
    if(!allPaused)
    {
        for(ProcessMap::iterator it = processes.begin(); it != processes.end(); it++)
        {
            ProcessList pro = it->second;
            if(pro.empty())
            {
                std::cout << "it's empty!";
                break;
            }
            if(groups.find(it->first)->second == true)
            {
                for(ProcessList::iterator lit = pro.begin(); lit != pro.end(); lit++)
                {
                    if(!lit->get()->isPaused)
                    {
                        if(lit->get()->doKill())
                        {
                            pro.erase(lit);
                            continue;
                        }
                        lit->get()->tick();
                    }
                }
            }
        }
    }
}
