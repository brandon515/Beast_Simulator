#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED
#include "Methods.h"
#include <iostream>
#include <string.h>
#include <boost/shared_ptr.hpp>
#include <boost/chrono.hpp>

class IEventData
{
    public:
        virtual ~IEventData(){}
};


typedef boost::shared_ptr<IEventData> IEventDataPtr;
typedef boost::chrono::duration<uint32_t, boost::milli> Milliseconds;
typedef boost::chrono::steady_clock::time_point time_b;

const char * const wildCardType = "*";

class EventType
{
    public:
        explicit EventType(const char * identStr);
        uint64_t getIdent() const;
        const char * getStr() const;
        bool operator< (EventType const & o) const;
        bool operator== (EventType const & o) const;
        static void * getHash(const char * identStr);
    private:
        const char * m_identStr;
        void * m_ident;
};

class Event
{
    public:
        explicit Event(const char * type, IEventDataPtr data = IEventDataPtr((IEventData*)NULL), time_b time = boost::chrono::steady_clock::now()):
            m_type(type),
            m_time(time),
            m_userData(data)
        {}
        explicit Event(Event const & o):
            m_type(o.m_type),
            m_time(o.m_time),
            m_userData(o.m_userData)
        {}
        virtual ~Event(){}

        EventType const & getType() const   {return m_type;}
        time_b getTime() const              {return m_time;}
        IEventDataPtr getData() const       {return m_userData;}

        template<typename _T>
        _T * getDataPtr() const { return reinterpret_cast<_T *>(m_userData.get());}

    private:
        EventType m_type;
        time_b m_time;
        IEventDataPtr m_userData;
};

#endif // EVENT_H_INCLUDED
