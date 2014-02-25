#ifndef DATAPACKET_H_INCLUDED
#define DATAPACKET_H_INCLUDED 
#include <json/json.h>
#include "Event_System.h"
#include "MsgEvt.h"
#include <climits>

class DataPacket;
typedef boost::shared_ptr<DataPacket> DataPacketPtr;
class DataPacket
{
    public:
        DataPacket(std::string pName, std::string pFilename, std::string data);
        DataPacket(Json::Value obj);
        int getInt(std::string name);
        int getBool(std::string name);
        std::string getString(std::string name);
        double getDouble(std::string name);
        template <typename T>
        bool set(std::string name, const T & dat)
        {
            if(!mutData.isMember(name))
                return false;
            Json::Value val(dat);
            if(val.isNull())
                return false;
            mutData[name] = val;
            return true;
        }   
        std::string getName();
        std::string getDataStr();
        std::vector<std::string> getStringList(std::string name);
        DataPacketPtr getBlock(std::string name);
    private:
        Json::Value getRoot(std::string filename);
        std::string name, objFile;
        Json::Value mutData, constData;
};
#endif
