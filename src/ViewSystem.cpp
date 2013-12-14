#include "ViewSystem.h"

ViewSystem & ViewSystem::getSingleton()
{
    static ViewSystem ret;
    return ret;
}

bool ViewSystem::addView(IGameViewPtr obj)
{
    if(!obj.get()->init())
        return false;
    gameViews.push_back(obj);
    return true;
}

void ViewSystem::tick()
{
    for(IGameViewList::iterator it = gameViews.begin(); it != gameViews.end(); it++)
    {
        (*it).get()->tick();
        if((*it).get()->needsDelete)
        {
            delView((*it));
            break;
        }
    }
}

bool ViewSystem::isEmpty()
{
    return gameViews.empty();
}

bool ViewSystem::delView(IGameViewPtr obj)
{
    bool erased = false;
    for(IGameViewList::iterator it = gameViews.begin(); it != gameViews.end(); it++)
    {
        IGameViewPtr itPtr = (*it);
        if(itPtr.get() == obj.get())
        {
            gameViews.erase(it);
            erased = true;
            break;
        }
    }
    return erased;
}
