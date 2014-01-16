#include <string>

class View
{
    public:
        virtual ~View(){}
        virtual bool add(std::string name)=0;
        virtual bool render()=0;
        virtual void remove(std::string name)=0;
        virtual bool init()=0;
};
