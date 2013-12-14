#ifndef IEVENTLISTENER_H_INCLUDED
#define IEVENTLISTENER_H_INCLUDED
#include "Event.h"
#include <iostream>

class IEventListener
{
    public:
        explicit IEventListener(std::string ID){uid = CRC32(ID.c_str(), ID.length());}
        virtual ~IEventListener(){}
        //return false if event is not consumed, true if it is
        virtual bool handleEvent(Event const & event) = 0;
    private:
        uint32_t uid;
};

#endif // IEVENTLISTENER_H_INCLUDED
