#ifndef HUMANVIEW_H_INCLUDED
#define HUMANVIEW_H_INCLUDED
#include <boost/serialization/map.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/make_shared.hpp>
#include <fstream>
#include "Interfaces.h"
#include "Logging.h"
#include "globals.h"
#include "ViewSystem.h"
#include "GameEvents.h"
#include "TestObject.h"
#include "Map.h"
#include <map>
#include <Gui.h>
#include <vector>
#include <SDL\SDL.h>
#include <SDL\SDL_ttf.h>


enum VirtualKeys
{
    VK_EXIT,
    VK_MAPRIGHT,
    VK_MAPLEFT,
    VK_MAPUP,
    VK_MAPDOWN
};

//Purpose: To handle all human interaction with the system. it's only interaction with the system must be firing events and reciving events

class HumanView : public IGameView, public IEventListener
{
    public:
        HumanView();
        ~HumanView();
        bool init();
        void tick();
        bool handleEvent(Event const & event);
    private:

        //typedefs

        typedef std::vector<IScreenElementPtr> IScreenElementMap;
        typedef std::pair<uint32_t, IScreenElementPtr> IScreenElementEnt;
        typedef std::pair<IScreenElementMap::iterator, bool> IScreenElementRes;

        typedef std::map<SDLKey, VirtualKeys> VirtualKeyboard;
        typedef std::pair<SDLKey, VirtualKeys> VirtualKeyboardEnt;
        typedef std::pair<VirtualKeyboard::iterator, bool> VirtualKeyboardRes;

        //member variables

        SDL_Surface *screen, *buf, *test;
        IScreenElementMap *renderableObjects;
        VirtualKeyboard keys;
        Logging log;
        SDL_Rect offset, vec, mapRect;
        SDL_Event event;
        Map mapSur;

        //member functions

        void handleKeyboard(SDLKey key, bool keyDown);
};

typedef boost::shared_ptr<HumanView> HumanViewPtr;

#endif // HUMANVIEW_H_INCLUDED
