#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED
#include "IScreenElement.h"
#include "Logging.h"
#include <boost\lexical_cast.hpp>
#include <cmath>

typedef std::pair<uint32_t, uint32_t> fxRet;
const double PI = atan(1)*4;

class Planet : public IScreenElement
{
    public:
        Planet(Sint16 x, Sint16 y, uint32_t radius, uint32_t color);
    private:
        uint32_t m_radius;
};

#endif // CIRCLE_H_INCLUDED
