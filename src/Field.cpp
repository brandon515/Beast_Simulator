#include "Field.h"

Field::Field(uint32_t width, uint32_t height, int prime1, int prime2, int prime3):
    IScreenElement(0,0),
    m_height(height),
    m_width(width),
    m_prime1(prime1),
    m_prime2(prime2),
    m_prime3(prime3)
{}

bool Field::setup()
{
    /*SDL_Surface *grass = loadImage(getString(g_config, "grassImage"));
    if(grass == NULL)
        Logging().log("grass not done");
    SDL_Surface *water = loadImage(getString(g_config, "waterImage"));*/
    sprite = SDL_CreateRGBSurface(SDL_SWSURFACE, m_width, m_height, 32, 0xff0000, 0x00ff00, 0x0000ff, 0);
    /*SDL_Rect curPos;
    for(curPos.x = 0; curPos.x < m_width; curPos.x+=grass->w)
    {
        for(curPos.y = 0; curPos.y < m_height; curPos.y+=grass->h)
        {
            if(perlinNoise(curPos.x, curPos.y, m_prime1, m_prime2, m_prime3, 1,0,0)+1*100 > 100)
            {
                SDL_BlitSurface(grass, NULL, sprite, &curPos);
                Logging().log("grass");
            }
            else
            {
                SDL_BlitSurface(water, NULL, sprite, &curPos);
                Logging().log("water");
            }
        }
    }*/
    SDL_Surface *grass = loadImage(getString(g_config,"grassImage"));
    if(!grass)
        return false;
    SDL_Surface *water = loadImage(getString(g_config,"waterImage"));
    if(!water)
        return false;
    SDL_Rect pos = {0,0,0,0};
    for(int y = 0; y <= m_height;  y++)
    {
        for(int x = 0; x <= m_width; x++)
        {
            int deter = (perlinNoise(x,y,m_prime1,m_prime2,m_prime3,25,0,0)*128+128);
            if(deter > 100)
            {
                SDL_BlitSurface(grass, NULL, sprite, &pos);
            }
            else
            {
                SDL_BlitSurface(water, NULL, sprite, &pos);
            }
            pos.x+=grass->w;
        }
        pos.y+=grass->h;

        pos.x=0;
    }
    SDL_FreeSurface(grass);
    SDL_FreeSurface(water);
    return true;
}
