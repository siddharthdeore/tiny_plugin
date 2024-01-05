# FILEPATH: /home/sid/dev/cpp/tiny_plugin/CMakeLists.txt
cmake_minimum_required(VERSION 3.14)

project(tiny_plugin VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON) # -fPIC flag

# Output paths
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")

# Build shared libs
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

include(GNUInstallDirs)

include(CMakePackageConfigHelpers)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
if(MSVC)
    #add_compile_options(/W4 /WX)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)
else()
    add_compile_options(-Wall -Wextra)
endif()

include_directories("include")
file(GLOB tiny_plugin_HDR "include/tiny_plugin/*.h")
add_library(tiny_plugin INTERFACE)
target_include_directories(tiny_plugin INTERFACE 
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)


set_target_properties(tiny_plugin PROPERTIES  PUBLIC_HEADER "${tiny_plugin_HDR}")

# List exported CMake package dependencies
install(TARGETS ${PROJECT_NAME}
  EXPORT  ${PROJECT_NAME}
  COMPONENT runtime
  LIBRARY       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT shlib
  ARCHIVE       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT lib
  RUNTIME       DESTINATION "${CMAKE_INSTALL_BINDIR}"                            COMPONENT bin
  PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/tiny_plugin")

include(InstallBasicPackageFiles)
install_basic_package_files(${PROJECT_NAME}
  NAMESPACE tiny_plugin::
  VERSION ${${PROJECT_NAME}_VERSION}
  COMPATIBILITY SameMajorVersion
  VARS_PREFIX ${PROJECT_NAME}
  NO_CHECK_REQUIRED_COMPONENTS_MACRO)


# Install package.xml to share
install(FILES package.xml DESTINATION share/cmake/tiny_plugin)

set(CPACK_PACKAGE_NAME tiny_plugin)
set(CPACK_PACKAGE_CONTACT "siddharth deore <siddharthdeore@gmail.com>")
set(CPACK_GENERATOR DEB)
include(CPack)

# make uninstall
include(AddUninstallTarget)

# Optional: Add an alias for easier usage
# add_library(YourNamespace::YourLibrary ALIAS YourLibrary)

add_subdirectory(examples)

add_executable(main main.cpp)
target_link_libraries(main )
target_link_directories(main PUBLIC ${CMAKE_BINARY_DIR})