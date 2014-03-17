#ifndef EVENTPARSER_H_INCLUDED
#define EVENTPARSER_H_INCLUDED
#include "Event_System.h"


extern "C"
{
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

namespace EventParser
{
    bool parserEvent(std::string evt);
    bool parseEvent(lua_State *l);
}
#endif
