#ifndef TINY_PLUGIN_PLUGIN_MANAGER_H
#define TINY_PLUGIN_PLUGIN_MANAGER_H

#pragma once

#include <tiny_plugin/SharedLibrary.h>
#include <unordered_map>
#include <mutex>

class PluginManager
{
private:
    std::unordered_map<std::string, std::shared_ptr<SharedLibrary>> plugins;
    std::mutex mtx;

public:
    PluginManager()
    {
    }

    void load_library(const std::string &name, const std::string &path = "")
    {
        std::lock_guard<std::mutex> lock(mtx);
        plugins[name] = std::make_shared<SharedLibrary>(name, path);
    }

    template <typename T, typename... Args>
    std::shared_ptr<T> create_instance_sptr(const std::string &name, Args... args)
    {
        std::lock_guard<std::mutex> lock(mtx);
        if (plugins.find(name) == plugins.end())
        {
            std::cerr << "Plugin not found, load library before making instance!" <<std::endl;
            return nullptr;
        }
        else
        {
            return plugins[name]->create_instance_sptr<T>(args...);
        }
    }

    ~PluginManager()
    {
    }
};

#endif // TINY_PLUGIN_PLUGIN_MANAGER_H