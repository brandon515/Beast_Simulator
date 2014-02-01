#include "PyProcess.h"

void PyProcess::tick()
{
    
}

PyProcess::PyProcess(std::string name):
    Process(name),
    module(name)
{}

void PyProcess::init()
{
    
}
