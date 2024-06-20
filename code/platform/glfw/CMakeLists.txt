target_precompile_headers(${PROJECT_NAME} PUBLIC public.hpp)
target_link_libraries(${PROJECT_NAME}     PUBLIC glfw)

target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_EXPOSE_NATIVE_WIN32)

target_sources(${PROJECT_NAME} PRIVATE platform.cpp)