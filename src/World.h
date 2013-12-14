#ifndef WORLD_H
#define WORLD_H
#include"IScreenElement.h"
#include "IMovableElement.h"
#include <vector>


class World
{
    public:
        ~World();
        static World & getSingleton();
        std::vector<IScreenElementPtr>* GetScreenList() { return &screenPtrList; }
        std::vector<IMovableElementPtr>* GetMoveList() { return &movablePtrList; }
        void addScreenPtr(IScreenElementPtr ptr){screenPtrList.push_back(ptr);}
        void addMovePtr(IMovableElementPtr ptr){movablePtrList.push_back(ptr);}
    private:
        World(){}
        World(const World& other);
        World& operator=(const World& other);
        std::vector<IScreenElementPtr> screenPtrList; //!< Member variable "screenPtrLis"
        std::vector<IMovableElementPtr> movablePtrList; //!< Member variable "movablePtrList"
};

#endif // WORLD_H
