#include "Logging.h"

Logging::Logging()
{
    file.open(getString(g_config, "logFile").c_str(), std::ios::app|std::ios::out);
}

Logging::~Logging()
{
    file.close();
}

void Logging::log(std::string msg)
{
    //static Logging inst;
    if(!file)
    {
        file.open(getString(g_config, "logFile").c_str());
        if(!file)
        {
            Event_System::getSingleton().queueEvent(EventPtr(new Evt_Quit()));
            cerr << "logging system is stupid!";
        }
    }

    std::ostringstream msg2;
    const boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
    boost::posix_time::time_facet*const f = new boost::posix_time::time_facet("%H:%M:%S: ");
    msg2.imbue(std::locale(msg2.getloc(),f));
    msg2 << now;

    /*boost::chrono::system_clock::time_point bTime = boost::chrono::system_clock::now();
    time_t tTime = boost::chrono::system_clock::to_time_t(bTime);
    char * timeStr;
    const char *timeStrN = ctime(&tTime);
    strncpy(timeStr, timeStrN, strlen(timeStrN)-1);*/

    file << msg2.str() << msg;
    std::endl(file);
}
