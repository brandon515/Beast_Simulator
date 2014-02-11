#include <SDL2/SDL.h>
#include "Event_System.h"
#include "Event.h"
#include "KeyboardInjector.h"
#include "MsgEvt.h"
#include "Evt_Keyboard.h"
#include "Evt_CloseWindow.h"
#include "Evt_WindowFocus.h"
#include <iostream>
#include <map>
#include <boost/shared_ptr.hpp>
#include <fstream>

class SDLInjector : public KeyboardInjector 
{
    public:
        SDLInjector();
        ~SDLInjector();
        bool init();
        void tick();
        uint32_t getKey();
    private:
        typedef std::map<uint32_t, Event*> EventMap;
        typedef std::pair<uint32_t, Event*> EventEnt;
        typedef std::pair<EventMap::iterator, bool> EventRes;

        SDL_Event event;
        EventMap keyEvent;
};

typedef boost::shared_ptr<SDLInjector> SDLInjectorPtr;
