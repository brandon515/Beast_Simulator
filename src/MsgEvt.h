#include "Event.h"
#include <ctime>
#include <string>

class Evt_MsgData : public IEventData
{
    public:
        Evt_MsgData(std::string outputStr)
        {
            time_t curTime = time(NULL);
            struct tm curDate = *localtime(&curTime);
            char buf[256];
            sprintf(buf, "[%d %d %d, %d:%d:%d:] ", curDate.tm_mon, curDate.tm_mday, curDate.tm_year, curDate.tm_hour, curDate.tm_min, curDate.tm_sec);
            std::string dateStr(buf);
            output = dateStr + outputStr;
        }
        ~Evt_MsgData(){}
        std::string output;
};

class MsgEvt : public Event
{
    public:
        explicit MsgEvt(std::string output):
            Event("Output Message", IEventDataPtr(new Evt_MsgData(output)))
            {}
        explicit MsgEvt():
            Event("NULL Output Message")
            {}

};