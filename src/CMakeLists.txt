add_headers_and_sources(primality_tests ${CMAKE_CURRENT_SOURCE_DIR})
add_library(primality_tests ${primality_tests_headers} ${primality_tests_sources} probable_primes.h primality_status.h)
target_link_libraries(primality_tests gmp gmpxx)
