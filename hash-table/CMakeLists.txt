cmake_minimum_required(VERSION 3.13)
project(hash_table)

include_directories(googletest/googletest/include/)
set(CMAKE_CXX_STANDARD 14)
link_directories(googletest/ googletest/build/lib/)

add_executable(hash_table ht_tests.cpp hashTable.h hashTable.cpp)
target_link_libraries(hash_table gtest gtest_main)
