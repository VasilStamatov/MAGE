#include <ecs/ComponentManager.h>
#include <ecs/Component.h>

namespace mage
{
namespace ecs
{

struct ExampleComponent : Component
{
    ExampleComponent(std::uint32_t _data)
        : m_data(_data)
    {
    }
    std::uint32_t m_data;
};

void ComponentManagerTestFunc()
{
    ComponentManager<ExampleComponent> testManager;
    Entity testEntity(0);

    testManager.AddComponent(testEntity, ExampleComponent(5));
    ExampleComponent *comp = testManager.GetComponent(testEntity);
    testManager.RemoveComponent(testEntity);
}

} // namespace ecs
} // namespace mage