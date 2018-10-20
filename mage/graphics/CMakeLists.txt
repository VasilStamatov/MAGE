project(graphics)

add_library(graphics STATIC
  include/graphics/Video.h
  include/graphics/VideoHints.h
  include/graphics/Window.h

  src/Video.cpp
  src/VideoHints.cpp
  src/Window.cpp)


# find_package(Vulkan REQUIRED)
# target_link_libraries(graphics PRIVATE Vulkan::Vulkan)
target_link_libraries(graphics PUBLIC glfw)

target_include_directories(graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)