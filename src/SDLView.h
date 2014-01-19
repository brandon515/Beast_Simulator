#include "Process.h"
#include <map>
#include <SDL/SDL.h>
#include "MsgEvt.h"
#include "Event_System.h"
#include "View.h"
#include <json/json.h>
#include <fstream>

class SDLView : public View
{
    public:
        SDLView(std::string view);
        ~SDLView();
        bool loadFile(std::string filename);
        bool init();
        bool add(std::string name, std::string filename);
        void remove(std::string name);
        bool render();
    private:
        //typedefs

        typedef std::map<uint32_t, SDL_Texture> TextureMap;
        typedef std::pair<uint32_t, SDL_Texture> TextureEnt;
        typedef std::pair<TextureMap::iterator, bool> TextureRes;

        std::string viewName;
        SDL_Window *window;
        SDL_Renderer *renderer;
        bool fullscreen;
        uint32_t height, width;
};

typedef boost::shared_ptr<SDLView> SDLViewPtr;
