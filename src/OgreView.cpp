#include "OgreView.h"

void OgreListener::messageLogged(const Ogre::String &message, Ogre::LogMessageLevel lml, bool maskDebug, const Ogre::String &logName, bool &skipThisMessage)
{
    Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt(logName, message)));
}

OgreView::OgreView():
    View(1)
{}

OgreView::~OgreView()
{
    delete root;
}

bool OgreView::add(DataPacketPtr data)
{
    return true;
}

void OgreView::preFrame()
{
    
}

void OgreView::onFrame(DataPacketPtr data)
{
    
}

void OgreView::postFrame()
{
    root->renderOneFrame();
    window->update();
}

void OgreView::remove(std::string name)
{
    
}

bool OgreView::init()
{
    //logManager
    Ogre::LogManager *logMgr = new Ogre::LogManager();
    logMgr->createLog("Ogre System", true, false, true);
    logMgr->setLogDetail(Ogre::LL_NORMAL); 
    logMgr->getDefaultLog()->addListener(new OgreListener());
    //root
    root = new Ogre::Root("", "res.cfg");
    root->loadPlugin("RenderSystem_GL");
    root->loadPlugin("Plugin_OctreeSceneManager");
    Ogre::RenderSystemList renList = root->getAvailableRenderers();
    for(Ogre::RenderSystemList::iterator it = renList.begin(); it != renList.end(); it++)
    {
        Ogre::RenderSystem *ra = *(it);
        if(ra->getName().find("OpenGL") != std::string::npos)
        {
            root->setRenderSystem(ra);
            Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("Ogre View", ra->getName() + " loaded")));
            break;
        }
    }
    if(root->getRenderSystem() == NULL)
    {
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("Ogre View", "OpenGL was not able to load")));
        return false;
    }
    root->initialise(false);
    //window
    window = root->createRenderWindow(
        "Fighting Game",
        1024,
        576,
        false,
        0);
    //scene manager
    scene = root->createSceneManager(Ogre::ST_GENERIC, "Scene Manager");
    //camera
    camera = scene->createCamera("Main Camera");
    camera->setAspectRatio(1024.0f/576.0f);
    camera->setNearClipDistance(5.0f);
    camera->setFarClipDistance(1000.0f);
    //viewport
    bottom = window->addViewport(camera, 0);
    //resource creation
    Ogre::ResourceGroupManager &resGrp = Ogre::ResourceGroupManager::getSingleton();
    resGrp.addResourceLocation("./objects", "FileSystem", "meshes", true);
    resGrp.initialiseAllResourceGroups();
    //testing
    Ogre::Light *l = scene->createLight("mainLight");
    l->setPosition(20,80,50);
    Ogre::Entity *IM = scene->createEntity("IronMan", "IronMan/IronMan.mesh");
    Ogre::SceneNode *IMScene = scene->getRootSceneNode()->createChildSceneNode();
    IMScene->attachObject(IM);
    camera->setPosition(0,500,0);
    camera->lookAt(Ogre::Vector3(0,0,0));
    return true;
}
