target_link_libraries(${PROJECT_NAME}     PRIVATE glad)
target_precompile_headers(${PROJECT_NAME} PRIVATE private.hpp)
target_sources(${PROJECT_NAME}            PRIVATE functions.cpp pipeline.cpp commands.cpp buffer.cpp vertex_array.cpp
                                                  shader_stage.cpp)