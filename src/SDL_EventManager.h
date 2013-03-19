#ifndef SDL_EVENTMANAGER_H_INCLUDED
#define SDL_EVENTMANAGER_H_INCLUDED
#include <SDl\SDL.h>
#include "Event_System.h"
#include "Logging.h"
#include "GameEvents.h"

class SDL_EventManager
{
    public:
        void tick();
    private:
        SDL_Event event;
        Logging m_log;
};

#endif // SDL_EVENTMANAGER_H_INCLUDED
