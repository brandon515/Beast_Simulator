#include "Planet.h"
Planet::Planet(Sint16 x, Sint16 y, uint32_t radius, uint32_t color):
    IScreenElement(x, y)
{
    m_radius = radius;
    uint32_t diameter = (m_radius*2)+1;
    sprite = SDL_CreateRGBSurface(SDL_SWSURFACE, diameter, diameter, 32, 0xff0000, 0x00ff00, 0x0000ff, 0);
    uint32_t colorKey = 0;
    if(color != 0xff00ff)
        colorKey = SDL_MapRGB(sprite->format,0xFF,0,0xFF);
    else
        colorKey = SDL_MapRGB(sprite->format,0xFF,0,0xFd);
    SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, colorKey);
    SDL_LockSurface(sprite);
    uint32_t *pix = reinterpret_cast<uint32_t*>(sprite->pixels);
    for(int i = 0; i < sprite->w; i++)
    {
        for(int j = 0; j < sprite->h; j++)
        {
            pix[j*sprite->w+i] = colorKey;
        }
    }
    if(pix != NULL)
    {
        uint32_t x, y = 0;
        for(x = radius; x < diameter; x++)
        {
            double dx = x-radius;
            double rad = acos(dx/radius);
            y = radius-(sin(rad)*radius);

            uint32_t x2 = radius+(radius-x), y2 = radius+(radius-y);
            //comment here and
            for(uint32_t i = y; i<=y2; i++)
            {
                pix[i*diameter+x] = color;
                pix[i*diameter+x2] = color;
            }
            //uncomment here if you want unfilled for some odd reason
            /*pix[y*diameter+x] = color;
            pix[y2*diameter+x] = color;
            pix[y*diameter+x2] = color;
            pix[y2*diameter+x2] = color;*/
        }
        for(y = 0; y < radius; y++)
        {
            double dy = radius-y;
            double rad = acos(dy/radius);
            x = radius-(sin(rad)*radius);

            uint32_t x2 = radius+(radius-x), y2 = radius+(radius-y);
            //comment here and
            for(uint32_t i = x; i<=x2; i++)
            {
                pix[y*diameter+i] = color;
                pix[y2*diameter+i] = color;
            }
            //uncomment here if you want unfilled for some odd reason
            /*pix[y*diameter+x] = color;
            pix[y2*diameter+x] = color;
            pix[y*diameter+x2] = color;
            pix[y2*diameter+x2] = color;*/
        }
    }
    SDL_UnlockSurface(sprite);
    SDL_SaveBMP(sprite, "broman.bmp");
}
