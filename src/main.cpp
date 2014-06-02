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
    if(!model->loadMenu("def/menu"))
    {
        std::cerr << "Could not load Menu file";
    }
    model->addView(SDLViewPtr(new SDLView()));
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
    !Event_System::getSingleton().addListener(dat, Evt_Menu().getType()))
    {
        std::cerr << "DataController could not be added to event_system";
    }

    ApplicationControllerPtr app(new ApplicationController(model));
    Event_System::getSingleton().addListener(app, Evt_CloseApplication().getType());

    InputControllerPtr input(new InputController());
    if(!Event_System::getSingleton().addListener(input, Evt_Keyboard().getType()) ||
    !Event_System::getSingleton().addListener(input, Evt_JoystickAxis().getType()) ||
    !Event_System::getSingleton().addListener(input, Evt_JoystickButton().getType()) ||
    !Event_System::getSingleton().addListener(input, Evt_Context().getType()) ||
    !proc.addProcess(input->getInputProcess(), "Input"))
    {
        std::cerr << "Input system not inserted correctly";
    }

    MovementViewPtr mover(new MovementView());

    MovementControllerPtr moveControl(new MovementController(mover));
    if(!Event_System::getSingleton().addListener(moveControl, Evt_Move().getType()))
    {
        std::cerr << "movement system not active";
    }
    model->addView(mover);

    DataPacketPtr settings(new DataPacket("", "def/settings", ""));

    float fps = settings->getInt("fps");

    while(!app->shutdown())
    {
        clock_t begTick = clock();
        Event_System::getSingleton().queueEvent(EventPtr(new Evt_Move(3,0,"Fighter1")));
        proc.tick();
        Event_System::getSingleton().tick(infMill);
        clock_t difTick = clock() - begTick;
        while( (((float)difTick)/CLOCKS_PER_SEC) < 1.0f/fps)
            difTick = clock() - begTick;
    }
    return 0;
}
