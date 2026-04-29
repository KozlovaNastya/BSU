cmake_minimum_required(VERSION 3.10)
project(IPC_File_Messaging)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(Receiver)
add_subdirectory(Sender)
