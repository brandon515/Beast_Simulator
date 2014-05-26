#include "IEventListener.h"
#include "MovementView.h"

class MovementController : public IEventListener
{
    public:
        bool handleEvent(Event const & event);
    private:
        MovementViewPtr view;
};
