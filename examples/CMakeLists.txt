cmake_minimum_required(VERSION 3.14)

# sharead libraries
add_library(simple_function SHARED "plugins/simple_function.cpp")

add_library(SimplePlugin SHARED "plugins/SimplePlugin.cpp")

add_library(ComplexPlugin SHARED "plugins/ComplexPlugin.cpp")

# executables
add_executable(function_loader function_loader.cpp)
target_link_directories(function_loader PUBLIC ${CMAKE_BINARY_DIR}) 

add_executable(class_loader class_loader.cpp)
target_link_libraries(class_loader ComplexPlugin)
target_link_directories(class_loader PUBLIC ${CMAKE_BINARY_DIR}) 
