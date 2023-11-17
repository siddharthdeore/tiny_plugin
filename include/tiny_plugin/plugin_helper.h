#ifndef PLUGIN_HELPER_H
#define PLUGIN_HELPER_H

#pragma once

#include <string>
#include <iostream>
#include <tiny_plugin/visibility.h>

// clang-format off
#ifdef _WIN32
    #include <Windows.h>
    #define LIB_OS_SUFIX ".dll"
    #define LIB_OS_PRIFIX ""
#else
    #include <dlfcn.h>
    #define LIB_OS_SUFIX ".so"
    #define LIB_OS_PREFIX "lib"
#endif
// clang-format on

/**
 * @brief opens shared library from given path and return handle
 * returns nullptr on failure
 *
 * @param library_path
 * @return void*
 */
void *open_library_api(const std::string &library_path);

/**
 * @brief close library handle
 *
 * @param handle
 */
void close_library_api(void *handle);

/**
 * @brief loads symbol from shared library handle and returns symbol handle
 * returns nullptr on failure
 *
 * @param library_path
 * @return void*
 */
void *load_symbol_api(void *handle, const std::string &symbol_name);

void *open_library_api(const std::string &library_path)
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

void close_library_api(void *handle)
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

void *load_symbol_api(void *handle, const std::string &symbol_name)
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
