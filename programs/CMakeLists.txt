add_headers_and_sources(large_prime_numbers ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(large_prime_numbers ${large_prime_numbers_sources})
target_link_libraries(large_prime_numbers PRIVATE primality_tests)
target_include_directories(large_prime_numbers PRIVATE "${PROJECT_SOURCE_DIR}/src")
