cmake_minimum_required(VERSION 3.1)

project(file_io)

add_compile_options(-std=c++14)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(file_reader 
src/file_reader.cpp)

add_library(file_writer
src/file_writer.cpp)

add_executable(${PROJECT_NAME}
src/main.cpp)

# set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

target_link_libraries(${PROJECT_NAME}
file_reader
file_writer)


