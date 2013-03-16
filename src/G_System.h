#ifndef G_SYSTEM_H_INCLUDED
#define G_SYSTEM_H_INCLUDED
#include <SDL\SDL.h>
#include <SDL\SDL_ttf.h>
#include <vector>
#include "globals.h"
#include "Methods.h"
#include "IScreenElement.h"
#include "IEventListener.h"
#include "Event.h"
#include <boost\shared_ptr.hpp>

typedef boost::shared_ptr<IScreenElement> ScreenElementPtr;
typedef std::vector<ScreenElementPtr> ScreenElementList;

class G_System
{
    public:
        static G_System & getSingleton();
        ~G_System();
        bool setup();
        void render();
        void add(ScreenElementPtr const & obj);
    private:
        G_System() {}
        G_System(G_System const&);
        void operator=(G_System const&);
        SDL_Surface *screen;
        uint32_t m_height, m_width, m_bitRate;
        std::string m_windowCaption;
        ScreenElementList renList;
};

#endif // G_SYSTEM_H_INCLUDED
