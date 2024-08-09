project(gainput)

include_directories (include/)

file(GLOB_RECURSE sources source/*.cpp source/*.h include/*.h)

add_library(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_sources(${PROJECT_NAME} PRIVATE ${sources})
