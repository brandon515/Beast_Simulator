#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED
#include <string>
#include "Methods.h"
#include "Event_System.h"
#include "SDL_EventManager.h"
#include "Logging.h"
#include "GameEvents.h"
#include "EventLogger.h"
#include "ViewSystem.h"
#include "HumanView.h"
#include "TestObject.h"
class Application
{
    public:
        Application();
        ~Application();
        void go();
    private:
        Logging m_log;
        //SDL_EventManager m_appLayerEvents;
        //EventLogger log;
        bool setup();
};

typedef boost::shared_ptr<Application> ApplicationPtr;

#endif // APPLICATION_H_INCLUDED
