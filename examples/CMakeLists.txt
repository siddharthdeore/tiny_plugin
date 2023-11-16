cmake_minimum_required(VERSION 3.14)
project(examples)

add_library(simple_function SHARED "plugins/simple_function.cpp")
target_link_libraries(simple_function dl)
target_include_directories(simple_function PUBLIC include)

add_library(SimplePlugin SHARED "plugins/SimplePlugin.cpp" "plugins/SimplePlugin.h")
target_link_libraries(SimplePlugin dl)




add_executable(load_function load_function.cpp)
target_link_libraries(load_function ${COMON_LIBS})
target_link_directories(load_function PUBLIC ${CMAKE_BINARY_DIR}) 

add_executable(load_class load_class.cpp)
target_link_libraries(load_class ${COMON_LIBS})
target_link_directories(load_class PUBLIC ${CMAKE_BINARY_DIR}) 
message(WARNINF${CMAKE_BINARY_DIR})