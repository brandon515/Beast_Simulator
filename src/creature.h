#ifndef CREATURE_H
#define CREATURE_H
#include <SDL/SDL.h>
#include <iostream>
#include <list>
#include <cmath>
#include "Methods.h"
Uint16 getUID();
static const Uint8 male = 0;
static const Uint8 female = 1;
namespace actions
{
    static const Uint16 eat = 1;
    static const Uint16 strike = 2;
    static const Uint16 mate = 3;
}
namespace types
{
    static const Uint16 herb = 1;
    static const Uint16 carn = 2;
    static const Uint16 plant = 3;
}
struct geneticInfo
{
    Uint32 maxHealth, speed, damage;
};
struct msg
{
    Uint16 sender;
    Uint16 content;
};
class Creature
{
    public:
        Creature(std::list<Creature>, Uint16 _type, Uint16 _x, Uint16 _y);
        void handleMsg(msg);
        void update();
        geneticInfo genes;
		Uint8 sex, hunger;
        Uint16 uid;
        Uint32 health;
    private:
        Creature getFromList(Uint16 id);
        Uint16 type;
        std::list<Creature> sight;
        SDL_Surface *tile;
        SDL_Rect place;
};

#endif // CREATURE_H
