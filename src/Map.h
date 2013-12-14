#ifndef MAP_H
#define MAP_H
#include <SDL/SDL.h>
#include <iostream>
#include "Globals.h"
#include "Logging.h"

typedef struct _town
{
    uint32_t pop;
    float order;
    uint16_t foodRate;
    uint16_t goldRate;
    uint16_t techLevel;
    uint16_t defenseLevel;
    uint32_t character[35];
    char name[100];
} Town;

class Map
{
    public:
        Map();
        ~Map();
        void update();
        void render();
        void init();
        bool loadMap(std::string filename);
        void addVecX(Sint16 x);
        void addVecY(Sint16 y);
        SDL_Surface *getBufMap() { return bufMap; }
    private:
        SDL_Surface *bufMap, *dataMap;
        SDL_Rect offset, vec;
        Sint32 screenW, screenH;
        Town *townArray;
        Town readData(void *data, SDL_Rect dataOffset);
};

#endif // MAP_H
