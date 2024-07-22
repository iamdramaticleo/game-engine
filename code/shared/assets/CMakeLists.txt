project(assets)

add_library(${PROJECT_NAME})

target_compile_features(${PROJECT_NAME}    PUBLIC cxx_std_23)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_precompile_headers(${PROJECT_NAME}  PUBLIC public.hpp)

target_sources(${PROJECT_NAME} PRIVATE file.cpp)