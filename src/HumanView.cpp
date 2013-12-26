#include "HumanView.h"


HumanView::HumanView(std::string playerName):
    IEventListener(playerName)
{
<<<<<<< HEAD
=======
    plName = playerName;
>>>>>>> 3e7a77d718251ff59f88a128d6f1b33dd3a6cfb6
}

HumanView::~HumanView()
{
    Logging().log("human view destroyed");
}

bool HumanView::init()
{
<<<<<<< HEAD
    uint32_t width, height, bitRate;
    std::string windowCaption;

    //SDL and Screen initalization

    /*if(SDL_Init(SDL_INIT_EVERYTHING)==-1 || TTF_Init() == -1)
    {
        Logging().log(SDL_GetError());
        return false;
    }
    Logging().log("SDL system and TTF sub-system successfully started");
    height = getNumber(g_config, "height");
    if(height == LONG_MAX)
    {
        Logging().log("height not in config file, setting to default: 600");
        height = 600;
    }
    width = getNumber(g_config, "width");
    if(width == LONG_MAX)
    {
        Logging().log("width not in config file, setting to default: 800");
        width = 800;
    }
    bitRate = getNumber(g_config, "bit_rate");
    if(bitRate == LONG_MAX)
    {
        Logging().log("bit rate not in config file, setting to default: 32");
        bitRate = 32;
    }
    windowCaption = getString(g_config, "title");
    if(windowCaption.compare("nope") == 0)
    {
        Logging().log("window caption not in config file, setting to default: New Game");
        windowCaption = "New Game";
    }
    SDL_WM_SetCaption(windowCaption.c_str(), NULL);
    uint32_t flags = SDL_DOUBLEBUF | SDL_SWSURFACE;
    bool fullscreen = getNumber(g_config, "fullscreen");

    // fullscreen implementation

    if(fullscreen)
    {
        const SDL_VideoInfo *info;
        info = SDL_GetVideoInfo();
        width = info->current_w;
        height = info->current_h;
        flags = flags | SDL_NOFRAME;
        SDL_putenv("SDL_VIDEO_CENTERED=center");
    }
    //buf = SDL_CreateRGBSurface(SDL_SWSURFACE, mapWidth, mapHeight, 32,0xff0000, 0x00ff00, 0x0000ff, 0);
    screen = SDL_SetVideoMode(width, height, bitRate, flags);
    if(screen == NULL)
    {
        Logging().log("screen failed to inialize");
        return false;
    }*/

=======
>>>>>>> 3e7a77d718251ff59f88a128d6f1b33dd3a6cfb6
    Logging().log("Human View created");
    return true;
}

void HumanView::tick()
{
}

bool HumanView::handleEvent(Event const &event)
{
    return false;
}
