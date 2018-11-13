#include "demo/DemoApplication.h"

#include "demo/GameWorld.h"

void DemoApplication::AddGameWorlds()
{
  m_gameWorlds.push_back(std::make_unique<GameWorld>(m_applicationMessageBus));
}