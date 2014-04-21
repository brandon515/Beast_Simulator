#ifndef DATACONTROLLER_H_INCLUDED
#define DATACONTROLLER_H_INCLUDED
#include "IEventListener.h"
#include "DataModel.h"
#include "Evt_CloseWindow.h"
#include "Evt_WindowFocus.h"
#include "Evt_Keyboard.h"
#include "Evt_JoystickButton.h"
#include "Evt_JoystickAxis.h"
#include "Evt_Menu.h"
#include "MsgEvt.h"
#include "VirtualKeyboard.h"
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

class DataController : public IEventListener
{
    public:
        DataController(DataModelPtr data);
        bool handleEvent(Event const & event);
    private:
        DataModelPtr model;
        uint32_t currentFocusID;
};

typedef boost::shared_ptr<DataController> DataControllerPtr;
#endif
