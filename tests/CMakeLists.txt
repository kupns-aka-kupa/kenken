cmake_minimum_required(VERSION 3.5)

project(Tests LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PARSER_TEST_CASE "${PROJECT_SOURCE_DIR}/parser")

enable_testing()

add_subdirectory(${PARSER_TEST_CASE})

