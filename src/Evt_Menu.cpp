#include "Evt_Menu.h"


Evt_MenuData::Evt_MenuData(bool popen):
    open(popen)
{}

Evt_Menu::Evt_Menu(bool open):
    Event("Menu", IEventDataPtr(new Evt_MenuData(open)))
{}

Evt_Menu::Evt_Menu():
    Event("Menu")
{}
