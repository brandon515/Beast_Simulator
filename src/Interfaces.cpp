#include "Interfaces.h"

const std::string name::IScreenElement = "IScreenElement";
const std::string name::IEventListener = "IEventListener";
const std::string name::IWorldSubscriber = "IWorldSubscriber";
const std::string name::IGameView = "IGameView";
const std::string name::IMovableElement = "IMovableElement";

const uint32_t hashNumber::IScreenElement = CRC32(name::IScreenElement.c_str(), name::IScreenElement.length());
const uint32_t hashNumber::IEventListener = CRC32(name::IEventListener.c_str(), name::IEventListener.length());
const uint32_t hashNumber::IWorldSubscriber = CRC32(name::IWorldSubscriber.c_str(), name::IWorldSubscriber.length());
const uint32_t hashNumber::IGameView = CRC32(name::IGameView.c_str(), name::IGameView.length());
const uint32_t hashNumber::IMovableElement = CRC32(name::IMovableElement.c_str(), name::IMovableElement.length());
