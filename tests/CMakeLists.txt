project(tests)

add_executable(tests
  ecs/ComponentManagerTests.cpp
  ecs/ComponentMaskTests.cpp
  ecs/ComponentTests.cpp
  ecs/EntityManagerTests.cpp
  ecs/SystemTests.cpp

  math/VecTests.cpp

  src/testsMain.cpp)

target_link_libraries(tests PRIVATE catch)
target_link_libraries(tests PRIVATE mage_ecs)
target_link_libraries(tests PRIVATE mage_math)
