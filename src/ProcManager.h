#include <vector>
#include <string>
#include "Methods.h"
#include <map>
#include "Event_System.h"
#include "MsgEvt.h"
#include "Process.h"

class ProcManager
{
    public:
        
        ProcManager();
        bool addProcess(ProcessPtr obj, std::string group);
        bool pauseProcess(std::string processName);
        void pauseAllProcesses();
        void pauseGroup(std::string groupName);
        bool detachProcess(std::string name);
        bool resumeGroup(std::string groupName);
        bool resumeProcess(std::string name);
        void resumeAllProcesses();
        void tick();
        
    private:
        
        typedef std::vector<ProcessPtr> ProcessList;
        typedef std::map<uint32_t, ProcessList> ProcessMap;
        typedef std::pair<uint32_t, ProcessList> ProcessEnt;
        typedef std::pair<ProcessMap::iterator, bool> ProcessRes;
        
        typedef std::map<uint32_t, bool> GroupMap;
        typedef std::pair<uint32_t, bool> GroupEnt;
        typedef std::pair<GroupMap::iterator, bool> GroupRes;

        ProcessMap processes;
        GroupMap groups;
        bool allPaused;
};
