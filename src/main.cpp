#include "main.h"

int main(int argc, char *argv[])
{
    ProcManager proc;
    DataModelPtr model(new DataModel("main"));
    if(!model->loadFile("def/InPt"))
    {
        std::cerr << "Could not load insertion point";
    }
    SDLViewPtr view(new SDLView());
    model->addView(view);
    proc.addProcess(model, "DataModel");
    ApplicationControllerPtr app;
    Event_System::getSingleton().addListener(app, Evt_CloseApplication().getType());
    while(!app->shutdown())
    {
        proc.tick();
        Event_System::getSingleton().tick();
    }
    return 0;
}
