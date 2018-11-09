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

if (WIN32)
  string(REPLACE "/" "\\" source_path_windows "${mage_SOURCE_DIR}/res")
  string(REPLACE "/" "\\" build_path_windows "${mage_BINARY_DIR}/res")
  execute_process(COMMAND cmd.exe /c mklink /J "${build_path_windows}" "${source_path_windows}" RESULT_VARIABLE exitcode)
else()
  execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${mage_SOURCE_DIR}/res ${mage_BINARY_DIR}/res RESULT_VARIABLE exitcode)
endif()

if (NOT ${exitcode} EQUAL 0)
  MESSAGE("SYMLINKING FAILED: ${exitcode}")
  MESSAGE("FALLING BACK TO COPYING")
endif()

#Copy file if the build resource folder contains an older version. This is ignored when the symlink was succesful because the files are already the newest version.
file(GLOB_RECURSE RES RELATIVE ${mage_SOURCE_DIR}/res/ ${mage_BINARY_DIR}/res/*.*)
foreach(file IN LISTS RES)
  configure_file(${mage_SOURCE_DIR}/res/${file} ${mage_BINARY_DIR}/res/${file} COPYONLY)
endforeach()

add_subdirectory(mage)
add_subdirectory(sandbox)
add_subdirectory(tests)