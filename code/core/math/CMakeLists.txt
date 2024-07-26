target_precompile_headers(${PROJECT_NAME} PUBLIC public.hpp)
target_link_libraries(${PROJECT_NAME}     PUBLIC glm)
target_sources(${PROJECT_NAME}            PUBLIC vec3.cpp)