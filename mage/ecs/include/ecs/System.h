#pragma once

#include "ComponentMask.h"
#include "Entity.h"

#include <vector>

namespace mage
{
namespace ecs
{

// ------------------------------------------------------------------------------

class World;

// ------------------------------------------------------------------------------

/////////////////////////////////////////////////
/// The system is a process which is called to update all entities which have
/// the components this system cares about (using its signature)
/////////////////////////////////////////////////
class System
{
public:
  System();
  virtual ~System();

  // ------------------------------------------------------------------------------

  virtual void Initialize(World& _world) {}
  virtual void Uninitialize(World& _world) {}

  // ------------------------------------------------------------------------------

  /////////////////////////////////////////////////
  /// This function is called whenever the state of an entity changes, and
  /// either removes it from the system, if it no longer matches the signature,
  /// or adds it it matches the signature and isn't already registered.
  /////////////////////////////////////////////////
  void OnEntityComponentMaskChange(Entity _entity, ComponentMask _newMask);

  // ------------------------------------------------------------------------------

protected:
  std::vector<Entity> m_registeredEntities; ///< all entities whose entity mask
                                            ///< matches the system signature.
  ComponentMask m_systemSignature; ///< the system signature describes which
                                   ///< components this system operates on.
};

// ------------------------------------------------------------------------------

} // namespace ecs
} // namespace mage