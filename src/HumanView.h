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
<<<<<<< HEAD
=======
#include "IEventListener.h"
>>>>>>> 3e7a77d718251ff59f88a128d6f1b33dd3a6cfb6
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

<<<<<<< HEAD
class HumanView :public IEventListener
=======
class HumanView : public IEventListener
>>>>>>> 3e7a77d718251ff59f88a128d6f1b33dd3a6cfb6
{
    public:
        HumanView(std::string playerName);
        ~HumanView();
        bool init();
        void tick();
        bool handleEvent(Event const & event);
    private:
<<<<<<< HEAD
        //member variables

        Logging log;

=======
        std::string plName;
        Logging log;
>>>>>>> 3e7a77d718251ff59f88a128d6f1b33dd3a6cfb6
};

typedef boost::shared_ptr<HumanView> HumanViewPtr;

#endif // HUMANVIEW_H_INCLUDED
