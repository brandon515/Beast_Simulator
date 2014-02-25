#include "SDLView.h"

Texture::Texture(DataPacketPtr data, SDL_Renderer *render)
{
    int isAnimated = data->getBool("animated");
    if(isAnimated < 1)
    {
        std::string imageStr = data->getString("image");
        SDL_Texture *tex = NULL;
        SDL_Surface *sur = IMG_Load(imageStr.c_str());
        if(sur == NULL)
        {
                Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("SDL can't load image named " + imageStr + " \n\treason: " + IMG_GetError())));
        }
        tex = SDL_CreateTextureFromSurface(render, sur);
        if(tex == NULL)
        {
                Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("SDL can't create texture from file named " + imageStr + " \n\treason: " + IMG_GetError())));
        }
        SDL_FreeSurface(sur);
        animated = false;
        AnimationData dat;
        dat.texture = tex;
        dat.maxFrames = 1;
        curFrame = 1;
        dat.area.x = dat.area.y = 0;
        SDL_QueryTexture(tex, NULL, NULL, &dat.area.w, &dat.area.h);
        curTexture = dat;
    }
    else
    {
        std::vector<std::string> states;
        states = data->getStringList("states");
        for(std::vector<std::string>::iterator it = states.begin(); it != states.end(); it++)
        {
            //load texture
            DataPacketPtr block = data->getBlock(*it);
            std::string imageStr = block->getString("image");
            if(imageStr.compare("noObject") == 0)
            {
                Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("Block " + (*it) + " is not valid")));
                continue;
            }
            SDL_Texture *tex = NULL;
            SDL_Surface *sur = IMG_Load(imageStr.c_str());
            SDL_SetColorKey(sur, SDL_TRUE, SDL_MapRGB(sur->format, 0xFF, 0x00, 0xFF));
            if(sur == NULL)
            {
                Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("SDL can't load image named " + imageStr + " \n\treason: " + IMG_GetError())));
                continue;
            }
            tex = SDL_CreateTextureFromSurface(render, sur);
            SDL_FreeSurface(sur);
            if(tex == NULL)
            {
                Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("SDL can't create texture from file named " + imageStr + " \n\treason: " + IMG_GetError())));
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
            dat.area.w = block->getInt("w");
            dat.area.h = block->getInt("h");
            //add to texture map
            TextureEnt ent(hash, dat);
            TextureRes res = textures.insert(ent);
            if(res.first == textures.end() || res.second == false)
            {
                Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("Texture was not able to be added to map")));
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
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    curTexture.area.x = curTexture.area.w * (curFrame-1);
    pos.w = curTexture.area.w;
    pos.h = curTexture.area.h;
    SDL_RenderCopy(render, curTexture.texture, &curTexture.area, &pos);
    if(animated)
    {
        if(curFrame >= curTexture.maxFrames)
            curFrame = 1;
        else
            curFrame += 1;
    }
    //Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("\tmaxFrames: " + boost::lexical_cast<std::string>(curTexture.maxFrames) + "\n\tcurFrames: " + boost::lexical_cast<std::string>(curFrame))));
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
    IMG_Init(IMG_INIT_PNG);
    Json::Value root = getRoot("WindowSettings");
    uint32_t flags = 0;
    if(root["fullscreen"].asBool() == true)
    {
        flags = SDL_WINDOW_FULLSCREEN_DESKTOP|SDL_WINDOW_BORDERLESS;
    }
    int w = 800, h = 600;
    if(root["width"].isInt())
    {
        w = root["width"].asInt();
    }
    if(root["height"].isInt())
    {
        h = root["height"].asInt();
    }
    std::string title = "New Window";
    if(root["title"].isString())
    {
        title = root["title"].asString();
    }
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
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("SDL window failed to initilize: " + error)));
        return false;
    }
    setID(SDL_GetWindowID(window));
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
    {
        std::string error(SDL_GetError());
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("SDL window failed to initilize: " + error)));
        return false;
    } 
    return true;
}

bool SDLView::add(DataPacketPtr data)
{
    Texture *tex = new Texture(data, renderer);
    uint32_t hash = CRC32(data->getName().c_str(), data->getName().length());
    TextureEnt ent(hash, tex);
    TextureRes res = textures.insert(ent);
    if(res.first == textures.end() || res.second == false)
    {
            Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("Texture " + data->getName() + " couldn't be added into the Map")));
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

Json::Value SDLView::getRoot(std::string filename)
{
    Json::Value root;
    Json::Reader reader;
    ifstream file;
    file.open(filename.c_str());
    if(!file.is_open())
    {
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("file " + filename + " cannot be opened for Json parsing")));
        return Json::Value(false);
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
        return Json::Value(false);
    }
    return root;
}
