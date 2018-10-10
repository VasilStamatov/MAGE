project(tests)

add_executable(tests src/testsMain.cpp)

target_link_libraries(tests PRIVATE catch)