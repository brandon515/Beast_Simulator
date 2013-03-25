#ifndef G_SYSTEM_H_INCLUDED
#define G_SYSTEM_H_INCLUDED
#include <SDL\SDL.h>
#include <SDL\SDL_ttf.h>
#include "globals.h"
#include "Methods.h"
#include "IScreenElement.h"
#include "IEventListener.h"
#include "Logging.h"
#include "GameEvents.h"
#include <climits>
#include <map>
#include <boost\shared_ptr.hpp>
#include <boost\lexical_cast.hpp>

typedef boost::shared_ptr<IScreenElement> ScreenElementPtr;
typedef std::map<uint32_t, ScreenElementPtr> ScreenElementList;
typedef std::pair<uint32_t, ScreenElementPtr> ScreenElementEnt;
typedef std::pair<ScreenElementList::iterator, bool> ScreenElementRes;

class G_System : public IEventListener
{
    public:
        static G_System & getSingleton();
        ~G_System();
        bool setup();
        void render();
        uint32_t add(ScreenElementPtr const & obj);
        bool handleEvent(Event const & event);
        const ScreenElementList getRenderList() const;
    private:

        //singleton uninitialized functions

        G_System():m_curID(0) {}
        G_System(G_System const&);
        void operator=(G_System const&);

        //neccessary member functions and variables

        SDL_Surface *screen;
        uint32_t m_height, m_width, m_bitRate, m_curID;
        std::string m_windowCaption;
        ScreenElementList renList;
        Logging m_log;

        //ID aquisition

        uint32_t getNextId();
};

#endif // G_SYSTEM_H_INCLUDED
