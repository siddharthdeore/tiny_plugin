cmake_minimum_required(VERSION 3.14)

# sharead libraries
add_library(simple_function SHARED "plugins/simple_function.cpp")
target_link_libraries(simple_function dl)

add_library(SimplePlugin SHARED "plugins/SimplePlugin.cpp")
target_link_libraries(SimplePlugin dl)

add_library(ComplexPlugin SHARED "plugins/ComplexPlugin.cpp")
target_link_libraries(ComplexPlugin dl)

# executables
add_executable(function_loader function_loader.cpp)
target_link_libraries(function_loader dl)
target_link_directories(function_loader PUBLIC ${CMAKE_BINARY_DIR}) 

add_executable(class_loader class_loader.cpp)
target_link_libraries(class_loader dl ComplexPlugin)
target_link_directories(class_loader PUBLIC ${CMAKE_BINARY_DIR}) 
