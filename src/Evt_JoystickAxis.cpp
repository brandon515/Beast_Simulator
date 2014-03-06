#include "Evt_JoystickAxis.h"

Evt_JoystickAxisData::Evt_JoystickAxisData(uint32_t paxis, int16_t ppos):
    axis(paxis),
    pos(ppos)
{}

Evt_JoystickAxis::Evt_JoystickAxis(uint32_t axis, int16_t pos):
    Event("Joystick Axis", IEventDataPtr(new Evt_JoystickAxisData(axis, pos)))
{}

Evt_JoystickAxis::Evt_JoystickAxis():
    Event("Joystick Axis")
{}

