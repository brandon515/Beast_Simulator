#ifndef ISCREENELEMENT_H_INCLUDED
#define ISCREENELEMENT_H_INCLUDED
#include <string>
#include <SDL\SDL.h>
#include "Methods.h"
#include "IGameObject.h"

class IScreenElement : public IGameObject
{
    public:
        explicit IScreenElement(Sint16 x, Sint16 y, std::string pictureName = "n");
        virtual ~IScreenElement();
        virtual void render(SDL_Surface *renderTo);
        virtual bool setup();
        virtual const SDL_Rect getPos() const;
        virtual void setVec(Sint16 x, Sint16 y);
        virtual void move(Sint16 x, Sint16 y);
    protected:
        virtual bool loadSprite(std::string filename);
        SDL_Rect screenPos, sheetPos, velocity;
        SDL_Surface *sprite;
};

#endif // ISCREENELEMENT_H_INCLUDED
