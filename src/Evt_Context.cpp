#include "Evt_Context.h"

Evt_ContextData::Evt_ContextData(std::string name):
    contextStr(name)
{
    contextID = CRC32(name.c_str(), name.length());
}

Evt_Context::Evt_Context(std::string name):
    Event("context", IEventDataPtr(new Evt_ContextData(name)))
{}

Evt_Context::Evt_Context():
    Event("context")
{}
