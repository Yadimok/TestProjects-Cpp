cmake_minimum_required(VERSION 3.10)

project(SerialUsb VERSION 1.0)

set(BOOST_USE_MULTITHREADED ON)
set(BOOST_USE_STATIC_LIBS ON)
set(BOOST_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.71.0 REQUIRED COMPONENTS system thread)

if(Boost_FOUND)
	add_executable(serialUsb serialusb.hpp serialusb.cpp main.cpp)
	target_link_libraries(serialUsb Boost::system Boost::thread)
endif()