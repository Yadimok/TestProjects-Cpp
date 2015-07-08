cmake_minimum_required(VERSION 2.8)

project (dynQueue)

add_definitions(
	-std=c++11
	)

add_executable(queue DynQueue.cpp)