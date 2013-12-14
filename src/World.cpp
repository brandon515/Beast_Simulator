#include "World.h"

World::~World()
{
    //dtor
}

World & World::getSingleton()
{
    static World ret;
    return ret;
}
