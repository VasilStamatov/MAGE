project(ecs)

add_library(ecs STATIC
    include/ecs/Entity.h
    src/Entity.cpp)

    target_include_directories(ecs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)