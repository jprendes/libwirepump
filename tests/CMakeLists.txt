include(CTest)

macro(wirepump_test name)
    add_executable(wirepump-tests-${name} ${name}.cpp)
    target_link_libraries(wirepump-tests-${name} wirepump)
    add_test(wirepump-tests-${name} wirepump-tests-${name})

    add_executable(wirepump-tests-single-header-${name} ${name}.cpp)
    target_link_libraries(wirepump-tests-single-header-${name} wirepump-single-header)
    add_test(wirepump-tests-single-header-${name} wirepump-tests-single-header-${name})

    if(NOT "${ARGN}" STREQUAL "0")
        if("${ARGV1}" STREQUAL "ASIO")
            target_link_libraries(wirepump-tests-${name} wirepump-asio)
            target_link_libraries(wirepump-tests-single-header-${name} wirepump-asio)
        endif()
    endif()
endmacro()

# Basic tests
foreach(test char bool integers enum floating_point string tuple optional variant vector demo adapter)
    wirepump_test(${test})
endforeach()

# Tests depending on asio
foreach(test asio demo_asio)
    wirepump_test(${test} ASIO)
endforeach()
