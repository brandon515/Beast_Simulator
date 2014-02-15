#include "VirtualKeyboard.h"

VirtualKeyboard & VirtualKeyboard::getSingleton()
{
    static VirtualKeyboard ret;
    return ret;
}

VirtualKeyboard::VirtualKeyboard()
{
    Json::Reader reader;
    std::ifstream file;
    file.open("def/Keys");
    file.seekg(0, std::ios::end);
    int size = file.tellg();
    file.seekg(0, std::ios::beg);
    char *buf = new char[size];
    file.read(buf, size);
    std::string dat(buf);
    file.close();
    if(!reader.parse(dat, root))
    {
        std::string err = "unable to parse Keys file";
        EventPtr evt(new MsgEvt(err));
        Event_System::getSingleton().queueEvent(evt);
    }
}

uint32_t VirtualKeyboard::getKeyInt(std::string keyName)
{
    uint32_t key = root.get(keyName.c_str(), 0).asUInt();
    return key;
}

bool VirtualKeyboard::changeKey(std::string keyName, uint32_t newKey)
{
    uint32_t key = root.get(keyName.c_str(), 0).asUInt();
    if(key == 0)
        return false;
    root[keyName.c_str()] = newKey;
    Json::StyledWriter writer;
    std::string out = writer.write(root);
    std::ofstream file;
    file.open("def/Keys");
    file << out;
    file.close();
    return true;
}

bool VirtualKeyboard::registerNewKey(std::string keyName, uint32_t newKey)
{
    uint32_t key = root.get(keyName.c_str(), 0).asUInt();
    if(key != 0)
        return false;
    root[keyName.c_str()] = newKey;
    Json::StyledWriter writer;
    std::string out = writer.write(root);
    std::ofstream file;
    file.open("def/Keys");
    file << out;
    file.close();
    return true;
}
