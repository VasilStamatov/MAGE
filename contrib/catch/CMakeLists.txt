project(catch)

# Header only library, therefore INTERFACE
add_library(catch INTERFACE)

# INTERFACE targets only have INTERFACE properties
target_include_directories(catch INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# From Catch's CMake https://github.com/catchorg/Catch2/blob/master/CMakeLists.txt
target_compile_features(catch
  INTERFACE
    cxx_alignas
    cxx_alignof
    cxx_attributes
    cxx_auto_type
    cxx_constexpr
    cxx_defaulted_functions
    cxx_deleted_functions
    cxx_final
    cxx_lambdas
    cxx_noexcept
    cxx_override
    cxx_range_for
    cxx_rvalue_references
    cxx_static_assert
    cxx_strong_enums
    cxx_trailing_return_types
    cxx_unicode_literals
    cxx_user_literals
    cxx_variadic_macros
)