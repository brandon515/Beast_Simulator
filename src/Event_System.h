#ifndef EVENT_SYSTEM_H_INCLUDED
#define EVENT_SYSTEM_H_INCLUDED
#include <boost\shared_ptr.hpp>
#include <boost\chrono.hpp>
#include "IEventListener.h"
#include "Event.h"
#include <cassert>
#include <set>
#include <vector>
#include <map>
#include <list>

typedef boost::shared_ptr<IEventListener> EventListenerPtr;
typedef boost::shared_ptr<Event> EventPtr;
typedef std::vector<EventListenerPtr> EventListenerList;
typedef std::vector<EventType> EventTypeList;

const uint32_t numQueues = 2;
const uint32_t infMill = 0xffffffff;

/***********************************
* this is not designed to be on    *
* each idividual class but to used *
* on entire systems remember block *
* head!                            *
************************************/
class Event_System
{
    public:
        static Event_System & getSingleton();
        ~Event_System();
        bool addListener(EventListenerPtr const & listener, EventType const & type);
        bool delListener(EventListenerPtr const & listener, EventType const & type);
        bool trigger(Event const & event) const;
        bool queueEvent(EventPtr const & event);
        bool abortEvent(EventType const & type, bool allOfType);
        bool tick(uint32_t maxMillis);
        bool validateType(EventType const & type) const;
        EventTypeList getTypeList() const;
        EventListenerList getListenerList(EventType const & type) const;
    private:

        //singleton undefined methods

        Event_System() {m_activeQueue = 0;}
        Event_System(Event_System const &);
        bool operator=(Event_System const &);

        //typedefs used in the system

        typedef std::set<EventType> EventTypeSet;
        typedef std::pair<EventTypeSet::iterator, bool> EventTypeRes;
        typedef std::list<EventListenerPtr> EventListenerTable;
        typedef std::map<uint64_t, EventListenerTable> EventListenerMap;
        typedef std::pair<uint64_t, EventListenerTable> EventListerMapEnt;
        typedef std::pair<EventListenerMap::iterator, bool> EventListenerMapRes;
        typedef std::list<EventPtr> EventQueue;

        //member variables

        EventTypeSet m_typeList;
        EventListenerMap m_registry;
        EventQueue m_queue[numQueues];
        uint32_t m_activeQueue;

};

#endif // EVENT_SYSTEM_H_INCLUDED
