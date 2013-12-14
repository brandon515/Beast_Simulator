#ifndef TESTOBJECT_H_INCLUDED
#define TESTOBJECT_H_INCLUDED
#include "Interfaces.h"
#include "Methods.h"
#include "World.h"
#include "Logging.h"

class TestObject : public IScreenElement, public IMovableElement
{
    public:
        TestObject();
        ~TestObject();
        void init();
        void render(SDL_Surface *screen);
        void update();
};

typedef boost::shared_ptr<TestObject> TestObjectPtr;

#endif // TESTOBJECT_H_INCLUDED
