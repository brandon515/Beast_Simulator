#include "World.h"

World & World::getSingleton()
{
    static World ret;
    return ret;
}

template<typename _T>
        std::map<uint32_t, _T> World::getTypeList(std::string typeStr)
{
    std::map<uint32_t, _T> ret;
    uint32_t hashVal = CRC32(typeStr.c_str(), typeStr.length());
    //go through the map of objects
    for(IGameObjectList::iterator it = worldMembers.begin(); it != worldMembers.end(); it++)
    {
        //obtain the vector of types
        IGameObjectPtr member = (*it).second;
        std::vector<uint32_t> types = (*member).types;
        //iterate through the list and look to see if a type matches the requested one
        for(std::vector<uint32_t>::iterator tyIt = types.begin(); tyIt != types.end(); tyIt++)
        {
            if(hashVal == (*tyIt))
            {
                std::pair<uint32_t, _T> retEnt((*it).first, reinterpret_cast<_T>((*it).second));
                std::pair<typename std::map<uint32_t, _T>::iterator, bool> retRes;
                retRes = ret.insert(retEnt);
                if(retRes.second == false || retRes.first == types.end())
                {
                    std::string logMsg = "failed to retrieve the type " + typeStr;
                    Logging().log(logMsg);
                    Event_System::getSingleton().queueEvent(EventPtr(new Evt_Quit()));
                }
                //found it, no need to keep looking
                break;
            }
        }
    }
    return ret;
}
