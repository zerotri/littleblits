project(doctest)
include(ExternalProject)
find_package(Git REQUIRED)

ExternalProject_Add(
    ${PROJECT_NAME}
    PREFIX ${CMAKE_BINARY_DIR}/external/doctest
    GIT_REPOSITORY https://github.com/onqtam/doctest.git
    GIT_TAG 2.4.6
    TIMEOUT 10
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
)

ExternalProject_Get_Property(doctest source_dir)
set(DOCTEST_INCLUDE_DIR ${source_dir}/ CACHE INTERNAL "Path to include folder for doctest")
