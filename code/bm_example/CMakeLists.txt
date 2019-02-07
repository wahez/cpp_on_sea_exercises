cmake_minimum_required(VERSION 2.8)

project(bm_example)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -falign-loops=32 -fno-omit-frame-pointer")

add_executable(${CMAKE_PROJECT_NAME}
    bm_example.cc
)

target_link_libraries(${CMAKE_PROJECT_NAME}
    benchmark
    benchmark_main
    papi
    pthread
)
