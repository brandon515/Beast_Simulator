#include "Event_System.h"
#include "Process.h"

class KeyboardInjector : public Process
{
    public:
        KeyboardInjector(std::string name);
        ~KeyboardInjector();
        virtual void tick()=0;
        virtual uint32_t getKey()=0;
};
