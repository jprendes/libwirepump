add_executable(wirepump-bundler main.cpp)
target_compile_features(wirepump-bundler INTERFACE cxx_std_20)
set_property(TARGET wirepump-bundler PROPERTY CXX_STANDARD 20)
