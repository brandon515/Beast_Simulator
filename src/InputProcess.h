#include "Process.h"
#include <map>
#include "Methods.h"
#include "EventParser.h"
#include <boost/shared_ptr.hpp>

class InputProcess : public Process
{
    public:
        InputProcess();
        ~InputProcess(){}
        bool init();
        void tick();
        bool registerState(std::string name, std::string eventStr);
        void setState(std::string name, bool state);
        bool getState(std::string name);
        void fireEvent(std::string eventStr);
    private:
        typedef std::map<uint32_t, std::string> KeyEventMap;
        typedef std::pair<uint32_t, std::string> KeyEventEnt;
        typedef std::pair<KeyEventMap::iterator, bool> KeyEventRes;

        typedef std::map<uint32_t, bool> KeyBoolMap;
        typedef std::pair<uint32_t, bool> KeyBoolEnt;
        typedef std::pair<KeyBoolMap::iterator, bool> KeyBoolRes;

        KeyEventMap events;
        KeyBoolMap states;
};
        
typedef boost::shared_ptr<InputProcess> InputProcessPtr;
