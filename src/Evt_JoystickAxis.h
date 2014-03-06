#ifndef EVT_JOYSTICKAXIS_H_INCLUDED
#define EVT_JOYSTICKAXIS_H_INCLUDED
#include "Event.h"

class Evt_JoystickAxisData : public IEventData
{
    public:
        Evt_JoystickAxisData(uint32_t paxis, int16_t ppos);
        uint32_t axis;
        int16_t pos;
};

class Evt_JoystickAxis : public Event
{
    public:
        Evt_JoystickAxis(uint32_t axis, int16_t pos);
        Evt_JoystickAxis();
};
#endif
