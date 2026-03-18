add_library(search_engine_lib
    SearchServer.cpp
    InvertedIndex.cpp
    ConverterJSON.cpp
)

target_include_directories(search_engine_lib PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(search_engine
    main.cpp
)

target_link_libraries(search_engine
    search_engine_lib
)