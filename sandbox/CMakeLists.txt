project(sandbox)

add_executable(sandbox src/main.cpp)

target_link_libraries(sandbox PRIVATE mage_ecs)