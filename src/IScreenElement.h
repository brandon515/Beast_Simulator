#ifndef ISCREENELEMENT_H_INCLUDED
#define ISCREENELEMENT_H_INCLUDED
#include <string>
#include <SDL\SDL.h>
#include "Methods.h"

class IScreenElement
{
    public:
        virtual void render(SDL_Surface *renderTo);
        virtual void update();
    protected:
        virtual bool loadSprite(std::string filename);
        SDL_Rect screenPos, sheetPos;
        SDL_Surface *sprite;
};

#endif // ISCREENELEMENT_H_INCLUDED
