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
            Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("SDL Injector","Opened Gamepad " + boost::lexical_cast<std::string>(i))));
            Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("SDL Injector","Gamepad name: " + name)));
            Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("SDL Injector","# of axes: " + boost::lexical_cast<std::string>(SDL_JoystickNumAxes(stick)))));
            Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("SDL Injector","# of buttons: " + boost::lexical_cast<std::string>(SDL_JoystickNumButtons(stick)))));
            Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("SDL Injector","# of balls: " + boost::lexical_cast<std::string>(SDL_JoystickNumBalls(stick)))));
            joysticks.push_back(stick);
        }
        else
        {
            Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("SDL Injector","Could not open Joystick " + boost::lexical_cast<std::string>(i))));
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
            if(event.key.repeat == 0)
            {
                Evt_Keyboard evt(event.key.state == SDL_PRESSED, event.key.keysym.sym);
                Event_System::getSingleton().trigger(evt);
            }
        }
        else if(event.type == SDL_WINDOWEVENT)
        {
            switch(event.window.event)
            {
                case SDL_WINDOWEVENT_CLOSE:
                {
                    Evt_CloseWindow evt(event.window.windowID);
                    Event_System::getSingleton().trigger(evt);
                    break;
                }
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                {
                    Evt_WindowFocus evt(event.window.windowID);
                    Event_System::getSingleton().trigger(evt);
                    break;
                }
            }
        }
        else if(event.type == SDL_JOYBUTTONDOWN || event.type == SDL_JOYBUTTONUP) 
        {
            Evt_JoystickButton evt(event.jbutton.state == SDL_PRESSED, event.jbutton.button);
            Event_System::getSingleton().trigger(evt);
        }
        else if(event.type == SDL_JOYAXISMOTION)
        {
            Evt_JoystickAxis evt(event.jaxis.axis, event.jaxis.value);
            Event_System::getSingleton().trigger(evt);
        }
    }
}


