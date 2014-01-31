#ifndef EVT_CLOSEAPPLICATION
#define EVT_CLOSEAPPLICATION
#include "Event.h"

class Evt_CloseApplication : public Event
{
    public:
        explicit Evt_CloseApplication():
            Event("Close Applicaiton")
        {}
};
#endif
