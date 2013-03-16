#include "SDL_EventManager.h"

void SDL_EventManager::tick()
{
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            Evt_Quit *sdlEvent;
            EventPtr msg(sdlEvent);
            Event_System::getSingleton().queueEvent(msg);
        }
    }
}
