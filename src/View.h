class View
{
    public:
        View(std::string caption);
        virtual ~View();
        virtual bool add(std::string name);
        virtual bool render();
        virtual void remove(std::string name);
        virtual bool init();
};
