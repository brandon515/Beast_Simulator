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
#include <time.h>

typedef struct _AnimationData
{
    SDL_Texture *texture;
    uint32_t maxFrames, fps;
    SDL_Rect area, screenArea;
} AnimationData;

class Texture
{
    public:
        Texture(DataPacketPtr data, SDL_Renderer *render);
        void render(SDL_Renderer *render, int x, int y);
        bool setState(std::string pState);
    private:
        typedef std::map<uint32_t, AnimationData> TextureMap;
        typedef std::pair<uint32_t, AnimationData> TextureEnt;
        typedef std::pair<TextureMap::iterator, bool> TextureRes;

        std::string state;
        TextureMap textures;
        AnimationData curTexture;
        bool animated, lookingRight;
        uint32_t curFrame;
        clock_t lastRenderTime;
};
    

class SDLView : public View
{
    public:
        SDLView();
        ~SDLView();
        bool init();
        bool add(DataPacketPtr data);
        void remove(std::string name);
        void preFrame();
        void onFrame(DataPacketPtr data);
        void postFrame();
    private:
        //typedefs

        typedef std::map<uint32_t, Texture*> TextureMap;
        typedef std::pair<uint32_t, Texture*> TextureEnt;
        typedef std::pair<TextureMap::iterator, bool> TextureRes;

        //private functions

        TextureMap textures;
        SDL_Window *window;
        SDL_Renderer *renderer;
        bool fullscreen;
        uint32_t height, width;
};

typedef boost::shared_ptr<SDLView> SDLViewPtr;
