#ifndef EVT_MOVE_H_INCLUDED
#define EVT_MOVE_H_INCLUDED
#include "Event.h"
#include "Methods.h"

class Evt_MoveData : public IEventData
{
    public:
        Evt_MoveData(int16_t px, int16_t py, std::string name);
        ~Evt_MoveData(){}
        int16_t x, y;
        uint32_t ID;
};

class Evt_Move : public Event
{
    public:
        explicit Evt_Move(int16_t x, int16_t y, std::string name):
            Event("move creature", IEventDataPtr(new Evt_MoveData(x, y, name)))
            {}
        explicit Evt_Move():
            Event("move creature")
            {}

};
#endif
