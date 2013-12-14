#ifndef VIEWSYSTEM_H_INCLUDED
#define VIEWSYSTEM_H_INCLUDED
#include "IGameView.h"
#include "Logging.h"
#include "Interfaces.h"
#include <vector>

class ViewSystem
{
    public:

        static ViewSystem & getSingleton();
        void tick();
        void init();
        bool addView(IGameViewPtr obj);
        bool delView(IGameViewPtr obj);
        bool isEmpty();

    private:

        //singleton methods

        ViewSystem(){}
        ViewSystem(ViewSystem const &);
        bool operator=(ViewSystem const &);

        //typedefs

        typedef std::vector<IGameViewPtr> IGameViewList;

        //member

        IGameViewList gameViews;
};

#endif // VIEWSYSTEM_H_INCLUDED
