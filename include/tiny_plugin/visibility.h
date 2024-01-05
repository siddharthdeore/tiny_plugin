#ifndef VISIBILITY_H
#define VISIBILITY_H

#pragma once

// ref: GCC wiki https://gcc.gnu.org/wiki/Visibility
// Generic helper definitions for shared library support
#if defined(_WIN32) || defined(__CYGWIN__)
  #define SYMBOL_DLL_IMPORT __declspec(dllimport)
  #define SYMBOL_DLL_EXPORT __declspec(dllexport)
  #define SYMBOL_DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define SYMBOL_DLL_IMPORT __attribute__((visibility("default")))
    #define SYMBOL_DLL_EXPORT __attribute__((visibility("default")))
    #define SYMBOL_DLL_LOCAL  __attribute__((visibility("hidden")))
  #else
    #define SYMBOL_DLL_IMPORT
    #define SYMBOL_DLL_EXPORT
    #define SYMBOL_DLL_LOCAL
  #endif
#endif
// Now we use the generic helper definitions above to define LIB_API and LIB_LOCAL.
// LIB_API is used for the public API symbols. It either DLL imports or DLL exports (or does nothing for static build)
// LIB_LOCAL is used for non-api symbols.

 // explecitly definin  LIB_DLL, sould be done in better way
#define LIB_DLL
#define LIB_DLL_EXPORTS

#ifdef LIB_DLL // defined if LIB is compiled as a DLL
  #ifdef LIB_DLL_EXPORTS // defined if we are building the LIB DLL (instead of using it)
    #define LIB_API extern "C" SYMBOL_DLL_EXPORT
  #else
    #define LIB_API extern "C" SYMBOL_DLL_IMPORT
  #endif // LIB_DLL_EXPORTS
  #define LIB_LOCAL SYMBOL_DLL_LOCAL
#else // LIB_DLL is not defined: this means LIB is a static lib.
  #define LIB_API extern "C"
  #define LIB_LOCAL
#endif // LIB_DLL


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

// EXPORT_CLASS macro can take up to 8 arguments
#define EXPORT_CLASS(P, ...)                                     \
    LIB_API P *class_constructor(EXPAND_ARGS(__VA_ARGS__))       \
    {                                                            \
        return new P(EXPAND_OBJ(__VA_ARGS__));                   \
    }                                                            \
                                                                 \
    LIB_API void class_destructor(P *obj)                        \
    {                                                            \
        delete obj;                                              \
    }

#define EXPORT_CLASS_NOARG(P)                                    \
    LIB_API P *class_constructor()                               \
    {                                                            \
        return new P();                                          \
    }                                                            \
                                                                 \
    LIB_API void class_destructor(P *obj)                        \
    {                                                            \
        delete obj;                                              \
    }

#endif