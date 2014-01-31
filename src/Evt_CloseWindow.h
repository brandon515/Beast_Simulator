#ifndef EVT_CLOSEWINDOW_H_INCLUDED
#define EVT_CLOSEWINDOW_H_INCLUDED
#include "Event.h"

class Evt_CloseWindowData : public IEventData
{
    public:
        Evt_CloseWindowData(uint32_t pid):
            id(pid)
        {}
        uint32_t id;
};

class Evt_CloseWindow : public Event
{
    public:
        explicit Evt_CloseWindow(uint32_t pid):
            Event("Close Window", IEventDataPtr(new Evt_CloseWindowData(pid)))
        {}
        explicit Evt_CloseWindow():
           Event("Close Window")
        {}  
};

#endif
