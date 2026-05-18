cmake_minimum_required(VERSION 3.10)
project(NamedPipes_Database)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(Server)
add_subdirectory(Client)
