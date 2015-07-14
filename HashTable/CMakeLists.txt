cmake_minimum_required(VERSION 2.8)

project(hashmap)

add_definitions(
		-std=c++11
		)

add_executable(hashmap HashTable.cpp)