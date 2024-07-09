
add_library(glfw ${GLFW_LIBRARY_TYPE}
                 "${GLFW_SOURCE_DIR}/include/GLFW/glfw3.h"
                 "${GLFW_SOURCE_DIR}/include/GLFW/glfw3native.h"
                 internal.h platform.h
                 context.c init.c input.c monitor.c platform.c window.c)
if (WIN32)
    target_sources(glfw PRIVATE win32_thread.h win32_module.c win32_thread.c)
endif()

if (GLFW_BUILD_WIN32)
    target_compile_definitions(glfw PRIVATE _GLFW_WIN32)
    target_sources(glfw PRIVATE win32_platform.h win32_init.c win32_monitor.c win32_window.c wgl_context.c)
endif()

if (WIN32 AND GLFW_BUILD_SHARED_LIBRARY)
    configure_file(glfw.rc.in glfw.rc @ONLY)
    target_sources(glfw PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/glfw.rc")
endif()

if (UNIX AND GLFW_BUILD_SHARED_LIBRARY)
    # On Unix-like systems, shared libraries can use the soname system.
    set(GLFW_LIB_NAME glfw)
else()
    set(GLFW_LIB_NAME glfw3)
endif()
set(GLFW_LIB_NAME_SUFFIX "")

set_target_properties(glfw PROPERTIES
                      OUTPUT_NAME ${GLFW_LIB_NAME}
                      VERSION ${GLFW_VERSION_MAJOR}.${GLFW_VERSION_MINOR}
                      SOVERSION ${GLFW_VERSION_MAJOR}
                      POSITION_INDEPENDENT_CODE ON
                      C_STANDARD 99
                      C_EXTENSIONS OFF
                      DEFINE_SYMBOL _GLFW_BUILD_DLL
                      FOLDER "GLFW3")

target_include_directories(glfw PUBLIC
                           "$<BUILD_INTERFACE:${GLFW_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
target_include_directories(glfw PRIVATE
                           "${GLFW_SOURCE_DIR}/src"
                           "${GLFW_BINARY_DIR}/src")
target_link_libraries(glfw PRIVATE Threads::Threads)

# Workaround for CMake not knowing about .m files before version 3.16
if (CMAKE_VERSION VERSION_LESS "3.16" AND APPLE)
    set_source_files_properties(cocoa_init.m cocoa_joystick.m cocoa_monitor.m
                                cocoa_window.m nsgl_context.m PROPERTIES
                                LANGUAGE C)
endif()

if (GLFW_BUILD_WIN32)
    list(APPEND glfw_PKG_LIBS "-lgdi32")
endif()

# Enable a reasonable set of warnings
# NOTE: The order matters here, Clang-CL matches both MSVC and Clang
if (MSVC)
    target_compile_options(glfw PRIVATE "/W3")
elseif (CMAKE_C_COMPILER_ID STREQUAL "GNU" OR
        CMAKE_C_COMPILER_ID STREQUAL "Clang" OR
        CMAKE_C_COMPILER_ID STREQUAL "AppleClang")

    target_compile_options(glfw PRIVATE "-Wall")
endif()

if (GLFW_BUILD_WIN32)
    target_compile_definitions(glfw PRIVATE UNICODE _UNICODE)
endif()

# Workaround for legacy MinGW not providing XInput and DirectInput
if (MINGW)
    include(CheckIncludeFile)
    check_include_file(dinput.h DINPUT_H_FOUND)
    check_include_file(xinput.h XINPUT_H_FOUND)
    if (NOT DINPUT_H_FOUND OR NOT XINPUT_H_FOUND)
        target_include_directories(glfw PRIVATE "${GLFW_SOURCE_DIR}/deps/mingw")
    endif()
endif()

# Workaround for the MS CRT deprecating parts of the standard library
if (MSVC OR CMAKE_C_SIMULATE_ID STREQUAL "MSVC")
    target_compile_definitions(glfw PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

# Workaround for -std=c99 on Linux disabling _DEFAULT_SOURCE (POSIX 2008 and more)
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_definitions(glfw PRIVATE _DEFAULT_SOURCE)
endif()

if (GLFW_BUILD_SHARED_LIBRARY)
    if (WIN32)
        if (MINGW)
            # Remove the dependency on the shared version of libgcc
            # NOTE: MinGW-w64 has the correct default but MinGW needs this
            target_link_libraries(glfw PRIVATE "-static-libgcc")

            # Remove the lib prefix on the DLL (but not the import library)
            set_target_properties(glfw PROPERTIES PREFIX "")

            # Add a suffix to the import library to avoid naming conflicts
            set_target_properties(glfw PROPERTIES IMPORT_SUFFIX "dll.a")
        else()
            # Add a suffix to the import library to avoid naming conflicts
            set_target_properties(glfw PROPERTIES IMPORT_SUFFIX "dll.lib")
        endif()
        set (GLFW_LIB_NAME_SUFFIX "dll")

        target_compile_definitions(glfw INTERFACE GLFW_DLL)
    endif()

    if (MINGW)
        # Enable link-time exploit mitigation features enabled by default on MSVC
        include(CheckCCompilerFlag)

        # Compatibility with data execution prevention (DEP)
        set(CMAKE_REQUIRED_FLAGS "-Wl,--nxcompat")
        check_c_compiler_flag("" _GLFW_HAS_DEP)
        if (_GLFW_HAS_DEP)
            target_link_libraries(glfw PRIVATE "-Wl,--nxcompat")
        endif()

        # Compatibility with address space layout randomization (ASLR)
        set(CMAKE_REQUIRED_FLAGS "-Wl,--dynamicbase")
        check_c_compiler_flag("" _GLFW_HAS_ASLR)
        if (_GLFW_HAS_ASLR)
            target_link_libraries(glfw PRIVATE "-Wl,--dynamicbase")
        endif()

        # Compatibility with 64-bit address space layout randomization (ASLR)
        set(CMAKE_REQUIRED_FLAGS "-Wl,--high-entropy-va")
        check_c_compiler_flag("" _GLFW_HAS_64ASLR)
        if (_GLFW_HAS_64ASLR)
            target_link_libraries(glfw PRIVATE "-Wl,--high-entropy-va")
        endif()

        # Clear flags again to avoid breaking later tests
        set(CMAKE_REQUIRED_FLAGS)
    endif()

    if (UNIX)
        # Hide symbols not explicitly tagged for export from the shared library
        target_compile_options(glfw PRIVATE "-fvisibility=hidden")
    endif()
endif()

foreach(arg ${glfw_PKG_DEPS})
    string(APPEND deps " ${arg}")
endforeach()
foreach(arg ${glfw_PKG_LIBS})
    string(APPEND libs " ${arg}")
endforeach()

set(GLFW_PKG_CONFIG_REQUIRES_PRIVATE "${deps}" CACHE INTERNAL
    "GLFW pkg-config Requires.private")
set(GLFW_PKG_CONFIG_LIBS_PRIVATE "${libs}" CACHE INTERNAL
    "GLFW pkg-config Libs.private")
