cmake_minimum_required(VERSION 3.7)
project(mage)

if (MSVC)
  # warning level 4 and all warnings as errors
  add_compile_options(/W4 /WX)
else()
  # lots of warnings and all warnings as errors
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_subdirectory(contrib/catch)
add_subdirectory(contrib/glfw)
add_subdirectory(mage/ecs)
add_subdirectory(mage/graphics)
add_subdirectory(mage/math)
add_subdirectory(sandbox)
add_subdirectory(tests)