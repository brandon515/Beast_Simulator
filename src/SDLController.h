#include <SDL2/SDL.h>
#include "Event_System.h"
#include "Process.h"
#include "Event.h"
#include "MsgEvt.h"
#include <iostream>
#include <map>
#include <boost/shared_ptr.hpp>
#include <json/json.h>
#include <fstream>

class SDLController : public Process
{
    public:
        SDLController();
        ~SDLController();
        void init();
        void tick();
    private:
        typedef std::map<uint32_t, Event*> EventMap;
        typedef std::pair<uint32_t, Event*> EventEnt;
        typedef std::pair<EventMap::iterator, bool> EventRes;

        SDL_Event event;
        EventMap keyEvent;
        Json::Value getRoot(std::string filename);
        uint32_t getKey();
};

typedef boost::shared_ptr<SDLController> SDLControllerPtr;
