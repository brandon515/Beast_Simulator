#include "MovementView.h"

MovementView::MovementView()
{}

bool MovementView::add(DataPacketPtr data)
{
   return true;
}

void MovementView::addMoveEvent(Evt_Move const & event)
{
    moves.push_back(event);
}

/**********************************
*go through the move queue, see if*
*any movements are for the same   *
*entity then add them together    *
***********************************/
void MovementView::preFrame()
{
    for(MoveList::iterator it = moves.begin(); it != moves.end(); it++)
    {
        Evt_Move move;
        Evt_MoveData *dat = (*it).getDataPtr<Evt_MoveData>();
        uint32_t id = dat->ID;
        MoveList::iterator it2 = it;
        it2++;
        while(it2 != moves.end())
        {
            Evt_MoveData *datComp = (*it2).getDataPtr<Evt_MoveData>();
            
        }
    }
}

/************************************
*check if Data needs to be moved    *
*if so then move it, pretty easy    *
*************************************/
void MovementView::onFrame(DataPacketPtr data)
{
    
}

/************************************
*Check the move queue, if there are *
*any events in the queue then print *
*an error message                   *
*************************************/
void MovementView::postFrame()
{
    
}

void MovementView::remove(std::string name)
{
    
}

bool MovementView::init()
{
    
}
