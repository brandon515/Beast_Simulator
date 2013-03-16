#ifndef LOGGING_H_INCLUDED
#define LOGGING_H_INCLUDED

class Logging
{
    public:
        static Logging & getSingleton();
    private:
        Logging(){}
        Logging(const &Logging){}
        void operator=(const &Logging){}
};

#endif // LOGGING_H_INCLUDED
