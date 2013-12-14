#ifndef EVENTLOGGER_H_INCLUDED
#define EVENTLOGGER_H_INCLUDED
#include "Event_System.h"
#include "IEventListener.h"
#include "Logging.h"
#include <boost\lexical_cast.hpp>

class EventLogger: public IEventListener
{
    public:
        EventLogger();
        ~EventLogger();
        bool handleEvent(Event const &event);
    private:
        Logging m_log;
};

#endif // EVENTLOGGER_H_INCLUDED
