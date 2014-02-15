#ifndef VIRTUALKEYBOARD_H_INCLUDED
#define VIRTUALKEYBOARD_H_INCLUDED 
#include "Event_System.h"
#include "MsgEvt.h"
#include <json/json.h>
#include <fstream>
#include <stdint.h>

class VirtualKeyboard
{
    public:

        static VirtualKeyboard & getSingleton();
        uint32_t getKeyInt(std::string keyName);
        bool changeKey(std::string keyName, uint32_t newKey);
        bool registerNewKey(std::string keyName, uint32_t newKey);

    private:

        VirtualKeyboard();
        VirtualKeyboard(VirtualKeyboard const &);
        bool operator=(VirtualKeyboard const &);

        Json::Value root;
};
#endif
