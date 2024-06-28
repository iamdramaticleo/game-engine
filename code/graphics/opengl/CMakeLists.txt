target_precompile_headers(${PROJECT_NAME} PRIVATE private.hpp)
target_link_libraries(${PROJECT_NAME}     PRIVATE glad)

target_sources(${PROJECT_NAME} PRIVATE pipeline.cpp context.cpp commands.cpp vertex_array.cpp buffer.cpp
                                       shader_stage.cpp shader.cpp)