cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)
project(MyProject C CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -pthread")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/include")

find_package(PythonLibs)
include_directories("${PYTHON_INCLUDE_DIRS}")
link_libraries("${PYTHON_LIBRARIES}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Kaimon)


file(GLOB all_files "Kaimon/src/*.cpp" "Kaimon/src/*.h")

add_executable(reingine ${all_files})

