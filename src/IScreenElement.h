#ifndef ISCREENELEMENT_H_INCLUDED
#define ISCREENELEMENT_H_INCLUDED
#include <string>
#include <SDL\SDL.h>
#include "Methods.h"

class IScreenElement
{
    public:
        explicit IScreenElement(Sint16 x, Sint16 y, std::string pictureName = "did not init");
        virtual ~IScreenElement();
        virtual void render(SDL_Surface *renderTo);
        virtual void update();
        virtual const SDL_Rect getPos() const;
        virtual void setAcc(Sint16 x, Sint16 y);
        virtual void move(Sint16 x, Sint16 y);
    protected:
        virtual bool loadSprite(std::string filename);
        SDL_Rect screenPos, sheetPos, velocity, acc;
        SDL_Surface *sprite;
        uint32_t ID;
};

#endif // ISCREENELEMENT_H_INCLUDED
