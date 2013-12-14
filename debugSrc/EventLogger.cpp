#include "EventLogger.h"

EventLogger::EventLogger()
{
    //
}

EventLogger::~EventLogger()
{
    //
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
    else if(event.getType() == Evt_Keyboard().getType())
    {
        Evt_KeyboardData *dat = event.getDataPtr<Evt_KeyboardData>();
        std::string msg = "Keyboard button with the ID " + boost::lexical_cast<std::string>(dat->key)\
            + " has been " + (dat->keyDown ? "pressed" : "released");
        m_log.log(msg);
    }
    else if(event.getType() == Evt_MouseButton().getType())
    {
        Evt_MouseButtonData *dat = event.getDataPtr<Evt_MouseButtonData>();
        std::string msg = "Mouse Button with the ID " + boost::lexical_cast<std::string>(dat->button) + " was "\
            + (dat->buttonDown ? "pressed" : "released") + " at (" + boost::lexical_cast<std::string>(dat->x) + ","\
            + boost::lexical_cast<std::string>(dat->y) + ")";
        m_log.log(msg);
    }
    return false;
}
