#ifndef GAMEEVENTS_H_INCLUDED
#define GAMEEVENTS_H_INCLUDED
#include "Event.h"

class Evt_Quit : public Event
{
    public:
        explicit Evt_Quit():
            Event("exit program")
            {}
};

class Evt_MoveData : public IEventData
{
    public:
        Evt_MoveData(Sint16 px, Sint16 py, uint32_t pID):
            x(px),
            y(py),
            ID(pID)
        {}
        ~Evt_MoveData(){}
        Sint16 x, y;
        uint32_t ID;
};

class Evt_Move : public Event
{
    public:
        explicit Evt_Move(Sint16 x, Sint16 y, uint32_t ID):
            Event("move creature", IEventDataPtr(new Evt_MoveData(x,y, ID)))
            {}
        explicit Evt_Move():
            Event("move creature")
            {}

};

#endif // GAMEEVENTS_H_INCLUDED
