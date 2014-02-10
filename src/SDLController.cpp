#include "SDLController.h"

SDLController::SDLController():
    Process("SDLController")
{}

SDLController::~SDLController()
{}

bool SDLController::init()
{
    Json::Value root = getRoot("def/Keys");
    Json::Value keyNames = root["keyNames"];
    for(uint32_t i = 0; i < keyNames.size(); i++)
    {
        std::string name = keyNames[i].asString();
        if(root[name].asInt() == 0)
        {
            std::cout << "Press new key for " << name << " : " << std::flush;
            uint32_t key = getKey();
            std::cout << key << std::endl;
            root[name] = key;
        }
    }
    Json::StyledWriter writer;
    std::string newFile = writer.write(root);
    ofstream file;
    file.open("def/Keys", ios::out|ios::trunc);
    file << newFile.c_str();
    file.close();
    return true;
}

uint32_t SDLController::getKey()
{
    uint32_t key = 0;
    while(!key)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_KEYUP)
            {
                key = event.key.keysym.sym;
            }
        }
    }
    return key;
}

void SDLController::tick()
{
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
        {
            EventPtr evt(new Evt_Keyboard(event.key.state == SDL_PRESSED, event.key.keysym.sym));
            Event_System::getSingleton().queueEvent(evt);
        }
        else if(event.type == SDL_WINDOWEVENT)
        {
            switch(event.window.event)
            case SDL_WINDOWEVENT_CLOSE:
            {
                EventPtr evt(new Evt_CloseWindow(event.window.windowID));
                Event_System::getSingleton().queueEvent(evt);
                break;
            }
        }
    }
}

Json::Value SDLController::getRoot(std::string filename)
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
