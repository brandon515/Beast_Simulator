#include <math.h>
#include "Methods.h"
#include "Globals.h"
#include "Application.h"
#include <iostream>
#include <cassert>

int main(int argc, char *argv[])
{
    if(g_config.compare("nope.avi") == 0)
        return -1;
    Application app;
    app.go();
    /*if(SDL_Init(SDL_INIT_EVERYTHING)==-1 || TTF_Init() == -1)
        return 1;

    //load config file and values from the file

    std::string config = fileRead("config");
    static const int width = getNumber(config,"width"), height = getNumber(config,"height"), bit_rate = getNumber(config,"bit_rate"),
                     prime1 = getNumber(config,"prime1"), prime2 = getNumber(config,"prime2"), prime3 = getNumber(config,"prime3"),
                     fps = getNumber(config,"fps"), fieldWidth = getNumber(config, "fieldWidth"), fieldHeight = getNumber(config,"fieldHeight");
    SDL_Surface *screen= SDL_SetVideoMode(width, height, bit_rate, SDL_SWSURFACE);
    SDL_Surface *field = SDL_CreateRGBSurface(SDL_SWSURFACE, fieldWidth, fieldHeight, bit_rate, 0xff0000, 0x00ff00, 0x0000ff, NULL);
    SDL_WM_SetCaption(getString(config, "title").c_str(), NULL);
    SDL_Event event;

    // menu resources

    TTF_Font *title = TTF_OpenFont(getString(config,"font").c_str(), 80), *buttons = TTF_OpenFont(getString(config,"font").c_str(), 18);
    SDL_Surface *button_dormant = loadImage(getString(config, "butD"));
    SDL_Surface *button_used = loadImage(getString(config, "butU"));
    SDL_Rect pos = {0,0,0,0};
    SDL_Color white({255,255,255});
    SDL_Surface *newMap = TTF_RenderText_Solid( buttons, getString(config, "newText").c_str(), white );
    SDL_Surface *loadMap = TTF_RenderText_Solid( buttons, getString(config, "loadText").c_str(), white );
    SDL_Surface *titleText = TTF_RenderText_Solid( title, getString(config, "title").c_str(), white );
    SDL_Rect button1, button2, newMapLoc, loadMapLoc, titleLoc;
    button1.w = button2.w = button_dormant->w;
    button1.h = button2.h = button_dormant->h;
    button1.x = (width/2)-(button1.w/2);
    button2.x = (width/2)-(button2.w/2);
    //divide the screen into eigths and place it on the 5th and 7th line
    button1.y = (height*5/8)-(button1.h/2);
    button2.y = (height*7/8)-(button2.h/2);
    newMapLoc.x = button1.x+(button1.w/2-newMap->w/2);
    loadMapLoc.x = button2.x+(button2.w/2-loadMap->w/2);
    newMapLoc.y = button1.y+(button1.h/2-newMap->h/2);
    loadMapLoc.y = button2.y+(button2.h/2-loadMap->h/2);
    titleLoc.x = width/2-titleText->w/2;
    titleLoc.y = height*1/4-titleText->h/2;
    bool getOut = false, onButton1 = false, onButton2 = false, createNewMap = false, loadOldMap = false;

    //menu loop

    while(!getOut)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                return 0;
            if(event.type == SDL_MOUSEMOTION)
            {
                int x = event.motion.x;
                int y = event.motion.y;

                if((x > button1.x) && (x < button1.x+button1.w) && (y > button1.y) && (y < button1.y+button1.h))
                    onButton1 = true;
                else if((x > button2.x) && (x < button2.x+button2.w) && (y > button2.y) && (y < button2.y+button2.h))
                    onButton2 = true;
                else
                    onButton1 = onButton2 = false;
            }
            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x = event.button.x;
                int y = event.button.y;

                if((x > button1.x) && (x < button1.x+button1.w) && (y > button1.y) && (y < button1.y+button1.h))
                {
                    getOut = true;
                    createNewMap = true;
                }
                else if((x > button2.x) && (x < button2.x+button2.w) && (y > button2.y) && (y < button2.y+button2.h))
                {
                    getOut = true;
                    loadOldMap = true;
                }
            }
        }
        if(onButton1)
            SDL_BlitSurface(button_used, NULL, screen, &button1);
        else
            SDL_BlitSurface(button_dormant, NULL, screen, &button1);
        if(onButton2)
            SDL_BlitSurface(button_used, NULL, screen, &button2);
        else
            SDL_BlitSurface(button_dormant, NULL, screen, &button2);
        SDL_BlitSurface(newMap, NULL, screen, &newMapLoc);
        SDL_BlitSurface(loadMap, NULL, screen, &loadMapLoc);
        SDL_BlitSurface(titleText, NULL, screen, &titleLoc);
        SDL_Flip(screen);
    }

    // create new map

    if(createNewMap)
    {
        SDL_Surface *grass = loadImage(getString(config,"grassImage"));
        SDL_Surface *water = loadImage(getString(config,"waterImage"));
        for(int y = 0; y <= height;  y++)
        {
            for(int x = 0; x <= width; x++)
            {
                int deter = (perlinNoise(x,y,prime1,prime2,prime3,25,0,0)*128+128);
                if(deter > 100)
                {
                    SDL_BlitSurface(grass, NULL, field, &pos);
                }
                else
                {
                    SDL_BlitSurface(water, NULL, field, &pos);
                }
                pos.x+=20;
            }*128+128
            pos.y+=20;

            pos.x=0;
        }
        SDL_FreeSurface(grass);
        SDL_FreeSurface(water);
    }

    //load old map

    if(loadMap)
    {
        //LOAD MAP
    }

    //simulation resources

    std::list<Creature> animals;
    pos.x =0;
    pos.y =0;
    pos.w = width;
    pos.h = height;
    Uint8 *keyStates = SDL_GetKeyState(NULL);
    SDL_BlitSurface(field, &pos, screen, NULL);
    SDL_Flip(screen);
    getOut=false;
    while(!getOut)
    {
        clock_t start = clock();
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                getOut = true;
        }
        if(keyStates[SDLK_ESCAPE])
            getOut = true;
        if(keyStates[SDLK_RIGHT])
        {
            if(pos.x < (fieldWidth-width))
                pos.x+=2;
        }
        if(keyStates[SDLK_LEFT])
        {
            if(pos.x > 0)
                pos.x-=2;
        }
        if(keyStates[SDLK_UP])
        {
            if(pos.y > 0)
                pos.y-=2;
        }
        if(keyStates[SDLK_DOWN])
        {
            if(pos.y < (fieldHeight-height))
                pos.y+=2;
        }
        SDL_BlitSurface(field, &pos, screen, NULL);
        SDL_Flip(screen);
        SDL_PumpEvents();
        maintainFPS(fps,start);
    }
    SDL_FreeSurface(field);
    SDL_FreeSurface(screen);*/
    return 0;
}
