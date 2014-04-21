#ifndef EVT_CONTEXT_H_INCLUDED
#define EVT_CONTEXT_H_INCLUDED
#include "Event.h"


class Evt_ContextData : public IEventData
{
    public:
        Evt_ContextData(std::string name);
        ~Evt_ContextData(){}
        std::string contextStr;
        uint32_t contextID;
};

class Evt_Context : public Event
{
    public:
        Evt_Context(std::string name);
        Evt_Context();
        ~Evt_Context(){}
};
#endif
