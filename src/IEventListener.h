#ifndef IEVENTLISTENER_H_INCLUDED
#define IEVENTLISTENER_H_INCLUDED
#include "Event.h"
#include <iostream>

class IEventListener
{
    public:
        explicit IEventListener(){}
        virtual ~IEventListener(){}
        //return false if event is not consumed, true if it is
        virtual bool handleEvent(Event const & event) = 0;
};

#endif // IEVENTLISTENER_H_INCLUDED
