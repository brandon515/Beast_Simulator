#include "Application.h"

Application::Application()
{
    //
}

Application::~Application()
{
    //
}

void Application::go()
{
    if(setup())
    {
        bool playing = true;
        while(playing == true)
        {
            G_System::getSingleton().render();
        }
    }
}

bool Application::setup()
{
    if(SDL_Init(SDL_INIT_EVERYTHING)==-1 || TTF_Init() == -1)
    {
        cerr << "sdl failed";
        return false;
    }
    if(!G_System::getSingleton().setup())
    {
        cerr << "graphics system failed";
        return false;
    }
    return true;
}
