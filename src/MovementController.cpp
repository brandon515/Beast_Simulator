#include "MovementController.h"

bool MovementController::handleEvent(Event const & event)
{
    if(event.getType() == Evt_Move().getType())
    {
        view->addMoveEvent(*((Evt_Move*)&event));
        return true;
    }
    return false;
}

MovementController::MovementController(MovementViewPtr pview):
    view(pview)
{}
