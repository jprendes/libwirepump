include(FetchContent)

FetchContent_Declare(wirepump-asio
  GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
  GIT_TAG        asio-1-27-0
)
FetchContent_Populate(wirepump-asio)
FetchContent_GetProperties(wirepump-asio)

add_library(wirepump-asio INTERFACE)
target_include_directories(wirepump-asio INTERFACE ${wirepump-asio_SOURCE_DIR}/asio/include)
target_compile_features(wirepump-asio INTERFACE cxx_std_20)
set_property(TARGET wirepump-asio PROPERTY CXX_STANDARD 20)
target_compile_definitions(wirepump-asio INTERFACE
  ASIO_HEADER_ONLY ASIO_STANDALONE ASIO_SEPARATE_COMPILATION ASIO_NO_DEPRECATED)
find_package(Threads)
target_link_libraries(wirepump-asio INTERFACE Threads::Threads)