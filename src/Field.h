#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED
#include "IScreenElement.h"
#include "Methods.h"
#include "Logging.h"
#include <boost\lexical_cast.hpp>

class Field : public IScreenElement
{
    public:
        Field(uint32_t width, uint32_t height, int prime1, int prime2, int prime3);
        bool setup();
    private:
        uint32_t m_height, m_width;
        int m_prime1, m_prime2, m_prime3;
};

#endif // FIELD_H_INCLUDED
