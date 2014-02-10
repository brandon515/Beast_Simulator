#include "Process.h"
#include "Event_System.h"
#include "MsgEvt.h"
#include <Python.h>
#include <string>

class PyProcess : public Process
{
    public:
        PyProcess(std::string name, PyObject *pClass);
        ~PyProcess();
        void tick();
        bool init();
    private:
        PyObject *pyTick, *pyClass;
};
