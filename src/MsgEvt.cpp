#include "MsgEvt.h"

Evt_MsgData::Evt_MsgData(std::string name, std::string outputStr)
{
    time_t curTime = time(NULL);
    struct tm curDate = *localtime(&curTime);
    char buf[256];
    sprintf(buf, "[%02d/%02d/%d %02d:%02d:%02d] [%s]", curDate.tm_mon+1, curDate.tm_mday, curDate.tm_year+1900, curDate.tm_hour, curDate.tm_min, curDate.tm_sec, name.c_str());
    std::string dateStr(buf);
    output = dateStr + outputStr + "\n";
}
