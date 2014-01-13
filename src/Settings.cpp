#include "Settings.h"

Settings & Settings::getSingleton()
{
    static Settings ret;
    return ret;
}
