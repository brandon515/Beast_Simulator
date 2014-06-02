#ifndef MOVEMENTVIEW_H_INCLUDED
#define MOVEMENTVIEW_H_INCLUDED
#include "View.h"
#include "Evt_Move.h"
#include <vector>
#include <boost/shared_ptr.hpp>

class MovementView : public View
{
    public:
        MovementView();
        bool add(DataPacketPtr data);
        void preFrame();
        void onFrame(DataPacketPtr data);
        void postFrame();
        void remove(std::string name);
        bool init();
        void addMoveEvent(Evt_Move const & event);

    private:
        typedef std::vector<Evt_Move> MoveList;
        
        MoveList reqMoves, movesToBeExecuted;

};

typedef boost::shared_ptr<MovementView> MovementViewPtr;
#endif
