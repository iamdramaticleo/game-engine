target_precompile_headers(${PROJECT_NAME} PUBLIC public.hpp)
target_link_libraries(${PROJECT_NAME}     PUBLIC glfw)

target_sources(${PROJECT_NAME} PRIVATE platform.cpp platform_factory.cpp window.cpp)