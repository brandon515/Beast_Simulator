#include "EventLogger.h"

EventLogger::EventLogger()
{
    EventListenerPtr temp(this);
    if(!Event_System::getSingleton().addListener(temp, EventType(wildCardType)))
        m_log.log("EventLogger not added to listener list");
    else
        m_log.log("EventLogger added to listener list");
}

bool EventLogger::handleEvent(Event const &event)
{
    return false;
}
