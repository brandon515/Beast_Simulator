#include "HumanView.h"


HumanView::HumanView()
{
    offset.x = 0;
    offset.y = 0;
    vec.x = 0;
    vec.y = 0;
    //HumanViewPtr viewPtr(this);
    //ViewSystem::getSingleton().addView(viewPtr);
    keys.clear();
}

HumanView::~HumanView()
{
    Logging().log("human view destroyed");
    SDL_FreeSurface(screen);
}

bool HumanView::init()
{
    uint32_t width, height, bitRate;
    std::string windowCaption;

    //SDL and Screen initalization

    if(SDL_Init(SDL_INIT_EVERYTHING)==-1 || TTF_Init() == -1)
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
    }

    //loading Keyboard settings

    std::ifstream file("bindings");
    boost::archive::binary_iarchive arch(file);

    arch & keys;
    file.close();

    /*keys.insert(VirtualKeyboardEnt(SDLK_ESCAPE, VK_EXIT));
    keys.insert(VirtualKeyboardEnt(SDLK_UP, VK_MAPUP));
    keys.insert(VirtualKeyboardEnt(SDLK_DOWN, VK_MAPDOWN));
    keys.insert(VirtualKeyboardEnt(SDLK_LEFT, VK_MAPLEFT));
    keys.insert(VirtualKeyboardEnt(SDLK_RIGHT, VK_MAPRIGHT));
    std::ofstream file2("bindings");
    boost::archive::binary_oarchive arch2(file2);
    arch2 & keys;
    file2.close();*/

    renderableObjects = World::getSingleton().GetScreenList();
    mapSur.init();

    // adding myself to the event system

    /*IEventListener *evtDataPtr = this;
    EventListenerPtr evtListen(evtDataPtr);

    if(!Event_System::getSingleton().addListener(evtListen, Evt_Keyboard().getType()) || !Event_System::getSingleton().addListener(evtListen, Evt_Quit().getType()))
    {
        Logging().log("Human View not hooked into Event System");
        return false;
    }
    Logging().log("Human View added to Event_System");*/

    Logging().log("Human View created");
    return true;
}

void HumanView::tick()
{
    for(IScreenElementMap::iterator it = renderableObjects->begin(); it != renderableObjects->end(); it++)
    {
        it->get()->render(mapSur.getBufMap());
    }
    mapSur.update();
    mapSur.render();
    SDL_Flip(screen);
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
        {
            handleKeyboard(event.key.keysym.sym, event.type == SDL_KEYDOWN);
        }
        else if(event.type == SDL_QUIT)
        {
            /*IEventListener *datE = this;
            EventListenerPtr datEPtr(datE);
            Event_System::getSingleton().delListener(datEPtr, EventType(wildCardType));*/
            //ViewSystem::getSingleton().delView(this);
            needsDelete = true;
        }
    }
}

void HumanView::handleKeyboard(SDLKey key, bool keyDown)
{
    VirtualKeyboard::iterator ret = keys.find(key);
    if(ret != keys.end())
    {
        switch((*ret).second)
        {
            case VK_EXIT:
                needsDelete = true;
                break;
            case VK_MAPRIGHT:
                keyDown ? mapSur.addVecX(-20) : mapSur.addVecX(20);
                break;
            case VK_MAPLEFT:
                keyDown ? mapSur.addVecX(20) : mapSur.addVecX(-20);
                break;
            case VK_MAPUP:
                keyDown ? mapSur.addVecY(20) : mapSur.addVecY(-20);
                break;
            case VK_MAPDOWN:
                keyDown ? mapSur.addVecY(-20) : mapSur.addVecY(20);
                break;
            default:
                break;
        }
    }
}

bool HumanView::handleEvent(Event const &event)
{
    return false;
}
