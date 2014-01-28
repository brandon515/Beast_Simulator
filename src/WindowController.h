#include "IEventListener.h"
#include "DataModel.h"
#include <boost/shared_ptr.hpp>
#include "Evt_CloseWindow.h"

class WindowController : public IEventListener
{
    public:
        WindowController(DataModelPtr pModel);
        bool handleEvent(Event const & event);
    private:
        DataModelPtr model;
};

typedef boost::shared_ptr<WindowController> WindowControllerPtr;
