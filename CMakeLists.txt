cmake_minimum_required(VERSION 3.5)

project(kenken LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(${PROJECT_SOURCE_DIR}/tests)
add_subdirectory(${PROJECT_SOURCE_DIR}/itertools)
add_subdirectory(${PROJECT_SOURCE_DIR}/lib)
add_subdirectory(${PROJECT_SOURCE_DIR}/data)

include_directories(${PROJECT_SOURCE_DIR}/lib)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

file(GLOB SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB HEADER_FILES ${PROJECT_SOURCE_DIR}/*.hpp)
file(GLOB UI_FILES ${PROJECT_SOURCE_DIR}/*.ui)

set(PROJECT_SOURCES
    ${SOURCE_FILES}
    ${UI_FILES}
    ${HEADER_FILES}
    ${RESOURCE_FILES})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
else()
    add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        TestData
        cppitertools
        Internal)
target_compile_definitions(${PROJECT_NAME} PRIVATE DATA_DIR="${TestData_SOURCE_DIR}")
