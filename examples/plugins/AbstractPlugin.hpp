#ifndef ABSTRACT_PLUGIN_H
#define ABSTRACT_PLUGIN_H

#pragma once

class AbstractPlugin
{
private:
    /* data */
public:
    template <typename... Args>
    AbstractPlugin(Args... args) {}
    ~AbstractPlugin() {}
};

#ifdef __GNUG__
#include <cstdlib>
#include <memory>
#include <cxxabi.h>

struct handle
{
    char *p;
    handle(char *ptr) : p(ptr) {}
    ~handle() { std::free(p); }
};

std::string demangle(const char *name)
{

    int status = -4; // some arbitrary value to eliminate the compiler warning

    handle result(abi::__cxa_demangle(name, NULL, NULL, &status));

    return (status == 0) ? result.p : name;
}

#else

// does nothing if not g++
std::string demangle(const char *name)
{
    return name;
}

#endif

#define Type2Name(T) demangle(typeid(T).name())

#endif