#include <vector>
#include <string>
#include "Methods.h"
#include <map>

class Process;
typedef boost::shared_ptr<Process> ProcessPtr;

class ProcManager
{
    public:
        bool addProcess(ProcessPtr obj, std::string group = "NONE");
        void pauseProcess(std::string name);
        void pauseAllProcesses();
        void pauseGroup(std::string groupName);
        void tick();
        static ProcManager & getSingleton();
        
    private:
        typedef std::vector<ProcessPtr> ProcessList;
        typedef std::map<uint32_t, ProcessList> ProcessMap;
        typedef std::pair<uint32_t, ProcessList> ProcessEnt;
        typedef std::pair<bool, ProcessMap::iterator> ProcessRes;
        
        ProcessMap processes;

        ProcManager(){}
        ProcManager(ProcManager const &);
        bool operator=(ProcManager const &);
};


class Process
{
    public:
        explicit Process(std::string sName){name = CRC32(sName);}
        virtual void tick();
        uint32_t name;
};
