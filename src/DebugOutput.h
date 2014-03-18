#include "MsgEvt.h"
#include "Evt_CloseApplication.h"
#include "Evt_CloseWindow.h"
#include "Evt_JoystickAxis.h"
#include "Evt_JoystickButton.h"
#include "Evt_Keyboard.h"
#include "Evt_Move.h"
#include "Evt_WindowFocus.h"
#include "IEventListener.h"
#include "Event_System.h"
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

class DebugOutput : public IEventListener
{
    public:
        DebugOutput();
        bool handleEvent(Event const & event);
};

typedef boost::shared_ptr<DebugOutput> DebugOutputPtr;
