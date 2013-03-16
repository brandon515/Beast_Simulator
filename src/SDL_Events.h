#ifndef SDL_EVENTS_H_INCLUDED
#define SDL_EVENTS_H_INCLUDED
#include "Event.h"

class Evt_Quit : public Event
{
    public:
        explicit Evt_Quit():
            Event("exit program")
            {}
};

#endif // SDL_EVENTS_H_INCLUDED
