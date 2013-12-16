#ifndef HUMANVIEW_H_INCLUDED
#define HUMANVIEW_H_INCLUDED
#include <boost/serialization/map.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/make_shared.hpp>
#include <fstream>
#include "Logging.h"
#include "globals.h"
#include "GameEvents.h"
#include "IEventListener.h"
#include <map>
#include <vector>


enum VirtualKeys
{
    VK_EXIT,
    VK_MAPRIGHT,
    VK_MAPLEFT,
    VK_MAPUP,
    VK_MAPDOWN
};

//Purpose: To handle all human interaction with the system. it's only interaction with the system must be firing events and reciving events

class HumanView : public IEventListener
{
    public:
        HumanView(std::string playerName);
        ~HumanView();
        bool init();
        void tick();
        bool handleEvent(Event const & event);
    private:
        std::string plName;
        Logging log;
};

typedef boost::shared_ptr<HumanView> HumanViewPtr;

#endif // HUMANVIEW_H_INCLUDED
