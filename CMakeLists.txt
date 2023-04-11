cmake_minimum_required(VERSION 3.25)

project(wirepump VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_EXTENSIONS OFF)

option(wirepump_TESTS "Build wirepump tests" ON)

include(FetchContent)
FetchContent_Declare(cista
  GIT_REPOSITORY https://github.com/felixguendling/cista.git
  GIT_TAG        55e67f3a552ec79ab6d094d7da43f0caaaa2bde5
)
FetchContent_MakeAvailable(cista)
FetchContent_GetProperties(cista)

file(GLOB_RECURSE wirepump-include-files include/*.hpp)

add_library(wirepump INTERFACE)
set_property(TARGET wirepump PROPERTY CXX_STANDARD 17)
target_link_libraries(wirepump INTERFACE cista)
target_include_directories(wirepump INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(wirepump INTERFACE cxx_std_17)

add_subdirectory(bundler)

if(wirepump_TESTS)
add_subdirectory(tests)
endif()

# Generate the single-header bundle
add_custom_command(
  OUTPUT wirepump.hpp
  DEPENDS bundler ${wirepump-include-files}
  COMMAND bundler
    ${CMAKE_CURRENT_SOURCE_DIR}/include/wirepump.hpp
    wirepump=${CMAKE_CURRENT_SOURCE_DIR}/include/wirepump
    cista=${cista_SOURCE_DIR}/include/cista
    | sed -E 's/namespace cista/namespace wirepump::cista/'
    > wirepump.hpp
)
add_custom_target(wirepump-single-header-build DEPENDS wirepump.hpp)

add_library(wirepump-single-header INTERFACE)
target_include_directories(wirepump-single-header INTERFACE ${CMAKE_CURRENT_BINARY_DIR})
target_compile_features(wirepump-single-header INTERFACE cxx_std_17)
add_dependencies(wirepump-single-header wirepump-single-header-build)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/wirepump.hpp TYPE INCLUDE)
