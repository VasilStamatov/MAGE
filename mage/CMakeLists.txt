project(mage)

if (MSVC)
  # warning level 4 and all warnings as errors
  add_compile_options(/W4 /C)
else()
  # lots of warnings and all warnings as errors
  add_compile_options(-Wall -C)
endif()

add_definitions( -DGLEW_STATIC )

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
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/audio/include
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/core/include
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ecs/include
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ecs_common/include
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/exceptions/include
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/filesystem/include
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/graphics/include
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/input/include
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/math/include
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/messaging/include
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/renderer/include
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/video/include
)

# Find dependencies
find_package(OpenGL REQUIRED)
include(${CMAKE_SCRIPTS_DIR}/FindGLEW.cmake)
include(${CMAKE_SCRIPTS_DIR}/FindGLFW.cmake)
include(${CMAKE_SCRIPTS_DIR}/FindSTB.cmake)
include(${CMAKE_SCRIPTS_DIR}/FindTinyObj.cmake)
include(${CMAKE_SCRIPTS_DIR}/FindOpenAL-Soft.cmake)
include(${CMAKE_SCRIPTS_DIR}/FindOgg.cmake)
include(${CMAKE_SCRIPTS_DIR}/FindVorbis.cmake)

# Include dependencies headers
target_include_directories(mage
  PRIVATE ${OPENGL_INCLUDE_DIRS}
  PRIVATE ${GLEW_INCLUDE_DIR}
  PRIVATE ${GLFW_INCLUDE_DIR}
  PRIVATE ${STB_INCLUDE_DIR}
  PRIVATE ${TINY_OBJ_LOADER_INCLUDE_DIR}
  PRIVATE ${OPENAL_SOFT_INCLUDE_DIR}
  PRIVATE ${OGG_INCLUDE_DIR}
  PRIVATE ${VORBIS_INCLUDE_DIR}
)

# Link dependency libraries to this target library
target_link_libraries(mage 
  PRIVATE ${OPENGL_LIBRARIES}
  PRIVATE ${GLEW_LIBRARIES}
  PRIVATE ${GLFW_LIBRARIES}
  PRIVATE ${OPENAL_SOFT_LIBRARIES}
  PRIVATE ${OGG_LIBRARIES}
  PRIVATE ${VORBIS_LIBRARIES}
)