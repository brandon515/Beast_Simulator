#ifndef IMOVABLEELEMENT_H_INCLUDED
#define IMOVABLEELEMENT_H_INCLUDED
#include <SDL\SDl.h>
#include <boost\shared_ptr.hpp>
#include <map>
#include "IGameObject.h"

typedef std::pair<Sint16, Sint16> coPair;

class IMovableElement : public virtual IGameObject
{
    public:
        IMovableElement(){reg("IMovableElement");}
        void move(Sint16 x, Sint16 y){pos.x+=x; pos.y+=y;}
        void setPos(Sint16 x, Sint16 y){pos.x=x; pos.y=y;}
        void setPos(SDL_Rect newPos){pos=newPos;}
        SDL_Rect *getPos(){return &pos;}
    private:
        SDL_Rect pos;
};

typedef boost::shared_ptr<IMovableElement> IMovableElementPtr;

#endif // IMOVABLEELEMENT_H_INCLUDED
