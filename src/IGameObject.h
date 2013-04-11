#ifndef IGAMEOBJECT_H_INCLUDED
#define IGAMEOBJECT_H_INCLUDED
#include "Methods.h"
#include <vector>

class IGameObject
{
    public:
        bool reg(std::string hashStr);
        virtual void update() = 0;
        uint32_t id;
        std::vector<uint32_t> types;
};

#endif // IGAMEOBJECT_H_INCLUDED
