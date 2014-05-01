#include "InputController.h"

InputController::InputController()
{
    input = InputProcessPtr(new InputProcess());
    controls = getRoot("def/controls");
    Json::Value contexts = controls["contexts"];
    
}

bool InputController::handleEvent(Event const & event)
{
    if(event.getType() == Evt_Keyboard().getType())
    {
        
    }
    else if(event.getType() == Evt_Context().getType())
    {
        
    }
    return false;
}

InputProcessPtr InputController::getInputProcess()
{
    return input;
}

Json::Value InputController::getRoot(std::string filename)
{
    Json::Value root;
    Json::Reader reader;
    ifstream file;
    file.open(filename.c_str());
    if(!file.is_open())
    {
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("Input Controller", "file " + filename + " cannot be opened for Json parsing")));
        return Json::Value();
    }
    file.seekg(0, file.end);
    int len = file.tellg();
    file.seekg(0, file.beg);
    char *dat = new char[len];
    file.read(dat, len);
    std::string fileStr(dat);
    file.close();
    if(!reader.parse(fileStr, root))
    {
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("Input Controller", "JSON parser cannot parse the file: " + filename + "\n\treason:" + reader.getFormatedErrorMessages())));
        return Json::Value();
    }
    return root;
}
