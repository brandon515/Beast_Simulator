#ifndef ISCREENELEMENT_H_INCLUDED
#define ISCREENELEMENT_H_INCLUDED
#include <string>
#include <SDL\SDL.h>
#include "Methods.h"

class IScreenElement
{
    public:
        explicit IScreenElement(Sint16 x, Sint16 y, std::string pictureName);
        virtual void render(SDL_Surface *renderTo);
        virtual void update();
        virtual void move(Sint16 x, Sint16 y);
    protected:
        virtual bool loadSprite(std::string filename);
        SDL_Rect screenPos, sheetPos;
        SDL_Surface *sprite;
        uint32_t ID;
};

#endif // ISCREENELEMENT_H_INCLUDED
