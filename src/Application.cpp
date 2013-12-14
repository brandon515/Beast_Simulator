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
        while(!ViewSystem::getSingleton().isEmpty())
        {
            if(!Event_System::getSingleton().tick(infMill))
                m_log.log("event system cant keep up!");
            ViewSystem::getSingleton().tick();
        }
    }
}

bool Application::setup()
{
    fstream file;
    file.open(getString(g_config, "logFile").c_str(), std::ios::trunc|std::ios::out);
    file.close();
    /*EventListenerPtr evtPtr(this);
    if(!Event_System::getSingleton().addListener(evtPtr, Evt_Quit().getType()))
    {
        m_log.log("application not added to listener list");
        return false;
    }
    m_log.log("Event System successfully started and application added to listeners list");*/

    if(!ViewSystem::getSingleton().addView(HumanViewPtr(new HumanView())))
    {
        m_log.log("Human View not added to View System");
        return false;
    }
    m_log.log("Human View added to View System");
    (new TestObject())->init();

    /*if(!Event_System::getSingleton().addListener(humanView, Evt_Keyboard().getType()))
    {
        m_log.log("Human View not added to Event System");
        return false;
    }
    m_log.log("Human View added to Event System");*/

    return true;
}
