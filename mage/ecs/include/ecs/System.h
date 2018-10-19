#pragma once

#include "ComponentMask.h"
#include "Entity.h"

#include <vector>

namespace mage
{
namespace ecs
{

class World;

class System
{
public:
  System();
  virtual ~System();

  virtual void Initialize() {}
  virtual void Uninitialize() {}
  virtual void Tick(World& _world, float _deltaTime) = 0;

  void OnEntityComponentMaskChange(Entity _entity, ComponentMask _newMask);

protected:
  std::vector<Entity> m_registeredEntities;
  ComponentMask m_systemSignature;
};

} // namespace ecs
} // namespace mage