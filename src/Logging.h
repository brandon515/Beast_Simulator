#ifndef LOGGING_H_INCLUDED
#define LOGGING_H_INCLUDED
#include <fstream>
#include <cassert>
#include "Methods.h"
#include "Event_System.h"
#include "IEventListener.h"
#include <sstream>
#include "MsgEvt.h"


class Logging : public IEventListener
{
    public:
        Logging();
        ~Logging();
        bool handleEvent(Event const & event);
    private:
        fstream file;
};

#endif // LOGGING_H_INCLUDED
