cmake_minimum_required(VERSION 3.25)

project(wirepump VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options("-fdiagnostics-color=always")

# Dependencies
include(cmake/cista.cmake)
include(cmake/asio.cmake)

# The main library
add_library(wirepump INTERFACE)
target_compile_features(wirepump INTERFACE cxx_std_20)
set_property(TARGET wirepump PROPERTY CXX_STANDARD 20)
target_link_libraries(wirepump INTERFACE wirepump-cista)
target_include_directories(wirepump INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# The single-header bundle
add_subdirectory(bundler)
file(GLOB_RECURSE wirepump-include-files include/*.hpp)
add_custom_command(
  OUTPUT wirepump.hpp
  DEPENDS wirepump-bundler ${wirepump-include-files}
  COMMAND wirepump-bundler
    ${CMAKE_CURRENT_SOURCE_DIR}/include/wirepump.hpp
    wirepump=${CMAKE_CURRENT_SOURCE_DIR}/include/wirepump
    cista=${wirepump-cista_SOURCE_DIR}/include/cista
    | sed -E 's/namespace cista/namespace wirepump::cista/'
    > wirepump.hpp
)
add_custom_target(wirepump-single-header-build DEPENDS wirepump.hpp)

add_library(wirepump-single-header INTERFACE)
target_compile_features(wirepump-single-header INTERFACE cxx_std_20)
set_property(TARGET wirepump-single-header PROPERTY CXX_STANDARD 20)
target_include_directories(wirepump-single-header INTERFACE ${CMAKE_CURRENT_BINARY_DIR})
add_dependencies(wirepump-single-header wirepump-single-header-build)

# Tests
option(wirepump_ENABLE_TESTS "Build wirepump tests" ${PROJECT_IS_TOP_LEVEL})
if(wirepump_ENABLE_TESTS)
  add_subdirectory(tests)
endif()

# Install
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/wirepump.hpp TYPE INCLUDE)
