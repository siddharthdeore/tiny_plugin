cmake_minimum_required(VERSION 3.14)

project(tiny_plugin)

set(CMAKE_CXX_STANDARD 14)
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

add_library(tiny_plugin INTERFACE)
target_include_directories(tiny_plugin INTERFACE 
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Specify the header files for installation
install(DIRECTORY include/ DESTINATION include)

set(CPACK_PACKAGE_NAME tiny_plugin)
set(CPACK_PACKAGE_CONTACT "siddharth deore <siddharthdeore@gmail.com>")
set(CPACK_GENERATOR DEB)
include(CPack)


# make uninstall
add_custom_target("uninstall" COMMENT "Uninstall installed files")
add_custom_command(
    TARGET "uninstall"
    POST_BUILD
    COMMENT "Uninstall files with install_manifest.txt"
    COMMAND xargs rm -vf < install_manifest.txt || echo Nothing in
            install_manifest.txt to be uninstalled!
)

# Optional: Add an alias for easier usage
#add_library(YourNamespace::YourLibrary ALIAS YourLibrary)

add_subdirectory(examples)

add_executable(main main.cpp)
target_link_libraries(main ${COMON_LIBS})
target_link_directories(main PUBLIC ${CMAKE_BINARY_DIR}) 