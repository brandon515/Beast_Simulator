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
                m_log.log("event system cant keep up!");
            G_System::getSingleton().render();
        }
    }
}

bool Application::setup()
{
    fstream file;
    file.open(getString(g_config, "logFile").c_str(), std::ios::trunc|std::ios::out);
    file.close();
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
    //G_System::getSingleton().add(ScreenElementPtr(new Planet(200,200, 100, 0xffffff)));
    return true;
}

bool Application::handleEvent(Event const & event)
{
    EventType type = event.getType();
    if(type == Evt_Quit().getType())
    {
        playing = false;
        return true;
    }
    return false;
}
