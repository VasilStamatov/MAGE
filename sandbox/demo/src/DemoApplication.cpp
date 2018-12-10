#include "demo/DemoApplication.h"

#include "demo/MainWorld.h"

void DemoApplication::AddGameWorlds()
{
  m_gameWorlds.push_back(std::make_unique<MainWorld>(*this));
}