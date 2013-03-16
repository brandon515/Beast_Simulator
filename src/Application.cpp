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
        playing = true;
        while(playing == true)
        {
            mang.tick();
            if(!Event_System::getSingleton().tick(infMill))
                cerr << "placeholder";//Logging::getSingleton().log("event system not able to flush the queue, consider increasing the time");
            G_System::getSingleton().render();
        }
    }
}

bool Application::setup()
{
    //TODO create logging class and replace cerr
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
    IEventListener *thisPtr = this;
    EventListenerPtr safeThisPtr(thisPtr);
    if(!Event_System::getSingleton().addListener(safeThisPtr, Evt_Quit().getType()))
    {
        cerr << "application not added to listener list";
        return false;
    }
    return true;
}

bool Application::handleEvent(Event const & event)
{
    EventType type = event.getType();
    if(type.getIdent() == Evt_Quit().getType().getIdent())
    {
        playing = false;
    }
}
