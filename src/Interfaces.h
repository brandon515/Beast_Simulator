#ifndef INTERFACES_H_INCLUDED
#define INTERFACES_H_INCLUDED
#include "IEventListener.h"
#include "IGameObject.h"
#include "IScreenElement.h"
#include "IWorldSubscriber.h"
#include "IGameView.h"
#include "IMovableElement.h"

namespace name
{
    extern const std::string IScreenElement;
    extern const std::string IEventListener;
    extern const std::string IWorldSubscriber;
    extern const std::string IGameView;
    extern const std::string IMovableElement;
}

namespace hashNumber
{
    extern const uint32_t IScreenElement;
    extern const uint32_t IEventListener;
    extern const uint32_t IWorldSubscriber;
    extern const uint32_t IGameView;
    extern const uint32_t IMovableElement;
}

#endif // INTERFACES_H_INCLUDED
