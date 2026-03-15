cmake_minimum_required(VERSION 3.20)

project(search_engine)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(search_engine

        src/main.cpp
        src/ConverterJSON.cpp
        src/InvertedIndex.cpp
        src/SearchServer.cpp
)