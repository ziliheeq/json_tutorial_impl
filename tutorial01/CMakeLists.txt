cmake_minimum_required (VERSION 3.13 FATAL_ERROR)
project (leptjson_test C)

message( STATUS "c compiler id is ${CMAKE_C_COMPILER_ID}" )

if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi -pedantic -Wall")
endif()

add_library(leptjson leptjson.c)
add_executable(leptjson_test test.c)
target_link_libraries(leptjson_test leptjson)