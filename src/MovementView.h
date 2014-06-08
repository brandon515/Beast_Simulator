#ifndef MOVEMENTVIEW_H_INCLUDED
#define MOVEMENTVIEW_H_INCLUDED
#include "View.h"
#include "Evt_Move.h"
#include <vector>
#include <boost/shared_ptr.hpp>
#include <time.h>
#include <map>

class MoveData
{
    public:
        MoveData();
        clock_t lastMove;
        bool movedLastFrame;
};

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

        typedef std::map<uint32_t, MoveData*> MoveMap;
        typedef std::pair<uint32_t, MoveData*> MoveEnt;
        typedef std::pair<MoveMap::iterator, bool> MoveRes;
        
        MoveList reqMoves, movesToBeExecuted;
        MoveMap moveTiming;
};

typedef boost::shared_ptr<MovementView> MovementViewPtr;
#endif
