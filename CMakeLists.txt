cmake_minimum_required(VERSION 3.10)
project(vksbc)

include(cmake/c++-standards.cmake)
include(cmake/code-coverage.cmake)
include(cmake/sanitizers.cmake)
include(cmake/tools.cmake)

cxx_11()

add_executable(vksbc src/main.cpp)
target_code_coverage(vksbc)

install(TARGETS vksbc
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)