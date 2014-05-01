#include "DataPacket.h"

DataPacket::DataPacket(std::string pName, std::string pFilename, std::string dat)
{
    name = pName;
    objFile = pFilename;
    Json::Reader reader;
    Json::Value valuesObj, valuesArr, variablesArr;
    constData = getRoot(pFilename);
    if(!reader.parse(dat, valuesObj))
    {
        mutData = Json::Value();
    }
    else
    {
        if(valuesObj.isMember("data") && constData.isMember("data"))
        {
            valuesArr = valuesObj["data"];
            variablesArr = constData["data"];
            for(unsigned int i = 0; i < variablesArr.size(); i++)
            {
                mutData[variablesArr[i].asString()] = valuesArr[i];
            }
        }
        else
        {
            mutData = Json::Value();
        }
    }   
}

DataPacket::DataPacket(Json::Value obj)
{
    if(obj.isNull())
        return;
    if(!obj.isMember("name"))
    {
        mutData = obj;
        return;
    }
    else
    {
        name = obj["name"].asString();
    }
    if(!obj.isMember("objFile"))
    {
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt(name, "Json object with the name " + name + " has no filename field")));
        constData = obj;
    }
    else
    {
        constData = getRoot(obj["objFile"].asString());
        objFile = obj["objFile"].asString();
    }
    if(!obj.isMember("data"))
    {
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt(name, "Json object with the name: " + name + " has no mutData values")));
    }
    Json::Value valuesArr = obj["data"];
    if(constData.isNull() || !constData.isMember("data"))
    {
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt(name, "Json object with the name: " + name + " has no mutData variables")));
        mutData = Json::Value();
    }
    else
    {
        Json::Value variablesArr = constData["data"];
        for(unsigned int i = 0; i < variablesArr.size(); i++)
        {
            mutData[variablesArr[i].asString()] = valuesArr[i];
        }
    }
}

std::string DataPacket::getName()
{
    return name;
}

int DataPacket::getInt(std::string name)
{
    int ret;
    if(mutData.isNull() || !mutData.isMember(name))
    {
        ret = constData.get(name, INT_MAX).asInt();
    }
    else
    {
        ret = mutData[name].asInt();
    }
    return ret;
}

int DataPacket::getBool(std::string name)
{
    int ret;
    if(mutData.isNull() || !mutData.isMember(name))
    {
        if(!constData.isMember(name))
            return -1;
        ret = constData[name].asBool();
    }
    else
    {
        ret = mutData[name].asBool();
    }
    return ret;
}

std::string DataPacket::getString(std::string name)
{
    std::string ret;
    if(mutData.isNull() || !mutData.isMember(name))
    {
        ret = constData.get(name, "noObject").asString();
    }
    else
    {
        ret = mutData[name].asString();
    }
    return ret;
}

double DataPacket::getDouble(std::string name)
{
    double ret;
    if(mutData.isNull() || mutData.isMember(name))
    {
        ret = constData.get(name, INFINITY).asDouble();
    }
    else
    {
        ret = mutData[name].asDouble();
    }
    return ret;
}

Json::Value DataPacket::getRoot(std::string filename)
{
    Json::Value root;
    Json::Reader reader;
    ifstream file;
    file.open(filename.c_str());
    if(!file.is_open())
    {
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt(name, "file " + filename + " cannot be opened for Json parsing")));
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
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt(name, "JSON parser cannot parse the file: " + filename + "\n\treason:" + reader.getFormatedErrorMessages())));
        return Json::Value();
    }
    return root;
}

DataPacketPtr DataPacket::getBlock(std::string name)
{
    DataPacketPtr ret;
    if(mutData.isNull() || !mutData.isMember(name))
    {
        ret = DataPacketPtr(new DataPacket(constData[name]));
    }
    else
    {
        ret = DataPacketPtr(new DataPacket(mutData[name]));
    }
    return ret;
}

std::vector<std::string> DataPacket::getStringList(std::string name)
{
    std::vector<std::string> ret;
    if(mutData.isNull() || !mutData.isMember(name))
    {
        Json::Value arr = constData[name];
        if(arr.isArray())
        {
            for(uint32_t i = 0; i < arr.size(); i++)
            {
                ret.push_back(arr[i].asString());
            }
        }
    }
    else
    {
        Json::Value arr = mutData[name];
        if(arr.isArray())
        {
            for(uint32_t i = 0; i < arr.size(); i++)
            {
                ret.push_back(arr[i].asString());
            }
        }
    }
    return ret;
}

std::string DataPacket::getDataStr()
{
    Json::Value ret;
    ret["name"] = getName();
    ret["objFile"] = objFile;
    Json::Value mutDataVari = getRoot(objFile)["data"];
    if(mutDataVari.isNull())
    {
        ret["data"] = Json::Value(Json::arrayValue);
    }
    else
    {
        for(uint32_t i = 0; i < mutDataVari.size(); i++)
        {
            ret["data"][i] = mutData[mutDataVari[i].asString()];
        }
    }
    Json::StyledWriter writer;
    std::string output = writer.write(ret);
    return output;
}
