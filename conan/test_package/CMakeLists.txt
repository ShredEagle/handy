cmake_minimum_required(VERSION 3.16)
project(PackageTest CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_CURRENT_BINARY_DIR}>)
find_package(Handy REQUIRED COMPONENTS handy)

add_executable(example example.cpp)
target_link_libraries(example PRIVATE ad::handy)
