cmake_minimum_required(VERSION 3.14)

project(tiny_plugin)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON) # -fPIC flag  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if(MSVC)
  add_compile_options( /W4 /WX)
else()
    # add_compile_options( -Wall -Wextra -Wpedantic -Werror)
    add_compile_options( -Wall -Wextra)
endif()
set(COMON_LIBS pthread dl)

include_directories("include")

add_subdirectory(examples)

add_executable(main main.cpp)
target_link_libraries(main ${COMON_LIBS})
target_link_directories(main PUBLIC ${CMAKE_BINARY_DIR}) 