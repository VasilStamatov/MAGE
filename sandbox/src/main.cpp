#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include <ecs/World.h>

namespace me = mage::ecs;

struct Timer
{
  using HRTimePoint =
      std::chrono::time_point<std::chrono::high_resolution_clock>;

  Timer() { m_start = HRTimePoint::clock::now(); }
  ~Timer()
  {
    HRTimePoint end = HRTimePoint::clock::now();
    std::chrono::duration<double> timeSpan =
        std::chrono::duration_cast<std::chrono::duration<double>>(end -
                                                                  m_start);

    std::cout << "Millis elapsed: " << timeSpan.count() * 1000 << "\n";
  }

  double GetElapsedMilli()
  {
    HRTimePoint end = HRTimePoint::clock::now();
    std::chrono::duration<double> timeSpan =
        std::chrono::duration_cast<std::chrono::duration<double>>(end -
                                                                  m_start);
    return timeSpan.count() * 1000;
  }

  HRTimePoint m_start;
};

struct Composite
{
  Composite(float _a, float _b, int _c, int _d, int _e)
      : a(_a)
      , b(_b)
      , c(_c)
      , d(_d)
      , e(_e)
  {
  }

  float a;
  float b;
  int c;
  int d;
  int e;
};

struct TestComponent : me::Component
{
  TestComponent(Composite _composite, Composite _composite2, float _a, float _b,
                int _c, int _d, int _e, int _f)
      : composite(std::move(_composite))
      , composite2(std::move(_composite2))
      , a(_a)
      , b(_b)
      , c(_c)
      , d(_d)
      , e(_e)
      , f(_f)
  {
  }

  Composite composite;
  Composite composite2;
  float a;
  float b;
  int c;
  int d;
  int e;
  int f;
};

class TestSystem : public me::System
{
public:
  TestSystem() { m_systemSignature.AddComponent<TestComponent>(); }

  void Tick(me::World& _world, float _deltaTime) override
  {
    for (auto&& entity : m_registeredEntities)
    {
      auto testComponent = _world.GetComponent<TestComponent>(entity);
      std::cout << entity.m_id
                << " says hi! TestComponent.a = " << testComponent.a
                << std::endl;
    }
  }
};

class TestWorld : public me::World
{
private:
  virtual void AddSystems() override
  {
    AddSystem(std::make_unique<TestSystem>());
  }
  virtual void AddEntitiesAndComponents() override
  {
    auto handle = CreateEntity();
    handle.AddComponent<TestComponent>(Composite(1.0f, 1.0f, 1, 1, 1),
                                       Composite(1.0f, 1.0f, 1, 1, 1), 1.0f,
                                       1.0f, 1, 1, 1, 1);
  }
};

double RunExample()
{
  Timer timer;
  std::unique_ptr<me::World> world = std::make_unique<TestWorld>();
  world->Initialize();

  for (size_t i = 0; i < 50; i++)
  {
    world->TickSystems(1.0f);
  }

  return timer.GetElapsedMilli();
}

int main(int argc, char const* argv[])
{
  double milliAccumulator = 0.0;
  size_t numIterations = 30;

  for (size_t i = 0; i < numIterations; i++)
  {
    milliAccumulator += RunExample();
  }

  std::cout << "Average time: " << milliAccumulator / numIterations
            << " milliseconds\n";

  return 0;
}