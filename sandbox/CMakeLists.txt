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

if (WIN32)
  string(REPLACE "/" "\\" source_path_windows "${CMAKE_SOURCE_DIR}/res")
  string(REPLACE "/" "\\" build_path_windows "${sandbox_BINARY_DIR}/res")
  execute_process(COMMAND cmd.exe /c mklink /J "${build_path_windows}" "${source_path_windows}" RESULT_VARIABLE exitcode)
  MESSAGE("Making link between ${build_path_windows} and ${source_path_windows}")
else()
  execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/res ${sandbox_BINARY_DIR}/res RESULT_VARIABLE exitcode)
endif()

if (NOT ${exitcode} EQUAL 0)
  MESSAGE("SYMLINKING FAILED: ${exitcode}")
  MESSAGE("FALLING BACK TO COPYING")
endif()

#Copy file if the build resource folder contains an older version. This is ignored when the symlink was succesful because the files are already the newest version.
file(GLOB_RECURSE RES RELATIVE ${CMAKE_SOURCE_DIR}/res/ ${CMAKE_SOURCE_DIR}/res/*.*)
foreach(file IN LISTS RES)
  configure_file(${CMAKE_SOURCE_DIR}/res/${file} ${sandbox_BINARY_DIR}/res/${file} COPYONLY)
endforeach()

