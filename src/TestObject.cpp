#include "TestObject.h"

TestObject::TestObject()
{
    //
}

TestObject::~TestObject()
{
    Logging().log("testObject destroyed");
}

void TestObject::update()
{
    //
}

void TestObject::render(SDL_Surface *screen)
{
    SDL_BlitSurface(sprite, NULL, screen, getPos());
}

void TestObject::init()
{
    setPos(0,0);
    TestObjectPtr testPtr(this);
    World::getSingleton().addMovePtr(testPtr);
    World::getSingleton().addScreenPtr(testPtr);
    sprite = loadImage("images\\test.png");
}
