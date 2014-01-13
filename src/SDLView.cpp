#include "SDLView.h"


SDLView::HumanView(std::string view):
    window(NULL),
    renderer(NULL)
{
    viewName = view;
}

SDLView::~HumanView()
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
    Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("SDL system and TTF sub-system successfully started")));
    height = getNumber(g_config, "height");
    if(height == LONG_MAX)
    {
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("height not in config file, setting to default: 600")));
        height = 600;
    }
    width = getNumber(g_config, "width");
    if(width == LONG_MAX)
    {
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("width not in config file, setting to default: 800")));
        width = 800;
    }
    windowCaption = getString(g_config, "title");
    if(windowCaption.compare("nope") == 0)
    {
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("window caption not in config file, setting to default: New Game")));
        windowCaption = "New Game";
    }
    SDL_WM_SetCaption(windowCaption.c_str(), NULL);
    uint32_t flags = SDL_DOUBLEBUF | SDL_SWSURFACE;
    bool fullscreen = getNumber(g_config, "fullscreen");

    // fullscreen implementation

    /*if(fullscreen)
    {
        const SDL_VideoInfo *info;
        info = SDL_GetVideoInfo();
        width = info->current_w;
        height = info->current_h;
        flags = flags | SDL_NOFRAME;
        SDL_putenv("SDL_VIDEO_CENTERED=center");
    }*/

    //buf = SDL_CreateRGBSurface(SDL_SWSURFACE, mapWidth, mapHeight, 32,0xff0000, 0x00ff00, 0x0000ff, 0);
    screen = SDL_SetVideoMode(width, height, bitRate, flags);
    if(screen == NULL)
    {
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("screen failed to inialize")));
        return false;
    }

    return true;
}

void SDLView::tick()
{
    
}
