#include <vector>
#include <string>
#include "Methods.h"
#include <map>
#include <boost/shared_ptr.hpp>
#include "Event_System.h"

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
        
    private:
        
        typedef std::vector<ProcessPtr> ProcessList;
        typedef std::map<uint32_t, ProcessList> ProcessMap;
        typedef std::pair<uint32_t, ProcessList> ProcessEnt;
        typedef std::pair<bool, ProcessMap::iterator> ProcessRes;
        
        typedef std::map<uint32_t, bool> GroupMap;
        typedef std::pair<uint32_t, bool> GroupEnt;
        typedef std::pair<bool, GroupMap::iterator> GroupRes;

        ProcessMap processes;
        GroupMap groups;
};


class Process
{
    public:
        explicit Process(std::string sName){name = CRC32(sName);}
        virtual void tick();
        uint32_t name;
};
