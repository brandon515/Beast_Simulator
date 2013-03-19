#include "G_System.h"

G_System & G_System::getSingleton()
{
    static G_System inst;
    return inst;
}

G_System::~G_System()
{
    SDL_FreeSurface(screen);
}

bool G_System::setup()
{
    m_height = getNumber(g_config, "height");
    if(m_height == LONG_MAX)
    {
        m_log.log("height not in config file, setting to default:: 600");
        m_height = 600;
    }
    m_width = getNumber(g_config, "width");
    if(m_width == LONG_MAX)
    {
        m_log.log("width not in config file, setting to default: 800");
        m_width = 800;
    }
    m_bitRate = getNumber(g_config, "bit_rate");
    if(m_bitRate == LONG_MAX)
    {
        m_log.log("bit rate not in config file, setting to default: 32");
        m_bitRate = 32;
    }
    m_windowCaption = getString(g_config, "title");
    if(m_windowCaption.compare("nope") == 0)
    {
        m_log.log("window caption not in config file, setting to default");
        m_windowCaption = "New Game";
    }
    screen = SDL_SetVideoMode(m_width, m_height, m_bitRate, SDL_SWSURFACE);
    if(screen == NULL)
    {
        m_log.log("screen failed to inialize");
        return false;
    }
    if(!Event_System::getSingleton().addListener(EventListenerPtr(this), Evt_Move().getType()))
    {
        m_log.log("graphics system not hooked into Event System");
        return false;
    }
    SDL_WM_SetCaption(m_windowCaption.c_str(), NULL);
    return true;
}

void G_System::render()
{
    for(ScreenElementList::iterator it = renList.begin(); it != renList.end(); it++)
    {
        (*it).second.get()->update();
        (*it).second.get()->render(screen);
    }
}

uint32_t G_System::add(ScreenElementPtr const & obj)
{
    if(obj.get() == NULL)
        return 0;
    uint32_t ID = getNextId();
    ScreenElementEnt ent(ID, obj);
    ScreenElementRes res = renList.insert(ent);
    if(res.first == renList.end())
        return 0;
    else if(!res.second)
        return 0;
    return ID;
}

bool G_System::handleEvent(Event const & event)
{
    if(event.getType() == Evt_Move().getType())
    {
        Evt_MoveData *dat = event.getDataPtr<Evt_MoveData>();
        ScreenElementList::iterator selIt = renList.find(dat->ID);
        if(selIt == renList.end())
        {
            std::string msg = "creature ID " + boost::lexical_cast<std::string>(dat->ID) + " not available";
            m_log.log(msg);
            return true;
        }
        ScreenElementPtr ent = (*selIt).second;
        ent.get()->move(dat->x, dat->y);
        return true;
    }
    return false;
}

uint32_t G_System::getNextId()
{
    m_curID++;
    return m_curID;
}
