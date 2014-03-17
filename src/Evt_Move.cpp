#include "Evt_Move.h"

Evt_MoveData::Evt_MoveData(int16_t px, int16_t py, std::string name):
    x(px),
    y(py)
{
   ID = CRC32(name.c_str(), name.length()); 
}
