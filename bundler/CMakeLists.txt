add_executable(bundler main.cpp)
target_compile_features(bundler INTERFACE cxx_std_20)
set_property(TARGET bundler PROPERTY CXX_STANDARD 20)
