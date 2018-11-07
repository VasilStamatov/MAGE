project(mage)

if (MSVC)
  # warning level 4 and all warnings as errors
  add_compile_options(/W4 /C)
else()
  # lots of warnings and all warnings as errors
  add_compile_options(-Wall -C)
endif()

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

# Create the static library target with all the loaded files
add_library(mage STATIC ${HEADERS} ${SOURCES})

# Some parts of the engine require cpp 17 features
target_compile_features(mage PUBLIC cxx_std_17)

# Include the location of the header files
target_include_directories(mage 
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/core/include
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ecs/include
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/exceptions/include
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/input/include
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/math/include
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/messaging/include
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/video/include
)

# Find dependencies
include(${CMAKE_SCRIPTS_DIR}/FindVulkan.cmake)
include(${CMAKE_SCRIPTS_DIR}/FindGLFW.cmake)

# Include dependencies headers
target_include_directories(mage 
  PRIVATE ${VULKAN_INCLUDE_DIR}
  PRIVATE ${GLFW_INCLUDE_DIRS}
)

# Link dependency libraries to this target library
target_link_libraries(mage 
  PRIVATE ${VULKAN_LIBRARIES}
  PRIVATE ${GLFW_LIBRARIES}
)