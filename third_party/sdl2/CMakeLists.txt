project(sdl2)
include(ExternalProject)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(SDL2_VERSION "2.0.12")
    set(SDL2_LIBRARY_DIRS "${CMAKE_BINARY_DIR}/external/lib")
    set(SDL2_LIBRARIES "SDL2.lib")
    set(SDL2_INCLUDE_DIRS "${CMAKE_BINARY_DIR}/external/include/")
    ExternalProject_Add(
        sdl2
        PREFIX ${CMAKE_BINARY_DIR}/external/
        DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/dl
        URL http://libsdl.org/release/SDL2-devel-${SDL2_VERSION}-VC.zip
        URL_MD5 C2262A2F2D4E8487B75B541BFEE3C2C4
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND 
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_BINARY_DIR}/external/src/sdl2/lib/x64   ${SDL2_LIBRARY_DIRS}
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_BINARY_DIR}/external/src/sdl2/include   ${SDL2_INCLUDE_DIRS}/SDL2/
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/external/src/sdl2/lib/x64/SDL2.dll   ${CMAKE_BINARY_DIR}/bin/$<CONFIG>/SDL2.dll
        )

    set(SDL2_VERSION "${SDL2_VERSION}" PARENT_SCOPE)
    set(SDL2_LIBRARY_DIRS "${SDL2_LIBRARY_DIRS}" PARENT_SCOPE)
    set(SDL2_LIBRARIES "${SDL2_LIBRARIES}" PARENT_SCOPE)
    set(SDL2_INCLUDE_DIRS "${SDL2_INCLUDE_DIRS}" PARENT_SCOPE)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
# todo(Wynter): Add SDL package configuration for macOS
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2)
endif()