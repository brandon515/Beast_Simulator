#include <string>

class View
{
    public:
        virtual ~View(){}
        virtual bool add(std::string name, std::string filename)=0;
        virtual void preFrame()=0;
        virtual void onFrame(std::string name, int x, int y)=0;
        virtual void postFrame()=0;
        virtual void remove(std::string name)=0;
        virtual bool init()=0;
};
