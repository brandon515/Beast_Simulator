#ifndef IMOVABLEELEMENT_H_INCLUDED
#define IMOVABLEELEMENT_H_INCLUDED
#include "IScreenElement.h"

class IMovableElement: protected IScreenElement
{
    public:
        explicit IMovableElement(uint16_t x, uint16_t y, std::string pictureName);
        virtual void moveX(uint32_t blocks);
        virtual void moveY(uint32_t blocks);
};

#endif // IMOVABLEELEMENT_H_INCLUDED
