macro(add_test test_name)
    add_executable(${test_name} ${test_name}.cpp)
    target_link_libraries(${test_name} PRIVATE primality_tests gtest gtest_main)
    target_include_directories(${test_name} PRIVATE "${PROJECT_SOURCE_DIR}/src")
endmacro()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/primes_2_to_99991.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_test(low_primes_probable_primes_test)
add_test(utilities_test)
add_test(qs_test)
