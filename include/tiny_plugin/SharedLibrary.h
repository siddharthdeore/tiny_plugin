
/**
 * @file SharedLibrary.h
 * @brief This file contains the declaration of the SharedLibrary class.
 *
 * The SharedLibrary class provides functionality to load and manage shared libraries dynamically.
 * It allows retrieving symbols from the loaded library and creating instances of classes defined in the library.
 * The class also provides options to destroy the created instances.
 *
 * @author Siddharth Deore
 * @email siddharth.deore
 */

#ifndef SHAREDLIBRARY_H
#define SHAREDLIBRARY_H

#pragma once
#include <memory>

#include "plugin_helper.h"

class SharedLibrary
{
public:
    /**
     * @brief Constructs a SharedLibrary object.
     *
     * @param library_name The name of the library to load.
     * @param dir_path The directory path where the library is located. Defaults to an empty string.
     */
    SharedLibrary(const std::string &library_name, const std::string &dir_path = "");

    /**
     * @brief Destroys the SharedLibrary object.
     *
     * If the library is loaded, it is unloaded before destruction.
     */
    ~SharedLibrary();

    /**
     * @brief Retrieves a symbol from the loaded library.
     *
     * @param name The name of the symbol to retrieve.
     * @return A pointer to the symbol if found, otherwise nullptr.
     */
    void *get_symbol(const std::string &name) const;

    /**
     * @brief Checks if the library is loaded.
     *
     * @return True if the library is loaded, otherwise false.
     */
    bool is_loaded() const;

    /**
     * @brief Creates an instance of a class defined in the library using the specified constructor arguments.
     *
     * @tparam T The type of the class to create an instance of.
     * @tparam Args The types of the constructor arguments.
     * @param args The constructor arguments.
     * @return A pointer to the created instance if successful, otherwise nullptr.
     */
    template <typename T, typename... Args>
    T *create_instance_ptr(Args... args)
    {
        using Constructor = T *(*)(Args...);
        Constructor constructor = nullptr;
        constructor = reinterpret_cast<Constructor>(get_symbol("class_constructor"));

        if (constructor)
        {
            return constructor(args...);
        }
        else
        {
            return nullptr;
        }
    }
    /**
     * @brief Destroys an instance of a class created using create_instance_ptr().
     *
     * @tparam T The type of the class to destroy.
     * @param plugin_instance A pointer to the instance to destroy.
     */
    template <typename T>
    void destroy_instance(T *plugin_instance)
    {
        using Destructor = void (*)(T *);
        Destructor destructor = nullptr;
        destructor = reinterpret_cast<Destructor>(get_symbol("class_destructor"));

        if (destructor)
        {
            destructor(plugin_instance);
        }
    }

    /**
     * @brief Creates a shared pointer to an instance of a class defined in the library using the specified constructor arguments.
     *
     * @tparam T The type of the class to create an instance of.
     * @tparam Args The types of the constructor arguments.
     * @param args The constructor arguments.
     * @return A shared pointer to the created instance if successful, otherwise nullptr.
     */
    template <typename T, typename... Args>
    std::shared_ptr<T> create_instance_sptr(Args... args)
    {
        T *instance = create_instance_ptr<T>(args...);

        if (instance)
        {
            auto deleter = [this](T *ptr)
            {
                destroy_instance(ptr);
            };

            return std::shared_ptr<T>(instance, deleter);
        }
        else
        {
            return nullptr;
        }
    }
#if __cplusplus >= 201300 // c++ 14 and above
    /**
     * @brief Creates a unique pointer to an instance of a class defined in the library using the specified constructor arguments.
     *
     * @tparam T The type of the class to create an instance of.
     * @tparam Args The types of the constructor arguments.
     * @param args The constructor arguments.
     * @return A unique pointer to the created instance if successful, otherwise nullptr.
     */
    template <typename T, typename... Args>
    std::unique_ptr<T> create_instance_uptr(Args... args)
    {
        T *instance = create_instance_ptr<T>(args...);

        if (instance)
        {
            auto deleter = [this](T *ptr)
            {
                destroy_instance(ptr);
            };

            return std::unique_ptr<T>(instance, deleter);
        }
        else
        {
            return nullptr;
        }
    }
#endif

private:
    std::string library_path; ///< The path of the loaded library.
    void *handle;             ///< The handle to the loaded library.
};

/**
 * @brief Construct a new Shared Library:: Shared Library object
 * 
 * @param library_name 
 * @param dir_path 
 */
SharedLibrary::SharedLibrary(const std::string &library_name, const std::string &dir_path)
{
    library_path = dir_path + LIB_OS_PREFIX + library_name + LIB_OS_SUFIX;
    handle = open_library_api(library_path);
}

/**
 * @brief Destroys the SharedLibrary object.
 * 
 * If the library is loaded, it is unloaded before destruction.
 */
SharedLibrary::~SharedLibrary()
{
    if (is_loaded())
    {
        close_library_api(handle);
    }
}
/**
 * @brief Retrieves a symbol from the loaded library.
 * 
 * @param name 
 * @return void* 
 */
void *SharedLibrary::get_symbol(const std::string &name) const
{
    return load_symbol_api(handle, name);
}
/**
 * @brief Checks if the library is loaded.
 * 
 * @return true  if library is loaded
 * @return false if library is not loaded
 */
bool SharedLibrary::is_loaded() const
{
    return handle != nullptr;
}

#endif