cmake_minimum_required(VERSION 3.5)

project(mage)

# We need a CMAKE_DIR with some code to find external dependencies
set(CMAKE_SCRIPTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
  set(
    CMAKE_BUILD_TYPE 
      "Debug"
    CACHE STRING 
      "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) \"Debug\" \"Release\" \"RelWithDebInfo\" \"MinSizeRel\"."
    FORCE
  )
endif()

if ( CMAKE_BUILD_TYPE STREQUAL "Release" )
  add_definitions( -O2 )
  add_definitions( -NDEBUG )
endif ()

add_subdirectory(contrib)
add_subdirectory(mage)
add_subdirectory(sandbox)
add_subdirectory(tests)