#include "PyProcess.h"

void PyProcess::tick()
{
    PyObject_CallMethodObjArgs(pyClass, pyTick, NULL);
}

PyProcess::PyProcess(std::string name, PyObject *pClass):
    Process(name),
    pyClass(pClass)
{
    Py_INCREF(pClass);
}

PyProcess::~PyProcess()
{
    Py_DECREF(pyClass);
}

bool PyProcess::init()
{
    PyObject *retVal;
    char *initStr = new char[4];
    strcpy(initStr, "init");
    retVal = PyObject_CallMethod(pyClass, initStr, NULL);
    if(!PyBool_Check(retVal))
    {
        Event_System::getSingleton().queueEvent(EventPtr(new MsgEvt("PyProcess with the name " + getStrName() + " did not return correct init value(bool)" )));
        return false;
    }
    if(PyObject_Not(retVal))
    {
        return false;
    }
    pyTick = PyString_FromString("tick");
    Py_DECREF(retVal);
    return true;    
}
