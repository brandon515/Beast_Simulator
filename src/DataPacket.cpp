#include "DataPacket.h"

DataPacket::DataPacket(std::string pName, std::string pFilename, std::string dat)
{
    name = pName;
    Json::Reader reader;
    Json::Value valuesObj, valuesArr, variablesArr;
    constData = getRoot(pFilename);
    if(!reader.parse(dat, valuesObj))
    {
        mutData = Json::Value(false);
    }
    else
    {
        valuesArr = valuesObj["data"];
        variablesArr = constData["data"];
        for(unsigned int i = 0; i < variablesArr.size(); i++)
        {
            mutData[variablesArr[i].asString()] = valuesArr[i];
        } 
    }   
}

DataPacket::DataPacket(Json::Value obj)
{
    name = obj.get("name", "NoAdd").asString();
    if(strcmp(name.c_str(), "NoAdd") == 0)
    {
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("Json object has no name field")));
    }
    std::string filename = obj.get("objFile", "NoAdd").asString();
    if(strcmp(filename.c_str(), "NoAdd") == 0)
    {
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("Json object has no filename field")));
    }
    constData = getRoot(filename);
    Json::Value valuesArr = obj.get("data", "noArray");
    if(valuesArr == Json::Value("noArray"))
    {
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("Json object with the name: " + name + "has no mutData values")));
    }
    Json::Value variablesArr = constData.get("data", "noArray");
    if(variablesArr == Json::Value("noArray"))
    {
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("Json object with the name: " + name + "has no mutData variables")));
    }
    for(unsigned int i = 0; i < variablesArr.size(); i++)
    {
        mutData[variablesArr[i].asString()] = valuesArr[i];
    }
}

std::string DataPacket::getName()
{
    return name;
}

int DataPacket::getInt(std::string name)
{
    int ret = mutData.get(name, INT_MAX).asInt();
    if(ret == INT_MAX)
    {
        ret = constData.get(name, INT_MAX).asInt();
    }
    return ret;
}

int DataPacket::getBool(std::string name)
{
    int ret = mutData.get(name, -1).asBool();
    if(ret == -1)
    {
        ret = constData.get(name, -1).asBool();
    }
    return ret;
}

std::string DataPacket::getString(std::string name)
{
    std::string ret = mutData.get(name, "noObject").asString();
    if(strcmp(ret.c_str(), "noObject") == 0)
    {
        ret = constData.get(name, "noObject").asString();
    }
    return ret;
}

double DataPacket::getDouble(std::string name)
{
    double ret = mutData.get(name, INFINITY).asDouble();
    if(ret == INFINITY)
    {
        ret = constData.get(name, INFINITY).asDouble();
    }
    return ret;
}

template<typename T>
bool DataPacket::set(std::string name, const T& dat)
{
    Json::Value check = mutData.get(name, "noObject");
    if(check == Json::Value("noObject"))
        return false;
    mutData[name] = dat;
    return true;
}
    
Json::Value DataPacket::getRoot(std::string filename)
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
