#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "MsgEvt.h"
#include "Event_System.h"
#include "View.h"
#include "Methods.h"
#include "DataPacket.h"
#include <json/json.h>
#include <fstream>
#include <boost/lexical_cast.hpp>

class SDLView : public View
{
    public:
        SDLView();
        ~SDLView();
        bool init();
        bool add(DataPacket data);
        void remove(std::string name);
        void preFrame();
        void onFrame(DataPacket data);
        void postFrame();
    private:
        //typedefs

        typedef std::map<uint32_t, SDL_Texture*> TextureMap;
        typedef std::pair<uint32_t, SDL_Texture*> TextureEnt;
        typedef std::pair<TextureMap::iterator, bool> TextureRes;

        //private functions

        Json::Value getRoot(std::string filename);

        TextureMap textures;
        SDL_Window *window;
        SDL_Renderer *renderer;
        bool fullscreen;
        uint32_t height, width;
};

typedef boost::shared_ptr<SDLView> SDLViewPtr;
