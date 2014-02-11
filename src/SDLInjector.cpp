#include "SDLInjector.h"

SDLInjector::SDLInjector():
    KeyboardInjector("SDLInjector")
{}

SDLInjector::~SDLInjector()
{}

bool SDLInjector::init()
{
    return true;
}

uint32_t SDLInjector::getKey()
{
    uint32_t key = 0;
    while(!key)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_KEYUP)
            {
                key = event.key.keysym.sym;
            }
        }
    }
    return key;
}

void SDLInjector::tick()
{
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
        {
            EventPtr evt(new Evt_Keyboard(event.key.state == SDL_PRESSED, event.key.keysym.sym));
            Event_System::getSingleton().queueEvent(evt);
        }
        else if(event.type == SDL_WINDOWEVENT)
        {
            switch(event.window.event)
            {
                case SDL_WINDOWEVENT_CLOSE:
                {
                    EventPtr evt(new Evt_CloseWindow(event.window.windowID));
                    Event_System::getSingleton().queueEvent(evt);
                    break;
                }
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                {
                    EventPtr evt(new Evt_WindowFocus(event.window.windowID));
                    Event_System::getSingleton().queueEvent(evt);
                    break;
                }
            }
        }
    }
}


