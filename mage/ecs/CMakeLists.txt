project(ecs)

add_library(ecs STATIC
    include/ecs/Component.h
    include/ecs/ComponentMask.h
    include/ecs/Entity.h
    include/ecs/EntityManager.h

    src/Component.cpp
    src/ComponentMask.cpp
    src/Entity.cpp
    src/EntityManager.cpp)

    target_include_directories(ecs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)