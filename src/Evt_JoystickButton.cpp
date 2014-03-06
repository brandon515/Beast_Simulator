#include "Evt_JoystickButton.h"

Evt_JoystickButtonData::Evt_JoystickButtonData(bool pressedDown, uint8_t but):
    isPressed(pressedDown),
    button(but)
{}

Evt_JoystickButton::Evt_JoystickButton(bool isPressed, uint8_t button):
    Event("JoystickButton", IEventDataPtr( new Evt_JoystickButtonData(isPressed, button) ))
{}

Evt_JoystickButton::Evt_JoystickButton():
    Event("JoystickButton")
{}

