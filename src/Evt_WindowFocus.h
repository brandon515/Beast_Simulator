#ifndef EVT_WINDOWFOCUS_H_INCLUDED
#define EVT_WINDOWFOCUS_H_INCLUDED
#include "Event.h"

class Evt_WindowFocusData : public IEventData
{
    public:
        Evt_WindowFocusData(uint32_t pid):
            id(pid)
        {}
        uint32_t id;
};

class Evt_WindowFocus : public Event
{
    public:
        Evt_WindowFocus(uint32_t pid):
            Event("Focus Changed", IEventDataPtr(new Evt_WindowFocusData(pid)))
        {}
        Evt_WindowFocus():
            Event("Focus Changed", IEventDataPtr(new Evt_WindowFocusData(0)))
        {}
};

#endif
