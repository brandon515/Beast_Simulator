#ifndef EVT_JOYSTICKBUTTON_H_INCLUDED
#define EVT_JOYSTICKBUTTON_H_INCLUDED
#include "Event.h"

class Evt_JoystickButtonData : public IEventData
{
    public:
        Evt_JoystickButtonData(bool pressedDown, uint8_t but);
        bool isPressed;
        uint8_t button;
};

class Evt_JoystickButton : public Event
{
    public:
        Evt_JoystickButton(bool isPressed, uint8_t button);
        Evt_JoystickButton();
};
#endif
