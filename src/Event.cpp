#include "Event.h"

//---------------------------------------------
//              class EventType
//---------------------------------------------

EventType::EventType(const char * identStr):
    m_identStr(identStr),
    m_ident(getHash(identStr))
    {}

uint64_t EventType::getIdent() const
{
    return reinterpret_cast<uint64_t>(m_ident);
}

const char * EventType::getStr() const
{
    return m_identStr;
}

bool EventType::operator<(EventType const & o) const
{
    return (getIdent() < o.getIdent());
}

bool EventType::operator==(EventType const & o) const
{
    return (getIdent() == o.getIdent());
}

void * EventType::getHash(const char * identStr)
{
    void * r = NULL;

    if(identStr == NULL)
        return NULL;
    if(strcasecmp(identStr, wildCardType) == 0)
        return 0;
    uint32_t rA = CRC32(identStr, strlen(identStr));
    r = reinterpret_cast<void*>(rA);
    return r;
}
