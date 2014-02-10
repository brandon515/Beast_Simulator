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

class Evt_MouseMoveData : public IEventData
{
    public:
        Evt_MouseMoveData(Sint16 px, Sint16 py):
            x(px),
            y(py)
        {}
        Sint16 x, y;
};

class Evt_MouseMove : public Event
{
    public:
        explicit Evt_MouseMove(Sint16 x, Sint16 y):
            Event("MouseMoved", IEventDataPtr(new Evt_MouseMoveData(x,y)))
        {}
        explicit Evt_MouseMove():
            Event("MouseMoved")
        {}
};

class Evt_MouseButtonData : public IEventData
{
    public:
        Evt_MouseButtonData(bool pbuttonDown, uint8_t pbutton, uint16_t px, uint16_t py):
            buttonDown(pbuttonDown),
            button(pbutton),
            x(px),
            y(py)
        {}
        bool buttonDown;
        uint8_t button;
        uint16_t x, y;
};

class Evt_MouseButton : public Event
{
    public:
        Evt_MouseButton(bool buttonDown, uint8_t button, uint16_t x, uint16_t y):
            Event("MouseButton", IEventDataPtr(new Evt_MouseButtonData(buttonDown, button, x, y)))
        {}
        Evt_MouseButton():
            Event("MouseButton")
        {}
};

#endif // GAMEEVENTS_H_INCLUDED
