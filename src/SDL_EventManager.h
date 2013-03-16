#ifndef SDL_EVENTMANAGER_H_INCLUDED
#define SDL_EVENTMANAGER_H_INCLUDED
#include <SDl\SDL.h>
#include "Event_System.h"
#include "SDL_Events.h"

class SDL_EventManager
{
    public:
        void tick();
    private:
        SDL_Event event;
};

#endif // SDL_EVENTMANAGER_H_INCLUDED
