#ifndef SDL_EVENTMANAGER_H_INCLUDED
#define SDL_EVENTMANAGER_H_INCLUDED
#include <SDl\SDL.h>
#include <boost\lexical_cast.hpp>
#include "Event_System.h"
#include "Logging.h"
#include "GameEvents.h"

class SDL_EventManager
{
    public:
        void tick();
    private:
        SDL_Event event;
};

#endif // SDL_EVENTMANAGER_H_INCLUDED
