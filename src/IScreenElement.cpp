#include "IScreenElement.h"

IScreenElement::IScreenElement(Sint16 x, Sint16 y, std::string pictureName):
    screenPos{x,y,0,0}
{
    loadSprite(pictureName);
}

bool IScreenElement::loadSprite(std::string filename)
{
    sprite = loadImage(filename);
    if(sprite == NULL)
        return false;
    return true;
}

void IScreenElement::update()
{
    //
}

void IScreenElement::render(SDL_Surface *renderTo)
{
    if(sheetPos.w == 0)
    {
        if(screenPos.x == 0 and screenPos.y == 0)
            SDL_BlitSurface(sprite, NULL, renderTo, NULL);
        else
            SDL_BlitSurface(sprite, NULL, renderTo, &screenPos);
    }
    else
    {
        if(screenPos.x == 0 and screenPos.y == 0)
            SDL_BlitSurface(sprite, &sheetPos, renderTo, NULL);
        else
            SDL_BlitSurface(sprite, &sheetPos, renderTo, &screenPos);
    }
}

void IScreenElement::move(Sint16 x, Sint16 y)
{
    screenPos.x+=x;
    screenPos.y+=y;
}
