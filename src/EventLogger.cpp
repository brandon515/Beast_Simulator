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
    if(event.getType() == Evt_Quit().getType())
        m_log.log("SDL_Quit event realized, shutting down");
    else if(event.getType() == Evt_Move().getType())
    {
        Evt_MoveData *dat = event.getDataPtr<Evt_MoveData>();
        std::string msg = "object with the ID " + boost::lexical_cast<std::string>(dat->ID) + " has moved "\
        + boost::lexical_cast<std::string>(dat->x) + " units on the x axis and " + boost::lexical_cast<std::string>(dat->y) + " on the y axis";
        m_log.log(msg);
    }
    return false;
}
