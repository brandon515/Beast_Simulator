#include "DataModel.h"

bool DataModel::loadFile(std::string filename)
{
    Json::Value root = getRoot(filename);
    if(root == Json::Value(false))
        return false;
    Json::Value array = root["mapObjects"];
    for(int i = 0; true; i++)
    {
        if(!array.isValidIndex(i))
            break;
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
        DataEnt mapEnt(CRC32(ent.name), ent);
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
