#ifndef VIEW_H_INCLUDED
#define VIEW_H_INCLUDED
#include <string>
#include <stdint.h>
#include <boost/shared_ptr.hpp>
#include "DataPacket.h"

class View
{
    public:
        View(uint32_t pid){id = pid;}
        virtual ~View(){}
        virtual bool add(DataPacketPtr data)=0;
        virtual void preFrame()=0;
        virtual void onFrame(DataPacketPtr data)=0;
        virtual void postFrame()=0;
        virtual void remove(std::string name)=0;
        virtual bool init()=0;
        uint32_t getID(){return id;}
    protected:
        void setID(uint32_t pid){id = pid;}
    private:
        uint32_t id;
};

typedef boost::shared_ptr<View> ViewPtr;
#endif
