cmake_minimum_required(VERSION 2.8)

project(SkipList)

add_definitions(
		-std=c++11
		)

add_executable(skiplist SkipList.cpp)