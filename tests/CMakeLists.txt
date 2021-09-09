add_executable( testing_build
    test.cpp
    test_containers.cpp
)
add_dependencies( testing_build doctest )
add_test( NAME all_tests COMMAND testing_build )

set_target_properties(testing_build PROPERTIES
    C_STANDARD 11
    C_STANDARD_REQUIRED YES
    C_EXTENSIONS ON
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED 17
    CXX_EXTENSIONS ON
)

target_link_libraries(testing_build PUBLIC
    rockit
)

target_include_directories(testing_build PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)
