cmake_minimum_required(VERSION 3.1)

project(file_io)

add_compile_options(-std=c++17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(filesystem_utils
src/filesystem_utils)


add_executable(file_io
src/file_io.cpp
src/main.cpp)

# set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

target_link_libraries(file_io
filesystem_utils)

# install(TARGETS file_io
#         DESTINATION ${CMAKE_SOURCE_DIR}/bin
# )


