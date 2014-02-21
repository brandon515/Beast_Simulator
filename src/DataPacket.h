#ifndef DATAPACKET_H_INCLUDED
#define DATAPACKET_H_INCLUDED 
#include <json/json.h>
#include <boost/variant.hpp>
#include "Event_System.h"
#include "MsgEvt.h"
#include <climits>

typedef boost::variant<int, bool, std::string, double> Data;

class assignJsonValue : public boost::static_visitor<>
{
    public:
        template <typename T>
        void operator()(Json::Value obj, std::string name, T & operand) const
        {
            obj[name] = operand;
        }
};

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
        bool set(std::string name, const T &);
        std::string getName();
    private:
        Json::Value getRoot(std::string filename);
        std::string name;
        Json::Value mutData, constData;
};
#endif
