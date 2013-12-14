#include "SDL_EventManager.h"

void SDL_EventManager::tick()
{
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            Event_System::getSingleton().queueEvent(EventPtr(new Evt_Quit()));
        }
        else if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
        {
            SDLKey key = event.key.keysym.sym;
            uint32_t eventKey = boost::lexical_cast<uint32_t>(key);
            bool keyDown = (event.type == SDL_KEYDOWN);
            Event_System::getSingleton().queueEvent(EventPtr(new Evt_Keyboard(keyDown, eventKey)));
        }
        else if(event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
        {
            bool buttonDown = (event.button.state == SDL_PRESSED);
            uint8_t button = event.button.button;
            uint16_t x = event.button.x;
            uint16_t y = event.button.y;
            Event_System::getSingleton().queueEvent(EventPtr(new Evt_MouseButton(buttonDown, button, x, y)));
        }
        else if(event.type ==SDL_MOUSEMOTION)
        {
            uint16_t x = event.motion.x, y = event.motion.y;
            Event_System::getSingleton().queueEvent(EventPtr(new Evt_MouseMove(x, y)));
        }
    }
}
