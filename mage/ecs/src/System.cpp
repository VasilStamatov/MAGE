#include "ecs/System.h"

namespace mage
{
namespace ecs
{

// ------------------------------------------------------------------------------

System::System()
    : m_registeredEntities()
    , m_systemSignature()
{
}

// ------------------------------------------------------------------------------

System::~System() {}

// ------------------------------------------------------------------------------

void System::OnEntityComponentMaskChange(Entity _entity, ComponentMask _newMask)
{
  auto foundIt = std::find(m_registeredEntities.begin(),
                           m_registeredEntities.end(), _entity);

  if (_newMask.MatchesMask(m_systemSignature))
  {
    if (foundIt == m_registeredEntities.end())
    {
      m_registeredEntities.push_back(_entity);
    }
  }
  else
  {
    if (foundIt != m_registeredEntities.end())
    {
      m_registeredEntities.erase(foundIt);
    }
  }
}

// ------------------------------------------------------------------------------

} // namespace ecs
} // namespace mage