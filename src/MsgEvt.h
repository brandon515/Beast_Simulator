#ifndef MSGEVT_H_INCLUDED
#define MSGEVT_H_INCLUDED
#include "Event.h"
#include <ctime>
#include <string>

class Evt_MsgData : public IEventData
{
    public:
        Evt_MsgData(std::string name, std::string outputStr);
        ~Evt_MsgData(){}
        std::string output;
};

class MsgEvt : public Event
{
    public:
        explicit MsgEvt(std::string name, std::string output):
            Event("Output Message", IEventDataPtr(new Evt_MsgData(name, output)))
            {}
        explicit MsgEvt():
            Event("Output Message")
            {}

};
#endif
