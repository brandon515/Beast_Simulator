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
    m_width = getNumber(g_config, "width");
    m_bitRate = getNumber(g_config, "bit_rate");
    m_windowCaption = getString(g_config, "title");
    screen = SDL_SetVideoMode(m_width, m_height, m_bitRate, SDL_SWSURFACE);
    if(screen == NULL)
    {
        cerr << "screen failed to inialize";
        return false;
    }
    SDL_WM_SetCaption(m_windowCaption.c_str(), NULL);
    return true;
}

void G_System::render()
{
    for(ScreenElementList::iterator it = renList.begin(); it != renList.end(); it++)
    {
        (*it).get()->update();
        (*it).get()->render(screen);
    }
}

void G_System::add(ScreenElementPtr const & obj)
{
    renList.push_back(obj);
}
