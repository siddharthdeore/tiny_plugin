#ifndef PLUGIN_HELPER_H
#define PLUGIN_HELPER_H

#pragma once

#include <string>
#include <iostream>
#include "visibility.h"

// clang-format off
#ifdef _WIN32
    #include <Windows.h>
    #define LIB_OS_SUFIX ".dll"
#else
    #include <dlfcn.h>
    #define LIB_OS_SUFIX ".so"
    #define LIB_OS_PREFIX "lib"
#endif
// clang-format on

/**
 * @brief Opens a shared library from the given path and returns the handle.
 *        Returns nullptr on failure.
 *
 * @param library_path The path of the shared library.
 * @return void* The handle to the opened library.
 */
inline void *open_library_api(const std::string &library_path);

/**
 * @brief Closes the library handle.
 *
 * @param handle The handle to the library.
 */
inline void close_library_api(void *handle);

/**
 * @brief Loads a symbol from the shared library handle and returns the symbol handle.
 *        Returns nullptr on failure.
 *
 * @param handle The handle to the library.
 * @param symbol_name The name of the symbol to load.
 * @return void* The handle to the loaded symbol.
 */
inline void *load_symbol_api(void *handle, const std::string &symbol_name);

/**
 * @brief Opens a shared library from the given path and returns the handle.
 *        Returns nullptr on failure.
 *
 * @param library_path The path of the shared library.
 * @return void* The handle to the opened library.
 */
inline void *open_library_api(const std::string &library_path)
{
    void *handle = nullptr;

#ifdef _WIN32
    handle = LoadLibrary(library_path.c_str());
#else
    // handle = dlopen(library_path.c_str(), RTLD_NOW | RTLD_LOCAL);
    handle = dlopen(library_path.c_str(), RTLD_LAZY);
#endif

    if (handle == nullptr)
    {
#ifdef _WIN32
        std::cerr << "Error loading library: " << GetLastError() << std::endl;
#else
        std::cerr << "Error loading library: " << dlerror() << std::endl;
#endif
    }

    return handle;
}

/**
 * @brief Closes the library handle.
 *
 * @param handle The handle to the library.
 */
inline void close_library_api(void *handle)
{
    if (handle)
    {
#ifdef _WIN32
        FreeLibrary(static_cast<HMODULE>(handle));
#else
        dlclose(handle);
#endif
    }
}

/**
 * @brief Loads a symbol from the shared library handle and returns the symbol handle.
 *        Returns nullptr on failure.
 *
 * @param handle The handle to the library.
 * @param symbol_name The name of the symbol to load.
 * @return void* The handle to the loaded symbol.
 */
inline void *load_symbol_api(void *handle, const std::string &symbol_name)
{
    if (handle)
    {
#ifdef _WIN32
        return GetProcAddress(static_cast<HMODULE>(handle), symbol_name.c_str());
#else
        return dlsym(handle, symbol_name.c_str());
#endif
    }
    else
    {
        return nullptr;
    }
}

#endif // PLUGIN_HELPER_H
