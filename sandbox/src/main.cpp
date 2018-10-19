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

double RunExample()
{
  Timer timer;
  me::World world;
  me::EntityHandle handle = world.CreateEntity();

  for (size_t i = 0; i < 1; i++)
  {
    handle.AddComponent<TestComponent>(Composite(1.0f, 1.0f, 1, 1, 1),
                                       Composite(1.0f, 1.0f, 1, 1, 1), 1.0f,
                                       1.0f, 1, 1, 1, 1);
    handle.RemoveComponent<TestComponent>();
  }

  return timer.GetElapsedMilli();
}

int main(int argc, char const* argv[])
{
  double avg_time = 0.0;
  size_t num_iterations = 1;

  for (size_t i = 0; i < num_iterations; i++)
  {
    avg_time += RunExample();
  }

  std::cout << "Average time: " << avg_time / num_iterations
            << " milliseconds\n";

  return 0;
}