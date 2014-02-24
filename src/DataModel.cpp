#include "DataModel.h"

DataModel::DataModel(std::string name):
    Process(name)
{
    data = DataMapPtr(new DataMap());
}

DataModel::~DataModel()
{
}

DataModel::DataConstPtr DataModel::getDataList()
{
    return data;
}

bool DataModel::loadFile(std::string filename)
{
    if(!data->empty())
    {
        data->clear();
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
        Json::Value dat = obj.get("data", false);
        DataPacketPtr ent(new DataPacket(obj));
        DataEnt mapEnt(CRC32(ent->getName().c_str(), ent->getName().length()), ent);
        DataRes res = data->insert(mapEnt);
        if(res.first == data->end() || res.second == false)
        {
            Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("Json object not valid\n\tname: " + name)));
        }
    }
    return true;
}

bool DataModel::addObject(std::string name, std::string filename, std::string values)
{
    DataPacketPtr ent(new DataPacket(name, filename, values));
    DataEnt mapEnt(CRC32(ent->getName().c_str(), ent->getName().length()), ent);
    DataRes res = data->insert(mapEnt);
    if(res.first == data->end() || res.second == false)
    {
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("Json object not valid\n\tname: " + name)));
        return false;
    }
    for(ViewList::iterator it = views.begin(); it != views.end(); it++)
    {
        if(!(*it)->add(ent))
            Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("Obj with name " + ent->getName() + " couldn't be added")));
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
        return Json::Value();
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
        return Json::Value();
    }
    return root;
}

bool DataModel::addView(ViewPtr obj)
{
    if(obj.get() == NULL)
        return false;
    obj->init();
    for(DataMap::iterator it = data->begin(); it != data->end(); it++)
    {
        if(!obj->add((*it).second))
        {
            Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("Obj with name " + (*it).second->getName() + " couldn't be added")));
        }
    }
    views.push_back(obj);
    return true;
}

void DataModel::removeView(uint32_t id)
{
    for(ViewList::iterator it = views.begin(); it != views.end(); it++)
    {
        if((*it)->getID() == id)
        {
            views.erase(it);
            break;
        }
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
        for(DataMap::iterator it2 = data->begin(); it2 != data->end(); it2++)
        {
            DataPacketPtr dat = it2->second;
            (*it)->onFrame(dat);
        }
    }
    for(it = views.begin(); it != views.end(); it++)
    {
        (*it)->postFrame();
    }
}
