project(ecs)

add_library(ecs STATIC
    include/ecs/Component.h
    include/ecs/ComponentManager.h
    include/ecs/ComponentMask.h
    include/ecs/Entity.h
    include/ecs/EntityHandle.h
    include/ecs/EntityManager.h
    include/ecs/System.h
    include/ecs/SystemManager.h
    include/ecs/World.h

    src/Component.cpp
    src/ComponentManager.cpp
    src/ComponentMask.cpp
    src/Entity.cpp
    src/EntityHandle.cpp
    src/EntityManager.cpp
    src/System.cpp
    src/SystemManager.cpp
    src/World.cpp)

  target_include_directories(ecs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)