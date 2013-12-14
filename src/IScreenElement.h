#ifndef ISCREENELEMENT_H_INCLUDED
#define ISCREENELEMENT_H_INCLUDED
#include <string>
#include <SDL\SDL.h>
#include <boost\shared_ptr.hpp>
#include "Methods.h"
#include "IGameObject.h"

class IScreenElement : public virtual IGameObject
{
    public:
        IScreenElement(){visible = true; reg("IScreenElement");}
        virtual ~IScreenElement(){}
        virtual void render(SDL_Surface *renderTo)=0;
        bool isVisible(){return visible;}
        void setVisibility(bool vis){visible = vis;}
        SDL_Surface *sprite;
    private:
        bool visible;
};

typedef boost::shared_ptr<IScreenElement> IScreenElementPtr;

#endif // ISCREENELEMENT_H_INCLUDED
