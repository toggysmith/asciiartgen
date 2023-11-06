# ----------------------------------------------------------------------------------------------------
# Configure CMake.
# ----------------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.9.0)

project(asciiartgen LANGUAGES CXX)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



# ----------------------------------------------------------------------------------------------------
# Variables for asciiartgen.
# ----------------------------------------------------------------------------------------------------
set(ASCIIARTGEN_SOURCES_WITHOUT_MAIN "src/conversion_method.cpp" "src/color.cpp")
set(ASCIIARTGEN_SOURCES "src/main.cpp" ${ASCIIARTGEN_SOURCES_WITHOUT_MAIN})
set(ASCIIARTGEN_TEST_SOURCES "tests/main.cpp" "tests/test_conversion_method.cpp")
set(ASCIIARTGEN_EXTERNAL "external")
set(ASCIIARTGEN_EXECUTABLE_NAME "asciiartgen")
set(BUILD_EXAMPLES OFF)
set(BUILD_SHARED_LIBS OFF)



# ----------------------------------------------------------------------------------------------------
# Add doctest.
# ----------------------------------------------------------------------------------------------------
add_subdirectory(${ASCIIARTGEN_EXTERNAL}/doctest)



# ----------------------------------------------------------------------------------------------------
# Add SFML.
# ----------------------------------------------------------------------------------------------------
set(SFML_USE_STATIC_LIBS ON)
set(SFML_BUILD_EXAMPLES OFF)
set(SFML_BUILD_DOC OFF)
set(SFML_BUILD_AUDIO OFF)
set(SFML_BUILD_GRAPHICS ON)
set(SFML_BUILD_WINDOW ON)
set(SFML_BUILD_NETWORK OFF)
add_subdirectory(${ASCIIARTGEN_EXTERNAL}/SFML)



# ----------------------------------------------------------------------------------------------------
# Build object library out of sources, except entry point.
# ----------------------------------------------------------------------------------------------------
add_library(asciiartgen_source_object_library OBJECT ${ASCIIARTGEN_SOURCES_WITHOUT_MAIN})
target_include_directories(asciiartgen_source_object_library PUBLIC ${ASCIIARTGEN_EXTERNAL} ${ASCIIARTGEN_EXTERNAL}/doctest "src")
target_link_libraries(asciiartgen_source_object_library PUBLIC sfml-graphics sfml-window doctest)



# ----------------------------------------------------------------------------------------------------
# Build executable out of sources, including entry point.
# ----------------------------------------------------------------------------------------------------
add_executable(asciiartgen "src/main.cpp")
target_link_libraries(asciiartgen PRIVATE asciiartgen_source_object_library)



# ----------------------------------------------------------------------------------------------------
# Build test runner out of sources, including test sources.
# ----------------------------------------------------------------------------------------------------
add_executable(test_runner ${ASCIIARTGEN_TEST_SOURCES})
target_link_libraries(test_runner PRIVATE asciiartgen_source_object_library)
include(${ASCIIARTGEN_EXTERNAL}/doctest/scripts/cmake/doctest.cmake)
doctest_discover_tests(test_runner)



# ----------------------------------------------------------------------------------------------------
# Don't place build output in Debug/ and Release/ directories.
# ----------------------------------------------------------------------------------------------------
set_target_properties(asciiartgen PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(asciiartgen PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(test_runner PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(test_runner PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})



# ----------------------------------------------------------------------------------------------------
# Copy everything in data directory from source directory to build directory.
# ----------------------------------------------------------------------------------------------------
add_custom_command(TARGET asciiartgen POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                           ${CMAKE_CURRENT_SOURCE_DIR}/data
                           ${CMAKE_CURRENT_BINARY_DIR}/data)