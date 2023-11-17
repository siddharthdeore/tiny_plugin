#ifndef VISIBILITY_H
#define VISIBILITY_H
#include <utility> // std::forward
#pragma once

// clang-format off
#if defined(_WIN32)
    #ifdef EXPORT_PLUGIN_DLL
        #define EXPORT_SYMBOL __declspec(dllexport) extern "C"
    #else
        #define EXPORT_SYMBOL __declspec(dllimport) extern "C"
    #endif
#elif defined(__GNUC__) || defined(__clang__)
    #define EXPORT_SYMBOL extern "C" __attribute__((visibility("default")))
    #define EXPORT_SYMBOL extern "C" __attribute__((visibility("default")))
#elif defined(__MINGW32__) || defined(__MINGW64__)
    #define EXPORT_SYMBOL extern "C" __declspec(dllexport) extern "C"
#elif defined(__CYGWIN__)
    #define EXPORT_SYMBOL extern "C" __declspec(dllexport) extern "C"
#elif defined(__APPLE__)
    #include <TargetConditionals.h>
    #if TARGET_OS_MAC
        #define EXPORT_SYMBOL extern "C" __attribute__((visibility("default")))
    #endif
#elif defined(__sun) && defined(__SVR4)
    #define EXPORT_SYMBOL extern "C" __global
#else
    #error "Unsupported compiler/platform"
#endif

template <typename P, typename... Args>
P *create_plugin_instance(const Args&... args)
{
    return new P(args...);
}

template <typename P>
P *create_plugin_instance()
{
    return new P;
}

/* macro to count arguments  from 0 to 9 */
#define _GET_NTH_ARG(_1, _2, _3, _4, _5, _6, _7, _8, _9, N, ...) N
#define COUNT_VARARGS(...) _GET_NTH_ARG("ignored", ##__VA_ARGS__, 9, 8, 7, 6, 4, 3, 2, 1, 0)

#define EXPAND_ARGS(...) CAT(COUNT_VARARGS(__VA_ARGS__))(__VA_ARGS__)
#define CAT(N) DOG(N)
#define DOG(N) EXPAND_ARGS ## N

#define EXPAND_ARGS0(A) 
#define EXPAND_ARGS1(A, ...) A arg_1 EXPAND_ARGS0(__VA_ARGS__)
#define EXPAND_ARGS2(A, ...) A arg_2, EXPAND_ARGS1(__VA_ARGS__)
#define EXPAND_ARGS3(A, ...) A arg_3, EXPAND_ARGS2(__VA_ARGS__)
#define EXPAND_ARGS4(A, ...) A arg_4, EXPAND_ARGS3(__VA_ARGS__)
#define EXPAND_ARGS5(A, ...) A arg_5, EXPAND_ARGS4(__VA_ARGS__)
#define EXPAND_ARGS6(A, ...) A arg_6, EXPAND_ARGS5(__VA_ARGS__)
#define EXPAND_ARGS7(A, ...) A arg_7, EXPAND_ARGS6(__VA_ARGS__)
#define EXPAND_ARGS8(A, ...) A arg_8, EXPAND_ARGS7(__VA_ARGS__)
#define EXPAND_ARGS9(A, ...) A arg_9, EXPAND_ARGS8(__VA_ARGS__)

#define EXPAND_OBJ(...) SHARK(COUNT_VARARGS(__VA_ARGS__))(__VA_ARGS__)
#define SHARK(N) FISH(N)
#define FISH(N) EXPAND_OB ## N
#define EXPAND_OB0(A)
#define EXPAND_OB1(A, ...) arg_1 EXPAND_OB0(__VA_ARGS__)
#define EXPAND_OB2(A, ...) arg_2, EXPAND_OB1(__VA_ARGS__)
#define EXPAND_OB3(A, ...) arg_3, EXPAND_OB2(__VA_ARGS__)
#define EXPAND_OB4(A, ...) arg_4, EXPAND_OB3(__VA_ARGS__)
#define EXPAND_OB5(A, ...) arg_5, EXPAND_OB4(__VA_ARGS__)
#define EXPAND_OB6(A, ...) arg_6, EXPAND_OB5(__VA_ARGS__)
#define EXPAND_OB7(A, ...) arg_7, EXPAND_OB6(__VA_ARGS__)
#define EXPAND_OB8(A, ...) arg_8, EXPAND_OB7(__VA_ARGS__)
#define EXPAND_OB9(A, ...) arg_9, EXPAND_OB8(__VA_ARGS__)

// clang-format on

// EXPORT_PLUGIN macro can take up to 8 arguments
#define EXPORT_PLUGIN(P, ...)                                     \
    EXPORT_SYMBOL P *plugin_constructor(EXPAND_ARGS(__VA_ARGS__)) \
    {                                                             \
        return new P(EXPAND_OBJ(__VA_ARGS__));                    \
    }                                                             \
                                                                  \
    EXPORT_SYMBOL void plugin_destructor(P *obj)                  \
    {                                                             \
        delete obj;                                               \
    }

#endif