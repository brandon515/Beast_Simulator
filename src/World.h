#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED
#include <boost\shared_ptr.hpp>
#include <map>
#include <vector>
#include "IGameObject.h"
#include "Methods.h"
#include "Logging.h"
#include "GameEvents.h"
#include "Event_System.h"

typedef boost::shared_ptr<IGameObject> IGameObjectPtr;

class World
{
    public:

        static World & getSingleton();
        template<typename _T>
        std::map<uint32_t, _T> getTypeList(std::string typeStr);
        uint32_t add(IGameObjectPtr obj);
        bool createFromFile(std::string filename);
        void Tick();

    private:

        //singleton methods

        World(){curId = 0;}
        World(World const &){}
        bool operator=(World const &);

        //typedefs

        typedef std::map<uint32_t, IGameObjectPtr> IGameObjectList;
        typedef std::pair<IGameObjectList::iterator, bool> IGameObjectRes;
        typedef std::pair<uint32_t, IGameObjectPtr> IGameObjectEnt;

        //member variables

        IGameObjectList worldMembers;
        uint32_t curId;
};

#endif // WORLD_H_INCLUDED
