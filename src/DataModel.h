#ifndef DATAMODEL_H_INCLUDED
#define DATAMODEL_H_INCLUDED
#include <string>
#include <iostream>
#include "Process.h"
#include "Methods.h"
#include "MsgEvt.h"
#include "View.h"
#include "Event_System.h"
#include "Evt_CloseApplication.h"
#include <boost/shared_ptr.hpp>
#include <map>
#include <json/json.h>

typedef struct dataPacket
{
    std::string name, filename;
    int x, y;
} DataPacket;

class DataModel : public Process
{
    public:
        DataModel(std::string name);
        ~DataModel();
        bool loadFile(std::string filename);
        void tick();
        bool init(){return true;}
        bool addView(ViewPtr obj);
        void removeView(uint32_t id);
    private:
        typedef std::map<uint32_t, DataPacket> DataMap;
        typedef std::pair<uint32_t, DataPacket> DataEnt;
        typedef std::pair<DataMap::iterator, bool> DataRes;

        typedef std::vector<ViewPtr> ViewList;

        DataMap data;
        ViewList views;

        Json::Value getRoot(std::string filename);
};

typedef boost::shared_ptr<DataModel> DataModelPtr;
#endif
