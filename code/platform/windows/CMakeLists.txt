target_link_libraries(${PROJECT_NAME}     PRIVATE glfw)
target_precompile_headers(${PROJECT_NAME} PRIVATE private.hpp)
target_sources(${PROJECT_NAME}            PRIVATE platform_factory.cpp window.cpp)