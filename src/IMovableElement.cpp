#include "IMovableElement.h"

IMovableElement::IMovableElement(uint16_t x, uint16_t y, std::string pictureName):
    IScreenElement(x,y,pictureName)
{
    //
}

void IMovableElement::moveX(uint32_t blocks)
{
    screenPos.x += (sprite->w*blocks);
}

void IMovableElement::moveY(uint32_t blocks)
{
    screenPos.y += (sprite->h*blocks);
}
