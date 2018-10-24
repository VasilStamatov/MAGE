project(mage_math)

add_library(mage_math STATIC
  include/math/Mat.h
  include/math/MathUtils.h
  include/math/Quat.h
  include/math/Vec.h
  
  src/Mat.cpp
  src/MathUtils.cpp
  src/Quat.cpp
  src/Vec.cpp)

target_compile_features(mage_math PUBLIC cxx_std_17)
target_include_directories(mage_math PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)