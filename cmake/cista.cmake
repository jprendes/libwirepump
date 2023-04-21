include(FetchContent)

FetchContent_Declare(wirepump-cista
  GIT_REPOSITORY https://github.com/felixguendling/cista.git
  GIT_TAG        55e67f3a552ec79ab6d094d7da43f0caaaa2bde5
)
FetchContent_Populate(wirepump-cista)
FetchContent_GetProperties(wirepump-cista)

add_library(wirepump-cista INTERFACE)
target_include_directories(wirepump-cista INTERFACE ${wirepump-cista_SOURCE_DIR}/include)
target_compile_features(wirepump-cista INTERFACE cxx_std_20)
set_property(TARGET wirepump-cista PROPERTY CXX_STANDARD 20)