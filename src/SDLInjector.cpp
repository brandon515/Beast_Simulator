#include "SDLInjector.h"

SDLInjector::SDLInjector():
    KeyboardInjector("SDLInjector")
{}

SDLInjector::~SDLInjector()
{
    for(JoystickList::iterator it = joysticks.begin(); it != joysticks.end(); it++)
    {
        if(SDL_JoystickGetAttached(*it))
            SDL_JoystickClose(*it);
    }
}

bool SDLInjector::init()
{
    SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    uint32_t numOfJoysticks = SDL_NumJoysticks();
    for(uint32_t i = 0; i < numOfJoysticks; i++)
    {
        SDL_Joystick *stick;
        stick = SDL_JoystickOpen(i);
        if(stick != NULL)
        {
            std::string name(SDL_JoystickNameForIndex(i));
            Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("Opened Gamepad " + boost::lexical_cast<std::string>(i))));
            Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("Gamepad name: " + name)));
            Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("# of axes: " + boost::lexical_cast<std::string>(SDL_JoystickNumAxes(stick)))));
            Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("# of buttons: " + boost::lexical_cast<std::string>(SDL_JoystickNumButtons(stick)))));
            Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("# of balls: " + boost::lexical_cast<std::string>(SDL_JoystickNumBalls(stick)))));
            joysticks.push_back(stick);
        }
        else
        {
            Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("Could not open Joystick " + boost::lexical_cast<std::string>(i))));
        }
    }
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
        else if(event.type == SDL_JOYBUTTONDOWN || event.type == SDL_JOYBUTTONUP) 
        {
            EventPtr evt(new Evt_JoystickButton(event.jbutton.state == SDL_PRESSED, event.jbutton.button));
            Event_System::getSingleton().queueEvent(evt);
        }
        else if(event.type == SDL_JOYAXISMOTION)
        {
            EventPtr evt(new Evt_JoystickAxis(event.jaxis.axis, event.jaxis.value));
            Event_System::getSingleton().queueEvent(evt);
        }
    }
}


