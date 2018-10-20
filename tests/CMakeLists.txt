project(tests)

add_executable(tests
  ecs/ComponentManagerTests.cpp
  ecs/ComponentMaskTests.cpp
  ecs/ComponentTests.cpp
  ecs/EntityManagerTests.cpp
  ecs/SystemTests.cpp
  src/testsMain.cpp)

target_link_libraries(tests PRIVATE catch)
target_link_libraries(tests PRIVATE ecs)