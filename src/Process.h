#include <boost/shared_ptr.hpp>

class Process
{
    public:
        explicit Process(std::string sName){name = CRC32(sName);kill=false;isPaused=false;}
        virtual void tick();
        uint32_t name;
        bool doKill(){return kill;}
        bool isPaused;
    private:
        bool kill;
};

typedef boost::shared_ptr<Process> ProcessPtr;
