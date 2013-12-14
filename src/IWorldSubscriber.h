#ifndef IWORLDSUBSCRIBER_H_INCLUDED
#define IWORLDSUBSCRIBER_H_INCLUDED
#include "IGameObject.h"
#include <map>

class IWorldSubscriber
{
    public:
        virtual ~IWorldSubscriber(){}
};

typedef boost::shared_ptr<IWorldSubscriber> IWorldSubscriberPtr;

#endif // IWORLDSUBSCRIBER_H_INCLUDED
