project(mage_math)

add_library(mage_math STATIC
  include/math/Vec.h
  
  src/Vec.cpp)

target_compile_features(mage_math PUBLIC cxx_std_17)
target_include_directories(mage_math PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)