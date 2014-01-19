#include "SDLView.h"


SDLView::SDLView(std::string view):
    window(NULL),
    renderer(NULL)
{
    viewName = view;
}

SDLView::~SDLView()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

bool SDLView::init()
{
    //SDL and Screen initalization

    if(SDL_Init(SDL_INIT_EVERYTHING)!=0)
    {
        std::string error(SDL_GetError());
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("SDL failed to initilize: " + error)));
        return false;
    }
    window = SDL_CreateWindow(
                "Test Window",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                0,
                0,
                SDL_WINDOW_FULLSCREEN_DESKTOP|SDL_WINDOW_BORDERLESS);
    if(window == NULL)
    {
        std::string error(SDL_GetError());
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("SDL window failed to initilize: " + error)));
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
    {
        std::string error = SDL_GetError();
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("SDL window failed to initilize: " + error)));
        return false;
    } 
    return true;
}

bool SDLView::loadFile(std::string filename)
{
    Json::Value root;
    Json::Reader reader;
    ifstream file;
    file.open(filename.c_str());
    if(!file.is_open())
    {
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("file " + filename + " cannot be opened for Json parsing")));
        return false;
    }
    file.seekg(0, file.end);
    int len = file.tellg();
    file.seekg(0, file.beg);
    char *dat = new char[len];
    file.read(dat, len);
    std::string fileStr(dat);
    file.close();
    if(!reader.parse(fileStr, root))
    {
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("JSON parser cannot parse the file: " + filename + "\n\treason:" + reader.getFormatedErrorMessages())));
        return false;
    }
    Json::Value array = root["mapObjects"];
    for(int i = 0; true; i++)
    {
        Json::Value obj = array[i];
        if(obj == NULL)
            break;
        std::string name, filename;
        name = obj["name"].asString();
        filename = obj["image"].asString();
        add(name, filename);
    }
    return true;
}

bool SDLView::add(std::string name, std::string filename)
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
