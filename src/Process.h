#include <boost/shared_ptr.hpp>
#include "Methods.h"
#include <string>

class Process
{
    public:
        explicit Process(std::string sName){name = sName;kill=false;isPaused=false;}
        virtual void tick();
        std::string getStrName(){return name;}
        uint32_t getHashName(){return CRC32(name.c_str(), name.length());}
        bool doKill(){return kill;}
        bool isPaused;
    private:
        std::string name;
        bool kill;
};

typedef boost::shared_ptr<Process> ProcessPtr;
