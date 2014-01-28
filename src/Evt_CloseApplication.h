#include "Event.h"

class Evt_CloseApplication : public Event
{
    public:
        explicit Evt_CloseApplication():
            Event("Close Applicaiton")
        {}
};
