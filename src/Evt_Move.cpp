#include "Evt_Move.h"

Evt_MoveData::Evt_MoveData(int16_t px, int16_t py, std::string pName):
    x(px),
    y(py),
    name(pName)
{
   ID = CRC32(name.c_str(), name.length()); 
}
