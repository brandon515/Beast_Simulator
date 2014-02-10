#include "MsgEvt.h"
#include "IEventListener.h"
#include "Event_System.h"
#include <boost/shared_ptr.hpp>

class DebugOutput : public IEventListener
{
    public:
        DebugOutput();
        bool handleEvent(Event const & event);
};

typedef boost::shared_ptr<DebugOutput> DebugOutputPtr;
