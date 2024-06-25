target_precompile_headers(${PROJECT_NAME} PUBLIC public.hpp)
target_link_libraries(${PROJECT_NAME}     PUBLIC glad)

target_sources(${PROJECT_NAME} PRIVATE pipeline.cpp)