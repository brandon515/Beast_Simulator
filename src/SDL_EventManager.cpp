#include "SDL_EventManager.h"

void SDL_EventManager::tick()
{
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            m_log.log("SDL_Quit event realized, shutting down");
            Event_System::getSingleton().queueEvent(EventPtr(new Evt_Quit()));
        }
    }
}
