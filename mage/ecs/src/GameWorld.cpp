#include "ecs/GameWorld.h"

namespace mage
{
namespace ecs
{

// ------------------------------------------------------------------------------

GameWorld::GameWorld(core::World& _ownerWorld)
    : m_gameSystems()
    , m_ownerWorld(_ownerWorld)
{
}

// ------------------------------------------------------------------------------

GameWorld::~GameWorld() {}

// ------------------------------------------------------------------------------

void GameWorld::Initialize()
{
  for (auto&& gameSystem : m_gameSystems)
  {
    gameSystem->Initialize(m_ownerWorld);
  }
}

// ------------------------------------------------------------------------------

void GameWorld::Uninitialize()
{
  for (auto&& gameSystem : m_gameSystems)
  {
    gameSystem->Uninitialize(m_ownerWorld);
  }
}

// ------------------------------------------------------------------------------

void GameWorld::Tick(float _deltaSeconds)
{
  for (auto&& gameSystem : m_gameSystems)
  {
    gameSystem->Tick(m_ownerWorld, _deltaSeconds);
  }
}

// ------------------------------------------------------------------------------

void GameWorld::UpdateEntityStatus(ecs::Entity& _entity,
                                   ecs::ComponentMask _entitySignature)
{
  for (auto&& gameSystem : m_gameSystems)
  {
    gameSystem->OnEntityComponentMaskChange(_entity, _entitySignature);
  }
}

// ------------------------------------------------------------------------------

void GameWorld::AddGameSystem(std::unique_ptr<GameSystem> _system)
{
  m_gameSystems.emplace_back(std::move(_system));
}

// ------------------------------------------------------------------------------

} // namespace ecs
} // namespace mage