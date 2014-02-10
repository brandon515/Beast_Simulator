#ifndef EVT_KEYBOARD_H_INCLUDED 
#define EVT_KEYBOARD_H_INCLUDED
#include "Event.h"

class Evt_KeyboardData : public IEventData
{
    public:
        Evt_KeyboardData(bool pkeyDown, uint32_t pkey):
            keyDown(pkeyDown),
            key(pkey)
        {}
        bool keyDown;
        uint32_t key;
};

class Evt_Keyboard : public Event
{
    public:
        explicit Evt_Keyboard(bool keyDown, uint32_t key):
            Event("Keyboard", IEventDataPtr( new Evt_KeyboardData(keyDown, key) ))
        {}
        explicit Evt_Keyboard():
            Event("Keyboard")
        {}
};
#endif
