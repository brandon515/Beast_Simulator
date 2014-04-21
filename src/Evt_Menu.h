#ifndef EVT_MENU_H_INCLUDED
#define EVT_MENU_H_INCLUDED
#include "Event.h"

class Evt_MenuData : public IEventData
{
    public:
        Evt_MenuData(bool popen);
        ~Evt_MenuData(){}
        bool open;
};

class Evt_Menu : public Event
{
    public:
        Evt_Menu(bool open);
        Evt_Menu();
        ~Evt_Menu(){}
};
#endif
