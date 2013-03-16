#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED
#include <string>
#include "Methods.h"
#include "G_System.h"
#include "Event_System.h"
#include "SDL_EventManager.h"
#include "SDL_Events.h"
#include <SDL\SDL.h>
#include <SDL\SDL_ttf.h>
class Application : public IEventListener
{
    public:
        Application();
        ~Application();
        void go();
        bool handleEvent(Event const & event);
    private:
        SDL_EventManager mang;
        bool setup();
        bool playing;
};

#endif // APPLICATION_H_INCLUDED
