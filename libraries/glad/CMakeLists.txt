project(glad)

add_library(${PROJECT_NAME} glad.c)

target_include_directories(${PROJECT_NAME} PUBLIC include)
