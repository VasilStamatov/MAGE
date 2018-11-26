project(tests)

# LOAD the header files
file(GLOB_RECURSE HEADERS
  ${CMAKE_CURRENT_SOURCE_DIR}/*.h
  ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
)

# LOAD the source files
file(GLOB_RECURSE SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

add_executable(tests ${HEADERS} ${SOURCES})

include(${CMAKE_SCRIPTS_DIR}/FindCatch.cmake)

target_include_directories(tests
  PRIVATE ${CATCH_INCLUDE_DIR}
)

target_link_libraries(tests PRIVATE mage)
