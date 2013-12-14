#ifndef IGAMEOBJECT_H_INCLUDED
#define IGAMEOBJECT_H_INCLUDED
#include "Methods.h"
#include <boost\shared_ptr.hpp>
#include <vector>
#include "GameInterface.h"

class IGameObject
{
    public:
        IGameObject();
        virtual ~IGameObject();
        bool reg(std::string hashStr);
        virtual void init() = 0;
        virtual void update() = 0;
        std::vector<uint32_t> types;
        uint32_t id;
};

typedef boost::shared_ptr<IGameObject> IGameObjectPtr;

#endif // IGAMEOBJECT_H_INCLUDED
