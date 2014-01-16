#include "Event_System.h"

Event_System & Event_System::getSingleton()
{
    static Event_System ret;
    return ret;
}

Event_System::~Event_System()
{
    m_registry.clear();
    m_typeList.clear();
    m_activeQueue = 0;
}

bool Event_System::validateType(EventType const & type) const
{
    if(type.getStr() == NULL)
        return false;
    if((type.getIdent() == 0) && (strcasecmp(type.getStr(), wildCardType) != 0))
        return false;
    EventTypeSet::const_iterator searchRes = m_typeList.find(type);

    if(searchRes != m_typeList.end())
    {
        EventType const & known = (*searchRes);

        const char * const knownStr = known.getStr();
        const char * const typeStr = type.getStr();

        int res = strcasecmp(knownStr, typeStr);

        assert(res == 0 && "two event types have collided");
        if(res != 0)
            return false;
    }
    return true;
}

bool Event_System::addListener(EventListenerPtr const & listener, EventType const & type)
{
    if(!validateType(type))
        return false;

    EventTypeSet::iterator evtRes = m_typeList.find(type);
    if(evtRes == m_typeList.end())
    {
        EventTypeRes insertRes = m_typeList.insert(type);

        if(insertRes.first == m_typeList.end())
            return false;

        if(insertRes.second == false)
            return false;

        evtRes = insertRes.first;
    }
    EventListenerMap::iterator elmIt = m_registry.find(type.getIdent());
    if(elmIt == m_registry.end())
    {
        EventListenerMapRes elmRes = m_registry.insert(EventListerMapEnt(type.getIdent(), EventListenerTable()));

        if(elmRes.first == m_registry.end())
            return false;

        if(elmRes.second == false)
            return false;

        elmIt = elmRes.first;
    }
    EventListenerTable &eltTable = (*elmIt).second;
    for(EventListenerTable::iterator it = eltTable.begin(); it != eltTable.end(); it++)
    {
        if(*it == listener)
            return false;
    }
    eltTable.push_back(listener);
    return true;
}

bool Event_System::delListener(EventListenerPtr const & listener, EventType const & type)
{
    if(!validateType(type))
        return false;

    bool erased = false;
    //wildcard EventType removes the listener from all lists
    if(type.getIdent() == 0)
    {
        for(EventListenerMap::iterator it = m_registry.begin(); it != m_registry.end(); it++)
        {
            EventListenerTable cur = (*it).second;
            for(EventListenerTable::iterator it2 = cur.begin(); it2 != cur.end(); it2++)
            {
                EventListenerPtr elp = (*it2);
                if(listener.get() == elp.get())
                {
                    cur.erase(it2);
                    erased = true;
                    break;
                }
            }
        }
    }
    //the listener doesnt want to recieve a certain event
    else
    {
        EventListenerMap::iterator mapIt = m_registry.find(type.getIdent());
        if(mapIt == m_registry.end())
            return false;
        EventListenerTable cur = (*mapIt).second;
        for(EventListenerTable::iterator it = cur.begin(); it != cur.end(); it++)
        {
            EventListenerPtr elp = (*it);
            if(elp.get() == listener.get())
            {
                cur.erase(it);
                erased = true;
                break;
            }
        }
    }
    return erased;
}

bool Event_System::trigger(Event const & event) const
{
    if(!validateType(event.getType()))
        return false;

    EventListenerMap::const_iterator wildCardListIt = m_registry.find(0);
    if(wildCardListIt != m_registry.end())
    {
        EventListenerTable wildCardList = (*wildCardListIt).second;
        for(EventListenerTable::const_iterator it = wildCardList.begin(); it != wildCardList.end(); it++)
        {
            (*it).get()->handleEvent(event);
        }
    }

    EventListenerMap::const_iterator eventTypeIt = m_registry.find(event.getType().getIdent());
    if(eventTypeIt == m_registry.end())
        return false;

    bool consumed;
    EventListenerTable eventTypeTable = (*eventTypeIt).second;
    for(EventListenerTable::iterator it = eventTypeTable.begin(); it != eventTypeTable.end(); it++)
    {
        if((*it).get()->handleEvent(event))
        {
            consumed = true;
            break;
        }
    }
    return consumed;
}

