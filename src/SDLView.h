#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "MsgEvt.h"
#include "Event_System.h"
#include "View.h"
#include "Methods.h"
#include <json/json.h>
#include <fstream>

class SDLView : public View
{
    public:
        SDLView(std::string view);
        ~SDLView();
        bool init();
        bool add(std::string name, std::string filename);
        void remove(std::string name);
        void preFrame();
        void onFrame(std::string name, int x, int y);
        void postFrame();
    private:
        //typedefs

        typedef std::map<uint32_t, SDL_Texture*> TextureMap;
        typedef std::pair<uint32_t, SDL_Texture*> TextureEnt;
        typedef std::pair<TextureMap::iterator, bool> TextureRes;

        //private functions

        Json::Value getRoot(std::string filename);

        TextureMap textures;
        std::string viewName;
        SDL_Window *window;
        SDL_Renderer *renderer;
        bool fullscreen;
        uint32_t height, width;
};

typedef boost::shared_ptr<SDLView> SDLViewPtr;
