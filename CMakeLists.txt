cmake_minimum_required(VERSION 3.1)

project(bug VERSION 1.0 DESCRIPTION "ChakraCore length bug" LANGUAGES CXX C)

add_executable(bug src/main.cpp)

target_include_directories(bug PUBLIC include)

configure_file(lib/ChakraCore.dll ${CMAKE_BINARY_DIR} COPYONLY)

target_link_libraries(bug ${CMAKE_SOURCE_DIR}/lib/ChakraCore.lib)