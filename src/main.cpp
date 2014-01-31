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
    if(!proc.addProcess(model, "DataModel"))
    {
        std::cerr << "DataModel can not be added";
        return 1;
    }
    SDLControllerPtr con(new SDLController());
    if(!proc.addProcess(con, "Controllers"))
    {
        std::cerr << "Controller can not be added";
        return 1;
    }
    ApplicationControllerPtr app(new ApplicationController());
    Event_System::getSingleton().addListener(app, Evt_CloseApplication().getType());
    while(!app->shutdown())
    {
        proc.tick();
        Event_System::getSingleton().tick(infMill);
    }
    return 0;
}
