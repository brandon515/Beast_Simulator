#include "SDLView.h"


SDLView::SDLView(std::string view):
    window(NULL),
    renderer(NULL)
{
    viewName = view;
}

SDLView::~SDLView()
{

}

bool SDLView::init()
{
    //SDL and Screen initalization

    if(SDL_Init(SDL_INIT_EVERYTHING)!=0)
    {
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt(SDL_GetError())));
        return false;
    }
    return true;
}

bool SDLView::add(std::string name)
{
    return false;
}

void SDLView::remove(std::string name)
{
    
}

bool SDLView::render()
{
    return false;
}
