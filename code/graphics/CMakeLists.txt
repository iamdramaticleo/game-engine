project(graphics)

option(USE_OPENGL_API "use opengl api" OFF)

add_library(${PROJECT_NAME})

target_compile_features(${PROJECT_NAME}    PUBLIC cxx_std_23)
target_precompile_headers(${PROJECT_NAME}  PUBLIC public.hpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if (USE_OPENGL_API)
   add_subdirectory(opengl)
endif()