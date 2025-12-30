cmake_minimum_required(VERSION 3.10)
project(Lumina)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC "src/*.cpp")

add_executable(Lumina ${SRC})
target_include_directories(Lumina PRIVATE .)
find_package(Threads REQUIRED)
target_link_libraries(Lumina Threads::Threads)
