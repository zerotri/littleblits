cmake_minimum_required(VERSION 3.15)
project(rockit)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# third party libraries
add_subdirectory("third_party/sdl2")

# engine library
set(PROJECT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/application.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/math/vec2.cpp
)

add_library(${PROJECT_NAME} ${PROJECT_SOURCES})
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/")
set_target_properties(${PROJECT_NAME} PROPERTIES 
    C_STANDARD 11
    C_STANDARD_REQUIRED YES
    C_EXTENSIONS ON
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED 14
    CXX_EXTENSIONS ON
)

target_include_directories( ${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


# samples
add_subdirectory("samples/demo")