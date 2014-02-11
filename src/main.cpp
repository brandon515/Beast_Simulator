#include "main.h"

int main(int argc, char *argv[])
{   
    DebugOutputPtr out(new DebugOutput());
    if(!Event_System::getSingleton().addListener(out, MsgEvt().getType()))
    {
        std::cerr << "Could not add debug\n";
        return 1;
    }

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
    Event_System::getSingleton().addListener(dat, Evt_CloseWindow().getType());
    Event_System::getSingleton().addListener(dat, Evt_WindowFocus().getType());
    Event_System::getSingleton().addListener(dat, Evt_Keyboard().getType());

    ApplicationControllerPtr app(new ApplicationController(model));
    Event_System::getSingleton().addListener(app, Evt_CloseApplication().getType());

    while(!app->shutdown())
    {
        proc.tick();
        Event_System::getSingleton().tick(infMill);
    }
    return 0;
}
