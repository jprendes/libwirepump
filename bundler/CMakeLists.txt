find_package(Threads REQUIRED)

add_executable(wirepump-bundler main.cpp)
target_compile_features(wirepump-bundler INTERFACE cxx_std_20)
set_property(TARGET wirepump-bundler PROPERTY CXX_STANDARD 20)
target_link_libraries(wirepump-bundler PRIVATE Threads::Threads)
