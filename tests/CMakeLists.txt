project(tests)

add_executable(tests
  ecs/ComponentManagerTests.cpp
  ecs/ComponentMaskTests.cpp
  ecs/ComponentTests.cpp
  ecs/EntityManagerTests.cpp
  ecs/SystemTests.cpp

  math/MatTests.cpp
  math/QuatTests.cpp
  math/VecTests.cpp

  src/testsMain.cpp
)

include(${CMAKE_SCRIPTS_DIR}/FindCatch.cmake)

target_include_directories(tests
  PRIVATE ${CATCH_INCLUDE_DIR}
)

target_link_libraries(tests PRIVATE mage)
