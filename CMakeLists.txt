cmake_minimum_required(VERSION 3.10)
project(cpp_server)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.65.1)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(cpp_server run_server.cpp TCP_server.cpp TCP_server.hpp TCP_connection.cpp TCP_connection.hpp)
endif()