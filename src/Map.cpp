#include "Map.h"

Map::Map()
{
    //
}

void Map::init()
{
    bufMap = loadImage("images/testMap.png");
    const SDL_VideoInfo *info = SDL_GetVideoInfo();
    screenH = info->current_h;
    screenW = info->current_w;
}

Map::~Map()
{
    //dtor
}

Town Map::readData(void *data, SDL_Rect dataOffset)
{
    uint32_t *byte4DataP = (uint32_t*)data;
    uint32_t byte4Data[64], cur = 0;
    for(int y = 0; y < 8; y++)
    {
        for(int x = 0; x < 8; x++)
        {
            byte4Data[cur] = byte4DataP[(dataOffset.y+y)*screenW+(dataOffset.x+x)];
            cur++;
        }
    }
    Town *temp = (Town*)&byte4Data;
    return (*temp);
}

bool Map::loadMap(std::string filename)
{
    std::size_t pos = filename.find(".png");
    std::string bufFile, dataFile;
    if(pos == std::string::npos)
    {
        bufFile = filename + ".png";
        dataFile = filename + "_data.png";
    }
    else
    {
        std::string filename1, filename2;
        filename1 = filename.substr(0, pos);
        filename2 = filename.substr(pos);
        bufFile = filename;
        dataFile = filename1 + "_data" + filename2;
    }
    bufMap = loadImage(bufFile);
    dataMap = loadImage(dataFile);
    SDL_LockSurface(dataMap);
    uint32_t *place = (uint32_t*)dataMap->pixels;
    uint32_t num = place[0];
    if(townArray)
        delete townArray;
    townArray = new Town[num];
    for(uint32_t i = 1; i <= num; i++)
    {
        uint32_t curCo = place[i];
        SDL_Rect dOff;
        dOff.x = curCo&0xFFFF0000;
        dOff.y = curCo&0x0000FFFF;
        townArray[i-1] = readData(dataMap->pixels, dOff);
    }
    SDL_UnlockSurface(dataMap);
    return false;
}

void Map::addVecX(Sint16 x)
{
    vec.x += x;
}

void Map::addVecY(Sint16 y)
{
    vec.y += y;
}

void Map::update()
{
    if(((offset.x+vec.x) + bufMap->w >= screenW) && ((offset.x+vec.x) <= 0))
    {
        offset.x += vec.x;
    }
    if(((offset.y+vec.y) + bufMap->h >= screenH) && ((offset.y+vec.y) <= 0))
    {
        offset.y += vec.y;
    }
}

void Map::render()
{
    SDL_Rect temp;
    temp.x = offset.x;
    temp.y = offset.y;
    SDL_BlitSurface(bufMap, NULL, SDL_GetVideoSurface(), &temp);
}
