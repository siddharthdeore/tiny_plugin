#ifndef SHAREDLIBRARY_H
#define SHAREDLIBRARY_H

#pragma once
#include <memory>

#include "plugin_helper.h"


#define EXPORT_PLUGIN(P)                                      \
    EXPORT_SYMBOL P *plugin_constructor() { return new P(); } \
    EXPORT_SYMBOL void plugin_destructor(P *obj) { delete obj; }

class SharedLibrary
{
public:
    SharedLibrary(const std::string &library_name);

    ~SharedLibrary();

    void *get_symbol(const std::string &name) const;

    bool is_loaded() const;

    template <typename T, typename... Args>
    T *make_plugin_instance(Args... args)
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

    template <typename T, typename... Args>
    std::shared_ptr<T> make_plugin_sptr(Args... args)
    {
        T *instance = make_plugin_instance<T>(args...);

        if (instance)
        {
            auto deleter = [this](T *ptr)
            {
                destroy_plugin(ptr);
            };

            return std::shared_ptr<T>(instance, deleter);
        }
        else
        {
            return nullptr;
        }
    }

    template <typename T>
    void destroy_plugin(T *plugin_instance)
    {
        using Destructor = void (*)(T *);
        Destructor destructor = nullptr;
        destructor = reinterpret_cast<Destructor>(get_symbol("plugin_destructor"));

        if (destructor)
        {
            destructor(plugin_instance);
        }
    }

private:
    std::string library_path;
    void *handle;
};

SharedLibrary::SharedLibrary(const std::string &library_name)
{

    library_path = LIB_OS_PREFIX + library_name + LIB_OS_SUFIX;

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