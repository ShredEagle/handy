cmake_minimum_required(VERSION 3.16)
project(PackageTest CXX)

find_package(Handy REQUIRED COMPONENTS handy platform resource)

add_executable(example example.cpp)
target_link_libraries(example PRIVATE ad::handy)
