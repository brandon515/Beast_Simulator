#include "IEventListener.h"
#include "Evt_Keyboard.h"
#include "Evt_JoystickAxis.h"
#include "Evt_JoystickButton.h"
#include "Evt_Context.h"
#include "MsgEvt.h"
#include <json/json.h>
#include "InputProcess.h"
#include "ProcManager.h"
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

class InputController : public IEventListener
{
    public:
        InputController();
        ~InputController(){}
        bool handleEvent(Event const & event);
        InputProcessPtr getInputProcess();
        Json::Value getRoot(std::string filename);
    private:
        
        InputProcessPtr input;
        Json::Value controls;
};

typedef boost::shared_ptr<InputController> InputControllerPtr;
