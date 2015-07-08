cmake_minimum_required(VERSION 2.8)

project (dynStack)

add_definitions(
	-std=c++11
	)

add_executable(stack DynStack.cpp)