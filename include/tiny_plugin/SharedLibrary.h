#ifndef SHAREDLIBRARY_H
#define SHAREDLIBRARY_H

#pragma once
#include <memory>

#include "plugin_helper.h"

class SharedLibrary
{
public:
    SharedLibrary(const std::string &library_name, const std::string &dir_path = "");

    ~SharedLibrary();

    void *get_symbol(const std::string &name) const;

    bool is_loaded() const;

    template <typename T, typename... Args>
    T *create_instance_ptr(Args... args)
    {
        using Constructor = T *(*)(Args...);
        Constructor constructor = nullptr;
        constructor = reinterpret_cast<Constructor>(get_symbol("plugin_constructor"));

        if (constructor)
        {
            return constructor(args...);
        }
        else
        {
            return nullptr;
        }
    }
    template <typename T>
    void destroy_instance(T *plugin_instance)
    {
        using Destructor = void (*)(T *);
        Destructor destructor = nullptr;
        destructor = reinterpret_cast<Destructor>(get_symbol("plugin_destructor"));

        if (destructor)
        {
            destructor(plugin_instance);
        }
    }

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
#if __cplusplus >= 201300
    // c++ 14 and above
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
    std::string library_path;
    void *handle;
};

SharedLibrary::SharedLibrary(const std::string &library_name, const std::string &dir_path)
{

    library_path = dir_path + LIB_OS_PREFIX + library_name + LIB_OS_SUFIX;

    handle = open_library_api(library_path);
}

SharedLibrary::~SharedLibrary()
{
    if (is_loaded())
    {
        close_library_api(handle);
    }
}

void *SharedLibrary::get_symbol(const std::string &name) const
{
    return load_symbol_api(handle, name);
}

bool SharedLibrary::is_loaded() const
{
    return handle != nullptr;
}

#endif