#ifndef IGAMEVIEW_H_INCLUDED
#define IGAMEVIEW_H_INCLUDED
#include <boost\shared_ptr.hpp>
#include <boost\any.hpp>
#include "IGameObject.h"
#include "Logging.h"
#include "Interfaces.h"
#include "IMovableElement.h"
#include <vector>

class IGameView
{
    public:
        IGameView(){needsDelete = false;}
        virtual ~IGameView(){}
        virtual bool init()=0;
        virtual void tick()=0;
        bool needsDelete;
};

typedef boost::shared_ptr<IGameView> IGameViewPtr;

#endif // IGAMEVIEW_H_INCLUDED
