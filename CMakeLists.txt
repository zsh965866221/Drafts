cmake_minimum_required (VERSION 3.11)

project(compare)

# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories("./")

add_executable(main compare.cpp container.cpp)

