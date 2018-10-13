#pragma once

#include "ComponentMask.h"
#include "Entity.h"

#include <vector>

namespace mage
{
namespace ecs
{

class System
{
protected:
  std::vector<Entity> m_registeredEntities;
  ComponentMask m_systemSignature;

public:
  System();
  virtual ~System();

  virtual void Initialize() {}
  virtual void Uninitialize() {}

  void OnEntityComponentMaskChange(Entity _entity, ComponentMask _newMask);

  virtual void Tick(float _deltaTime) = 0;
};

} // namespace ecs
} // namespace mage