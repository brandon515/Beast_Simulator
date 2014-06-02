#include "IEventListener.h"
#include "MovementView.h"
#include <boost/shared_ptr.hpp>

class MovementController : public IEventListener
{
    public:
        MovementController(MovementViewPtr pview);
        bool handleEvent(Event const & event);
    private:
        MovementViewPtr view;
};

typedef boost::shared_ptr<MovementController> MovementControllerPtr;
