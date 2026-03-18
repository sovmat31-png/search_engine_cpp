add_executable(search_engine_tests
    test.cpp
)

target_include_directories(search_engine_tests PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_include_directories(search_engine_tests PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(search_engine_tests search_engine_lib)