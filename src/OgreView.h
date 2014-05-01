#include "View.h"
#include <iostream>
#include "Event_System.h"
#include "MsgEvt.h"
#include <OGRE/Ogre.h>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

class OgreListener : public Ogre::LogListener
{
    public:
        void messageLogged(const Ogre::String &message, Ogre::LogMessageLevel lml, bool maskDebug, const Ogre::String &logName, bool &skipThisMessage);
};

class OgreView : public View
{
    public:
        OgreView();
        ~OgreView();
        bool add(DataPacketPtr data);
        void preFrame();
        void onFrame(DataPacketPtr data);
        void postFrame();
        void remove(std::string name);
        bool init();
    private:
        Ogre::Root *root;
        Ogre::RenderWindow *window;
        Ogre::SceneManager *scene;
        Ogre::Camera *camera;
        Ogre::Viewport *bottom;
};

typedef boost::shared_ptr<OgreView> OgreViewPtr;
