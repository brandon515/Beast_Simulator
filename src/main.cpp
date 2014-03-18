#include "main.h"

int main(int argc, char *argv[])
{   
    DebugOutputPtr out(new DebugOutput());
    if(!Event_System::getSingleton().addListener(out, MsgEvt().getType()))
    {
        std::cerr << "Could not add debug\n";
        return 1;
    }
    Event_System::getSingleton().addListener(out, EventType(wildCardType));

    ProcManager proc;
    DataModelPtr model(new DataModel("main"));
    if(!model->loadFile("def/InPt"))
    {
        std::cerr << "Could not load insertion point";
    }
    SDLViewPtr view(new SDLView());
    model->addView(view);
    if(!proc.addProcess(model, "DataModel"))
    {
        std::cerr << "DataModel can not be added";
        return 1;
    }
    SDLInjectorPtr con(new SDLInjector());
    if(!proc.addProcess(con, "Controllers"))
    {
        std::cerr << "Controller can not be added";
        return 1;
    }
    DataControllerPtr dat(new DataController(model));
    if(!Event_System::getSingleton().addListener(dat, Evt_CloseWindow().getType()) ||
    !Event_System::getSingleton().addListener(dat, Evt_WindowFocus().getType()) ||
    !Event_System::getSingleton().addListener(dat, Evt_Keyboard().getType()) ||
    !Event_System::getSingleton().addListener(dat, Evt_JoystickButton().getType()) ||
    !Event_System::getSingleton().addListener(dat, Evt_JoystickAxis().getType()))
    {
        std::cerr << "DataController could not be added to event_system";
    }

    ApplicationControllerPtr app(new ApplicationController(model));
    Event_System::getSingleton().addListener(app, Evt_CloseApplication().getType());

    DataPacketPtr settings(new DataPacket("", "def/settings", ""));

    float fps = settings->getInt("fps");

    EventParser::parseEvent("move creature 2 3");

    while(!app->shutdown())
    {
        clock_t begTick = clock();
        proc.tick();
        Event_System::getSingleton().tick(infMill);
        clock_t difTick = clock() - begTick;
        while( (((float)difTick)/CLOCKS_PER_SEC) < 1.0f/fps)
            difTick = clock() - begTick;
    }
    return 0;
}
