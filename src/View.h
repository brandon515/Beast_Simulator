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
        // DataPacket passed to class, should not alter DataPacket
        virtual bool add(DataPacketPtr data)=0;
        // Set up
        virtual void preFrame()=0;
        // manipulation of the datapacket allowed
        virtual void onFrame(DataPacketPtr data)=0;
        // clean up for the frame
        virtual void postFrame()=0;
        // notification of deletion for a DataPacket
        virtual void remove(std::string name)=0;
        // set up
        virtual bool init()=0;
        uint32_t getID(){return id;}
    protected:
        void setID(uint32_t pid){id = pid;}
    private:
        uint32_t id;
};

typedef boost::shared_ptr<View> ViewPtr;
#endif
