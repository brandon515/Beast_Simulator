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
            m_appLayerEvents.tick();
            if(!Event_System::getSingleton().tick(infMill))
                m_log.log("event system not able to flush the queue, consider increasing the time");
            G_System::getSingleton().render();
        }
    }
}

bool Application::setup()
{
    if(SDL_Init(SDL_INIT_EVERYTHING)==-1 || TTF_Init() == -1)
    {
        m_log.log("SDL failed to setup");
        return false;
    }
    m_log.log("SDL and TTF sub-system successfully started");
    if(!G_System::getSingleton().setup())
    {
        m_log.log("graphics system failed");
        return false;
    }
    m_log.log("Graphics system successfully started");
    IEventListener *thisPtr = this;
    EventListenerPtr safeThisPtr(thisPtr);
    if(!Event_System::getSingleton().addListener(safeThisPtr, Evt_Quit().getType()))
    {
        m_log.log("application not added to listener list");
        return false;
    }
    m_log.log("Event System successfully started and application added to listeners list");
    return true;
}

bool Application::handleEvent(Event const & event)
{
    EventType type = event.getType();
    if(type.getIdent() == Evt_Quit().getType().getIdent())
    {
        playing = false;
        return true;
    }
    return false;
}
