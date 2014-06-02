#include "SDLView.h"

Texture::Texture(DataPacketPtr data, SDL_Renderer *render)
{
    int isAnimated = data->getBool("animated");
    string direct = data->getString("direction");
    if(direct.compare("right") == 0)
    {
        lookingRight = true;
    }
    else if(direct.compare("left") == 0)
    {
        lookingRight = false;
    }
    else
    {
        lookingRight = true;
    }
    if(isAnimated < 1)
    {
        std::string imageStr = data->getString("image");
        SDL_Texture *tex = NULL;
        SDL_Surface *sur = IMG_Load(imageStr.c_str());
        if(sur == NULL)
        {
            Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("SDL View","SDL can't load image named " + imageStr + " \n\treason: " + IMG_GetError())));
        }
        tex = SDL_CreateTextureFromSurface(render, sur);
        if(tex == NULL)
        {
            Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("SDL View","SDL can't create texture from file named " + imageStr + " \n\treason: " + IMG_GetError())));
        }
        SDL_FreeSurface(sur);
        animated = false;
        AnimationData dat;
        dat.texture = tex;
        dat.maxFrames = 1;
        curFrame = 1;
        dat.area.x = dat.area.y = 0;
        SDL_QueryTexture(tex, NULL, NULL, &dat.screenArea.w, &dat.screenArea.h);
        dat.area.w = dat.screenArea.w;
        dat.area.h = dat.screenArea.h;
        curTexture = dat;
    }
    else
    {
        std::vector<std::string> states;
        states = data->getStringList("states");
        lastRenderTime = 0;
        for(std::vector<std::string>::iterator it = states.begin(); it != states.end(); it++)
        {
            //load texture
            DataPacketPtr block = data->getBlock(*it);
            std::string imageStr = block->getString("image");
            if(imageStr.compare("noObject") == 0)
            {
                Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("SDL View","Block " + (*it) + " is not valid")));
                continue;
            }
            SDL_Texture *tex = NULL;
            SDL_Surface *sur = IMG_Load(imageStr.c_str());
            SDL_SetColorKey(sur, SDL_TRUE, SDL_MapRGB(sur->format, 0xFF, 0x00, 0xFF));
            if(sur == NULL)
            {
                Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("SDL View","SDL can't load image named " + imageStr + " \n\treason: " + IMG_GetError())));
                continue;
            }
            tex = SDL_CreateTextureFromSurface(render, sur);
            SDL_FreeSurface(sur);
            if(tex == NULL)
            {
                Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("SDL View","SDL can't create texture from file named " + imageStr + " \n\treason: " + IMG_GetError())));
                continue;
            }
            //load animation data
            uint32_t hash = CRC32((*it).c_str(), (*it).length());
            animated = true;
            curFrame = 1;
            AnimationData dat;
            dat.texture = tex;
            dat.maxFrames = block->getInt("frames");
            dat.area.x = dat.area.y = 0;
            dat.area.w = block->getInt("frameWidth");
            dat.area.h = block->getInt("frameHeight");
            dat.screenArea.w = block->getInt("screenWidth");
            dat.screenArea.h = block->getInt("screenHeight");
            dat.fps = block->getInt("fps");
            //add to texture map
            TextureEnt ent(hash, dat);
            TextureRes res = textures.insert(ent);
            if(res.first == textures.end() || res.second == false)
            {
                Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("SDL View","Texture was not able to be added to map")));
                continue;
            }
            //if starting state than make it so
            if(data->getString("startingState").compare(*it) == 0)
            {
                curTexture = dat;
            }
        }
    }
}

void Texture::render(SDL_Renderer *render, int x, int y)
{
    float deltaRenderTime, secondsPerFrame;
    if(animated)
    {
        deltaRenderTime = boost::lexical_cast<float>(clock()-lastRenderTime)/CLOCKS_PER_SEC;  
        secondsPerFrame = 1.0f/boost::lexical_cast<float>(curTexture.fps);
    }
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    curTexture.area.x = curTexture.area.w * (curFrame-1);
    pos.w = curTexture.screenArea.w;
    pos.h = curTexture.screenArea.h;
    SDL_RendererFlip flipIt = lookingRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    SDL_RenderCopyEx(render, curTexture.texture, &curTexture.area, &pos, 0, NULL, flipIt);
    if(animated && deltaRenderTime > secondsPerFrame)
    {
        if(curFrame >= curTexture.maxFrames)
        {
            curFrame = 1;
        }
        else
        {
            curFrame += 1;
        }
        lastRenderTime = clock();
    }
}

bool Texture::setState(std::string pState)
{
    uint32_t hash = CRC32(pState.c_str(), pState.length());
    TextureMap::iterator it = textures.find(hash);
    if(it == textures.end())
        return false;
    curTexture = it->second;
    return true;
}

SDLView::SDLView():
    View(0),
    window(NULL),
    renderer(NULL)
{
}

SDLView::~SDLView()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("SDL View","SDLView is dead")));
}

bool SDLView::init()
{
    //SDL and Screen initalization

    if(SDL_Init(SDL_INIT_EVERYTHING)!=0)
    {
        std::string error(SDL_GetError());
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("SDL View","SDL failed to initilize: " + error)));
        return false;
    }
    IMG_Init(IMG_INIT_PNG);
    DataPacketPtr data(new DataPacket("", "def/WindowSettings", ""));
    uint32_t flags = 0;
    if(data->getBool("fullscreen") == true)
    {
        flags = SDL_WINDOW_FULLSCREEN_DESKTOP|SDL_WINDOW_BORDERLESS;
    }
    int w = 800, h = 600;
    w = data->getInt("width");
    h = data->getInt("height");
    std::string title = data->getString("title");
    window = SDL_CreateWindow(
                title.c_str(),
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                w,
                h,
                flags);
    if(window == NULL)
    {
        std::string error(SDL_GetError());
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("SDL View","SDL window failed to initilize: " + error)));
        return false;
    }
    setID(SDL_GetWindowID(window));
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
    {
        std::string error(SDL_GetError());
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("SDL View","SDL renderer failed to initilize: " + error)));
        return false;
    } 
    return true;
}

bool SDLView::add(DataPacketPtr data)
{
    std::vector<std::string> types;
    types = data->getStringList("type");
    bool isRenderable = false;
    for(std::vector<std::string>::iterator it = types.begin(); it != types.end(); it++)
    {
        if((*it).compare("renderable") == 0)
        {
            isRenderable = true;
            break;
        }
    }
    if(!isRenderable)
        return true;
    Texture *tex = new Texture(data, renderer);
    uint32_t hash = CRC32(data->getName().c_str(), data->getName().length());
    TextureEnt ent(hash, tex);
    TextureRes res = textures.insert(ent);
    if(res.first == textures.end() || res.second == false)
    {
            Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("SDL View","Texture " + data->getName() + " couldn't be added into the Map")));
            return false;
    }
    return true;
}

void SDLView::remove(std::string name)
{
    TextureMap::iterator it = textures.find(CRC32(name.c_str(), name.length()));
    textures.erase(it);
}

void SDLView::preFrame()
{
    SDL_RenderClear(renderer);
}

void SDLView::onFrame(DataPacketPtr data)
{
    uint32_t hash = CRC32(data->getName().c_str(), data->getName().length());
    TextureMap::iterator it = textures.find(hash);
    Texture *temp = it->second;
    int x = data->getInt("x");
    int y = data->getInt("y");
    temp->render(renderer, x, y);
}

void SDLView::postFrame()
{
    SDL_RenderPresent(renderer);
}
