#include "IGameObject.h"

bool IGameObject::reg(std::string hashStr)
{
    uint32_t hashVal = CRC32(hashStr.c_str(), hashStr.length());
    if(types.empty() == false)
    {
        for(std::vector<uint32_t>::iterator it = types.begin(); it != types.end(); it++)
        {
            if(hashVal == (*it))
                return false;
        }
    }
    types.push_back(hashVal);
    return true;
}
