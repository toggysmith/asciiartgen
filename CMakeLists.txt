cmake_minimum_required(VERSION 3.5.0)

project(asciiartgen LANGUAGES CXX)

set(ASCIIARTGEN_SOURCES "src/main.cpp")

add_executable(asciiartgen ${ASCIIARTGEN_SOURCES})