add_library(glfw)

target_include_directories(glfw PUBLIC "../include" PRIVATE "src")
target_sources(glfw PRIVATE context.c init.c input.c monitor.c platform.c window.c win32_module.c win32_thread.c)

target_compile_definitions(glfw PRIVATE _GLFW_WIN32)
target_sources(glfw PRIVATE win32_init.c win32_monitor.c win32_window.c wgl_context.c)

target_link_libraries(glfw PRIVATE Threads::Threads)

if (GLFW_BUILD_WIN32)
    target_compile_definitions(glfw PRIVATE UNICODE _UNICODE)
endif()

# Workaround for the MS CRT deprecating parts of the standard library
if (MSVC OR CMAKE_C_SIMULATE_ID STREQUAL "MSVC")
    target_compile_definitions(glfw PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()