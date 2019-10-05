cmake_minimum_required (VERSION 3.11)

project(ACSearch)

include_directories("./")

add_executable(main main.cpp ACSearch.cpp container.cpp)

