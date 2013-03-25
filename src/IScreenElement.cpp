#include "IScreenElement.h"

IScreenElement::~IScreenElement()
{
    SDL_FreeSurface(sprite);
}

IScreenElement::IScreenElement(Sint16 x, Sint16 y, std::string pictureName)
{
    screenPos.x = x;
    screenPos.y = y;
    //let the derived class initalize the sprite in it's own way if they so choose
    if(pictureName.compare("did not init") != 0)
        loadSprite(pictureName);
}

void IScreenElement::update()
{
    //
}

bool IScreenElement::loadSprite(std::string filename)
{
    sprite = loadImage(filename);
    if(sprite == NULL)
        return false;
    return true;
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

void IScreenElement::setAcc(Sint16 x, Sint16 y)
{
    velocity.x=x;
    velocity.y=y;
}

void IScreenElement::move(Sint16 x, Sint16 y)
{
    screenPos.x+=x;
    screenPos.y+=y;
}

const SDL_Rect IScreenElement::getPos() const
{
    return screenPos;
}
