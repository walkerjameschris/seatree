cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME seatree)
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

set(SOURCES main.cpp)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

add_executable(${PROJECT_NAME} ${SOURCES})
