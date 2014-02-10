#include "IEventListener.h"
#include "Evt_CloseApplication.h"
#include "DataModel.h"
#include "Evt_CloseWindow.h"
#include <boost/shared_ptr.hpp>

class ApplicationController : public IEventListener
{
    public:
        ApplicationController(DataModelPtr dat);
        bool handleEvent(Event const & event);
        bool shutdown();
    private:
        bool shutOff;
        DataModelPtr model;
};

typedef boost::shared_ptr<ApplicationController> ApplicationControllerPtr;
