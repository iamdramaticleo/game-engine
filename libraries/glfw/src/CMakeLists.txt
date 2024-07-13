add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE win32_module.c win32_thread.c win32_init.c win32_monitor.c win32_window.c
                                       wgl_context.c context.c init.c input.c monitor.c platform.c window.c)

target_include_directories(${PROJECT_NAME} PUBLIC "$<BUILD_INTERFACE:${GLFW_SOURCE_DIR}/include>"
                                                  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
                                          PRIVATE "${GLFW_SOURCE_DIR}/src"
                                                  "${GLFW_BINARY_DIR}/src")

target_compile_definitions(${PROJECT_NAME} PRIVATE UNICODE _UNICODE _GLFW_WIN32)
target_link_libraries(${PROJECT_NAME}      PRIVATE Threads::Threads)
