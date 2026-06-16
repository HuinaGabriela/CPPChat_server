cmake_minimum_required(VERSION 3.20)

project(CPPChat LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    chat_server
    src/server/main.cpp
    src/network/tcp_server.cpp
)