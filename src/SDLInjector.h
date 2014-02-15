#include <SDL2/SDL.h>
#include "Event_System.h"
#include "KeyboardInjector.h"
#include "MsgEvt.h"
#include "Evt_Keyboard.h"
#include "Evt_CloseWindow.h"
#include "Evt_WindowFocus.h"
#include <iostream>
#include <map>
#include <boost/shared_ptr.hpp>
#include <fstream>

class SDLInjector : public KeyboardInjector 
{
    public:
        SDLInjector();
        ~SDLInjector();
        bool init();
        void tick();
        uint32_t getKey();
    private:
        SDL_Event event;
};

typedef boost::shared_ptr<SDLInjector> SDLInjectorPtr;
