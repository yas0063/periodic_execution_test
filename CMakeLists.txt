cmake_minimum_required(VERSION 3.10)

project(PERIODIC_EXECUTION_TEST)

set(CMAKE_CXX_FLAGS "-O2 -g -Wno-format -pthread")

add_definitions(-std=c++17)

ADD_EXECUTABLE(periodic_test
	main.cpp
)


