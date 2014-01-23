#include <string>
#include "Process.h"
#include "Methods.h"
#include "MsgEvt.h"
#include "View.h"
#include "Event_System.h"
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
        bool add(View *obj);
    private:
        typedef std::map<uint32_t, DataPacket> DataMap;
        typedef std::pair<uint32_t, DataPacket> DataEnt;
        typedef std::pair<DataMap::iterator, bool> DataRes;

        typedef std::vector<View*> ViewList;

        DataMap data;
        ViewList views;

        Json::Value getRoot(std::string filename);
};
