#=======================================================================================================================
project(graphics)
#=======================================================================================================================
add_library(${PROJECT_NAME})
#=======================================================================================================================
target_compile_features(${PROJECT_NAME}    PUBLIC cxx_std_23)
target_precompile_headers(${PROJECT_NAME}  PUBLIC public.hpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#=======================================================================================================================
add_subdirectory(opengl)
#=======================================================================================================================