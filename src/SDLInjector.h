#include <SDL2/SDL.h>
#include "MsgEvt.h"
#include "Event_System.h"
#include "KeyboardInjector.h"
#include "MsgEvt.h"
#include "Evt_Keyboard.h"
#include "Evt_CloseWindow.h"
#include "Evt_WindowFocus.h"
#include "Evt_JoystickButton.h"
#include "Evt_JoystickAxis.h"
#include <iostream>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <fstream>
#include <boost/lexical_cast.hpp>

class SDLInjector : public KeyboardInjector 
{
    public:
        SDLInjector();
        ~SDLInjector();
        bool init();
        void tick();
        uint32_t getKey();
    private:
        typedef std::vector<SDL_Joystick*> JoystickList;

        SDL_Event event;
        JoystickList joysticks;
};

typedef boost::shared_ptr<SDLInjector> SDLInjectorPtr;
