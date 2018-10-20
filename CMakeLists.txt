cmake_minimum_required(VERSION 3.7)
project(mage)

set(CMAKE_CXX_STANDARD 17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
# set(GLFW_VULKAN_STATIC ON CACHE BOOL "" FORCE)

add_subdirectory(contrib/catch)
add_subdirectory(contrib/glfw)
add_subdirectory(mage/ecs)
add_subdirectory(mage/graphics)
add_subdirectory(sandbox)
add_subdirectory(tests)