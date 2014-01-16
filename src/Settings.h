#include <fstream>

class Settings
{
    public:
        static Settings & getSingleton();
    private:
        Settings(){}
        Settings(Settings const &);
        bool operator=(Settings const &);
};
