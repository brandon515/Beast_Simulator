#include <vector>
#include <string>
#include "Methods.h"
#include <map>
#include <boost/shared_ptr.hpp>
#include "Event_System.h"


class ProcManager
{
    public:
        
        bool addProcess(ProcessPtr obj, std::string group = "NONE");
        bool pauseProcess(std::string name);
        bool pauseAllProcesses();
        bool pauseGroup(std::string groupName);
        bool detachProcess(std::string name);
        bool resumeGroup(std::string groupName);
        bool resumeProcess(std::string name);
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
