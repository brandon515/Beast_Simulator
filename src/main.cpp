#include "main.h"

int main(int argc, char *argv[])
{
    std::ifstream file;
    file.open("testJson");
    if(!file.is_open())
    {
        std::cout << "failure\n";
        return 1;
    }
    file.seekg(0, file.end);
    int len = file.tellg();
    file.seekg(0, file.beg);
    char * fileData = new char[len];
    file.read(fileData,len);
    std::string fileStr(fileData);
    Json::Value root;
    Json::Reader reader;
    if(!reader.parse(fileStr, root))
    {
        std::cout << reader.getFormatedErrorMessages() << "\n";
    }
    Json::Value mapObjects = root["mapObjects"];
    Json::Value ent = mapObjects[0u];
    std::string blah = ent["name"].asString();
    std::cout << blah << "\n";
    std::cout << "hey!\n";
    return 0;
}
