#include "Process.h"
#include <map>
#include <SDL/SDL.h>
#include "MsgEvt.h"
#include "Event_System.h"
#include "View.h"

class SDLView : public View
{
    public:
        SDLView(std::string view);
        ~SDLView();
        bool init();
        bool add(std::string name);
        void remove(std::string name);
        bool render();
    private:
        std::string viewName;
        SDL_Window *window;
        SDL_Renderer *renderer;
        bool fullscreen;
        uint32_t height, width;
};

typedef boost::shared_ptr<SDLView> SDLViewPtr;
