project(core)

add_library(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}      PUBLIC math)
target_compile_features(${PROJECT_NAME}    PUBLIC cxx_std_23)
target_precompile_headers(${PROJECT_NAME}  PUBLIC public.hpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(${PROJECT_NAME} PRIVATE time.cpp)