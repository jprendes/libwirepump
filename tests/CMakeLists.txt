include(CTest)

macro(make_test name)
    add_executable(${name}-test ${name}.cpp)
    target_link_libraries(${name}-test wirepump)
    add_test(${name}-test ${name}-test)

    add_executable(${name}-test-single-header ${name}.cpp)
    target_link_libraries(${name}-test-single-header wirepump-single-header)
    add_test(${name}-test-single-header ${name}-test-single-header)
endmacro()

foreach(test char integers enum floating_point string tuple variant vector demo asio)
    make_test(${test})
endforeach()

target_link_libraries(asio-test asio)
target_link_libraries(asio-test-single-header asio)