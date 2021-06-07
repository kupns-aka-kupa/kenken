cmake_minimum_required(VERSION 3.5)

project(SolverTestCase LANGUAGES CXX)

find_package(Qt5Test REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

include_directories(${Internal_SOURCE_DIR})
include_directories(${cppitertools_SOURCE_DIR})
add_executable(${PROJECT_NAME} tst_solvertestcase.cpp)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Test TestData Internal)

