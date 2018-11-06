#pragma once

#include <functional>
#include <map>
#include <typeindex>
#include <vector>

namespace mage
{
namespace messaging
{

using Callback = std::function<void(void* _ptrToEventData)>;

class MessageBus
{
public:
  template <typename EventType> void Broadcast(EventType* _event)
  {
    std::type_index key = typeid(EventType);

    auto foundIt = m_subscribers.find(key);

    if (foundIt != m_subscribers.end())
    {
      for (auto&& callback : foundIt->second)
      {
        callback(_event);
      }
    }
  }

  template <typename T, typename EventType>
  void Subscribe(T* _instance, void (T::*_memberFunc)(EventType*))
  {
    std::type_index key = typeid(EventType);
    m_subscribers[key].push_back([=](void* _event) {
      (_instance->*_memberFunc)(static_cast<EventType*>(_event));
    });
  }

private:
  // [Key = Id of Event type][value = vector of subscribed callbacks]
  std::map<std::type_index, std::vector<Callback>> m_subscribers;
};

} // namespace messaging
} // namespace mage