bool Event_System::queueEvent(EventPtr const & event)
{
    assert(m_activeQueue >= 0);
    assert(m_activeQueue < numQueues);

    if(!validateType(event.get()->getType()))
        return false;

    EventListenerMap::iterator elmIt = m_registry.find(event.get()->getType().getIdent());
    if(elmIt == m_registry.end())
        return false;

    m_queue[m_activeQueue].push_back(event);
    return true;
}

bool Event_System::abortEvent(EventType const & type, bool allOfType)
{
    assert(m_activeQueue >= 0);
    assert(m_activeQueue < numQueues);

    if(!validateType(type))
        return false;

    bool erased = false;
    for(EventQueue::iterator it = m_queue[m_activeQueue].begin(); it != m_queue[m_activeQueue].end(); it++)
    {
        EventPtr cur = (*it);
        if(cur.get()->getType() == type)
        {
            m_queue[m_activeQueue].erase(it);
            erased = true;
            if(!allOfType)
                break;
        }
    }
    return erased;
}

bool Event_System::tick(uint32_t maxMillis)
{
    time_b curSec = boost::chrono::steady_clock::now();
    Milliseconds maxDuration(maxMillis);
    time_b stopTime = curSec + maxDuration;

    EventListenerMap::const_iterator wcIt = m_registry.find(0);

    uint32_t queueProcessing = m_activeQueue;
    m_activeQueue = (m_activeQueue+1) % numQueues;

    m_queue[m_activeQueue].clear();

    while(!m_queue[queueProcessing].empty())
    {
        EventPtr curEvent = m_queue[queueProcessing].front();
        m_queue[queueProcessing].pop_front();

        EventType const & type = curEvent.get()->getType();

        EventListenerMap::const_iterator typeIt = m_registry.find(type.getIdent());

        if(wcIt != m_registry.end())
        {
            EventListenerTable wcTable = (*wcIt).second;
            for(EventListenerTable::const_iterator it = wcTable.begin(); it != wcTable.end(); it++)
            {
                (*it).get()->handleEvent(*curEvent.get());
            }
        }
        if(typeIt != m_registry.end())
        {
            EventListenerTable typeTable = (*typeIt).second;
            for(EventListenerTable::const_iterator it = typeTable.begin(); it != typeTable.end(); it++)
            {
                if((*it).get()->handleEvent(*(curEvent.get())))
                    break;
            }
        }

        if(maxMillis != infMill)
        {
            curSec = boost::chrono::steady_clock::now();
            if(curSec >= stopTime)
                break;
        }
    }
    bool queueFlushed = m_queue[queueProcessing].empty();
    if(!queueFlushed)
    {
        while(!m_queue[queueProcessing].empty())
        {
            EventPtr temp = m_queue[queueProcessing].back();
            m_queue[queueProcessing].pop_back();
            m_queue[m_activeQueue].push_front(temp);
        }
    }

    return queueFlushed;
}

EventTypeList Event_System::getTypeList() const
{
    if(m_typeList.empty())
        return EventTypeList();

    EventTypeList res;
    res.reserve(m_typeList.size());

    for(EventTypeSet::iterator it = m_typeList.begin(); it != m_typeList.end(); it++)
    {
        res.push_back(*it);
    }

    return res;
}

EventListenerList Event_System::getListenerList(EventType const & type) const
{
    if(!validateType(type))
        return EventListenerList();

    EventListenerMap::const_iterator evmIt = m_registry.find(type.getIdent());

    if(evmIt == m_registry.end())
        return EventListenerList();

    EventListenerTable elt = (*evmIt).second;

    EventListenerList res;
    res.reserve(elt.size());

    for(EventListenerTable::iterator it = elt.begin(); it != elt.end(); it++)
    {
        res.push_back(*it);
    }
    return res;
}
