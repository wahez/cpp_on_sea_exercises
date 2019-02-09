cmake_minimum_required(VERSION 2.8.12)

project(bm_example)

find_package(benchmark REQUIRED)

string(
    APPEND _opts
    "$<IF:$<CXX_COMPILER_ID:MSVC>,"
        "/W4;/Oy"
        "$<$<CONFIG:RELEASE>:/O2>,"
        "-Wall;-Wextra;-falign-loops=32;-fno-omit-frame-pointer"
        "$<$<CONFIG:RELEASE>:-O3>"
    ">"
)

add_executable(${CMAKE_PROJECT_NAME} bm_example.cc)

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE "${_opts}")

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES CXX_STANDARD 17)
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_14)

target_link_libraries(${CMAKE_PROJECT_NAME}
    benchmark::benchmark
    benchmark::benchmark_main
)