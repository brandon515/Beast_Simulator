#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED
#include <string>
#include "Methods.h"
#include "G_System.h"
#include <SDL\SDL.h>
#include <SDL\SDL_ttf.h>
class Application
{
    public:
        Application();
        ~Application();
        void go();
        //E_System events;
    private:
        bool setup();
};

#endif // APPLICATION_H_INCLUDED
