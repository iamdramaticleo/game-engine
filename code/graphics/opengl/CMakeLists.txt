target_precompile_headers(${PROJECT_NAME} PRIVATE private.hpp)
target_link_libraries(${PROJECT_NAME}     PRIVATE glad)
target_sources(${PROJECT_NAME}    PRIVATE functions.cpp pipeline.cpp commands.cpp)