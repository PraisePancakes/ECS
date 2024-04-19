cmake_minimum_required(VERSION 3.22.0)

set(PROJECT_NAME ecs)
set(SOURCES src/main.cpp)

project(${PROJECT_NAME} LANGUAGES CXX)


add_executable(${PROJECT_NAME} ${SOURCES})