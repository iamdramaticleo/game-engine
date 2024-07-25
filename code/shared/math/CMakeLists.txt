project(math)

add_library(${PROJECT_NAME} INTERFACE)

target_link_libraries(${PROJECT_NAME}      INTERFACE glm)
target_compile_features(${PROJECT_NAME}    INTERFACE cxx_std_23)
target_precompile_headers(${PROJECT_NAME}  INTERFACE public.hpp)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})