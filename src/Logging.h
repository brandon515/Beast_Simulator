#ifndef LOGGING_H_INCLUDED
#define LOGGING_H_INCLUDED
#include <fstream>
#include <cassert>
#include "Globals.h"
#include "Methods.h"
#include "GameEvents.h"
#include "Event_System.h"
#include <boost\date_time.hpp>
#include <sstream>


class Logging
{
    public:
        void log(std::string msg);
        Logging();
        ~Logging();
    private:
        ofstream file;
};

#endif // LOGGING_H_INCLUDED
