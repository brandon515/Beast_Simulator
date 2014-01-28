#include "IEventListener.h"
#include "Evt_CloseApplication.h"
#include <boost/shared_ptr.hpp>

class ApplicationController : public IEventListener
{
    public:
        ApplicationController();
        bool handleEvent(Event const & event);
        bool shutdown();
    private:
        bool shutOff;
};

typedef boost::shared_ptr<ApplicationController> ApplicationControllerPtr;
