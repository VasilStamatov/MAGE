project(sandbox)

add_executable(sandbox 
  src/SandboxApplication.h
  src/SandboxComponents.h
  src/SandboxSystems.h
  src/SandboxWorld.h

  src/main.cpp
)

target_include_directories(sandbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(sandbox PRIVATE mage)
