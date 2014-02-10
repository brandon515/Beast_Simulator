#include "DataModel.h"

DataModel::DataModel(std::string name):
    Process(name)
{
}

DataModel::~DataModel()
{
}

bool DataModel::loadFile(std::string filename)
{
    if(!data.empty())
    {
        data.clear();
    }
    Json::Value root = getRoot(filename);
    if(root == Json::Value(false))
    {
        return false;
    }
    Json::Value array = root["mapObjects"];
    for(uint32_t i = 0; i < array.size(); i++)
    {
        Json::Value obj = array[i];
        std::string name, objName;
        name = obj["name"].asString();
        objName = obj["objFile"].asString();
        int x = obj["x"].asInt();
        int y = obj["y"].asInt();
        DataPacket ent;
        ent.name = name;
        ent.filename = objName;
        ent.x = x;
        ent.y = y;
        DataEnt mapEnt(CRC32(ent.name.c_str(), ent.name.length()), ent);
        DataRes res = data.insert(mapEnt);
        if(res.first == data.end() || res.second == false)
        {
            Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("Json object not valid\n\tname: " + name)));
        }   
    }
    return true;
}

Json::Value DataModel::getRoot(std::string filename)
{
    Json::Value root;
    Json::Reader reader;
    ifstream file;
    file.open(filename.c_str());
    if(!file.is_open())
    {
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("file " + filename + " cannot be opened for Json parsing")));
        return Json::Value(false);
    }
    file.seekg(0, file.end);
    int len = file.tellg();
    file.seekg(0, file.beg);
    char *dat = new char[len];
    file.read(dat, len);
    std::string fileStr(dat);
    file.close();
    if(!reader.parse(fileStr, root))
    {
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("JSON parser cannot parse the file: " + filename + "\n\treason:" + reader.getFormatedErrorMessages())));
        return Json::Value(false);
    }
    return root;
}

bool DataModel::addView(ViewPtr obj)
{
    if(obj.get() == NULL)
        return false;
    obj->init();
    views.push_back(obj);
    return true;
}

void DataModel::removeView(uint32_t id)
{
    for(ViewList::iterator it = views.begin(); it != views.end(); it++)
    {
        if((*it)->getID() == id)
            views.erase(it);
    }
}

void DataModel::tick()
{
    if(views.empty())
    {
        Event_System::getSingleton().trigger(Evt_CloseApplication());
    }
    ViewList::iterator it;
    for(it = views.begin(); it != views.end(); it++)
    {
        (*it)->preFrame();
    }
    for(it = views.begin(); it != views.end(); it++)
    {
        for(DataMap::iterator it2 = data.begin(); it2 != data.end(); it2++)
        {
            DataPacket dat = it2->second;
            (*it)->onFrame(dat.name, dat.x, dat.y);
        }
    }
    for(it = views.begin(); it != views.end(); it++)
    {
        (*it)->postFrame();
    }
    if(views.empty())
    {
        EventPtr evt(new Evt_CloseApplication()); 
        Event_System::getSingleton().queueEvent(evt);
    }
}
