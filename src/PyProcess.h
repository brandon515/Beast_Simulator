#include "Process.h"
#include <Python.h>
#include <string>

class PyProcess : public Process
{
    public:
        PyProcess(std::string name);
        void tick();
        void init();
    private:
        std::string module;
        PyObject *func;
};
