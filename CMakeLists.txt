cmake_minimum_required(VERSION 3.15)
project(rockit)

enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(ROCKIT_LIBRARY_DIRS "")
set(ROCKIT_LIBRARIES "")
set(ROCKIT_INCLUDES "")

# third party libraries
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(ROCKIT_PLATFORM "sdl2")
    set(ROCKET_RENDERER "opengl")
    # set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    # set(ROCKIT_PLATFORM "sdl2")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # set(ROCKIT_PLATFORM "sdl2")
    # set(ROCKET_RENDERER "opengl")
endif()


# engine library
set(PROJECT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/actor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/application.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/coroutine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/pointer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/referencecounter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/resource.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/pipeline.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/rendertarget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics/shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/math/vec2.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/platform/window.cpp
)

add_subdirectory("third_party/doctest")
include_directories(${DOCTEST_INCLUDE_DIR})

if(ROCKIT_PLATFORM STREQUAL "sdl2")
    message("Using Platform: SDL2")
    add_subdirectory("third_party/sdl2")

    list(APPEND PROJECT_SOURCES
            modules/platform/sdl2/platform_sdl2.cpp
            # modules/platform/sdl2/renderer_sdl2.cpp
    )
    list(APPEND ROCKIT_LIBRARY_DIRS
        ${SDL2_LIBRARY_DIRS}
    )
    list(APPEND ROCKIT_LIBRARIES
        ${SDL2_LIBRARIES}
    )
    list(APPEND ROCKIT_INCLUDES
        ${SDL2_INCLUDE_DIRS}
    )
endif()

if(ROCKET_RENDERER STREQUAL "opengl")
    message("Using Renderer: OpenGL")
    add_subdirectory("third_party/opengl")

    list(APPEND PROJECT_SOURCES
            modules/renderer/opengl/renderer_opengl.h
    )
    list(APPEND ROCKIT_LIBRARY_DIRS
            ${OPENGL_LIBRARY_DIR}
            ${GLEW_LIBRARY_DIR}
    )
    list(APPEND ROCKIT_LIBRARIES
            ${OPENGL_LIBRARIES}
            ${GLEW_LIBRARIES}
    )
    message("Library dirs: ${ROCKIT_LIBRARIES}")
    list(APPEND ROCKIT_INCLUDES
            ${OPENGL_INCLUDE_DIRS}
            ${GLEW_INCLUDE_DIRS}
    )
endif()

add_library(${PROJECT_NAME} ${PROJECT_SOURCES})
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/")
set_target_properties(${PROJECT_NAME} PROPERTIES 
    C_STANDARD 11
    C_STANDARD_REQUIRED YES
    C_EXTENSIONS ON
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED 17
    CXX_EXTENSIONS ON
)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_options(${PROJECT_NAME} PUBLIC
        /EHs
    )
endif()

message("compile definitions: ${ROCKIT_DEFINITIONS}")
target_compile_definitions( ${PROJECT_NAME} PUBLIC
        ${ROCKIT_DEFINITIONS}
)

target_include_directories( ${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/modules
    ${ROCKIT_INCLUDES}
)

message("Library dirs: ${ROCKIT_LIBRARY_DIRS}")
target_link_directories(${PROJECT_NAME} PUBLIC
    ${ROCKIT_LIBRARY_DIRS}
)
message("Libraries: ${ROCKIT_LIBRARIES}")
target_link_libraries( ${PROJECT_NAME}
    ${ROCKIT_LIBRARIES}
)


# samples
add_subdirectory("samples/demo")
add_subdirectory( tests )
