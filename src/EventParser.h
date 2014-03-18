#ifndef EVENTPARSER_H_INCLUDED
#define EVENTPARSER_H_INCLUDED
#include "Event_System.h"
#include "MsgEvt.h"
#include "Evt_Move.h"
#include "Evt_CloseApplication.h"
#include "Evt_CloseWindow.h"
#include "Evt_JoystickAxis.h"
#include "Evt_JoystickButton.h"
#include "Evt_Keyboard.h"
#include "Evt_WindowFocus.h"
#include <string>

extern "C"
{
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

namespace EventParser
{
    bool parseEvent(std::string evt);
    bool parseEvent(lua_State *l);
}
#endif
