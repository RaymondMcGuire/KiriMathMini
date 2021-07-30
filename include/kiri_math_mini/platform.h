#ifndef _KIRI_MATH_MACROS_H_
#define _KIRI_MATH_MACROS_H_

#if defined(_WIN32) || defined(_WIN64)
#define KIRI_MATH_WINDOWS
#elif defined(__APPLE__)
#define KIRI_MATH_APPLE
#ifndef KIRI_MATH_IOS
#define KIRI_MATH_MACOSX
#endif
#elif defined(linux) || defined(__linux__)
#define KIRI_MATH_LINUX
#endif

#if defined(DEBUG) || defined(_DEBUG)
#define KIRI_MATH_DEBUG_MODE
#include <cassert>
#define KIRI_MATH_ASSERT(x) assert(x)
#else
#define KIRI_MATH_ASSERT(x)
#endif

#ifdef __cplusplus
#define KIRI_MATH_NON_COPYABLE(ClassName)  \
    ClassName(const ClassName &) = delete; \
    ClassName &operator=(const ClassName &) = delete;
#endif

#ifdef __cplusplus
#include <stdexcept>
#define KIRI_MATH_THROW_INVALID_ARG_IF(expression) \
    if (expression)                                \
    {                                              \
        throw std::invalid_argument(#expression);  \
    }
#define KIRI_MATH_THROW_INVALID_ARG_WITH_MESSAGE_IF(expression, message) \
    if (expression)                                                      \
    {                                                                    \
        throw std::invalid_argument(message);                            \
    }
#endif

#ifdef KIRI_MATH_WINDOWS
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

#define KIRI_MATH_DIAG_STR(s) #s
#define KIRI_DIAG_JOINSTR(x, y) KIRI_MATH_DIAG_STR(x##y)
#ifdef _MSC_VER
#define KIRI_MATH_DIAG_DO_PRAGMA(x) __pragma(#x)
#define KIRI_MATH_DIAG_PRAGMA(compiler, x) KIRI_MATH_DIAG_DO_PRAGMA(warning(x))
#else
#define KIRI_MATH_DIAG_DO_PRAGMA(x) _Pragma(#x)
#define KIRI_MATH_DIAG_PRAGMA(compiler, x) KIRI_MATH_DIAG_DO_PRAGMA(compiler diagnostic x)
#endif
#if defined(__clang__)
#define KIRI_MATH_DISABLE_CLANG_WARNING(clang_option) \
    KIRI_MATH_DIAG_PRAGMA(clang, push)                \
    KIRI_MATH_DIAG_PRAGMA(clang, ignored KIRI_DIAG_JOINSTR(-W, clang_option))
#define KIRI_MATH_ENABLE_CLANG_WARNING(clang_option) KIRI_MATH_DIAG_PRAGMA(clang, pop)
#define KIRI_MATH_DISABLE_MSVC_WARNING(gcc_option)
#define KIRI_MATH_ENABLE_MSVC_WARNING(gcc_option)
#define KIRI_MATH_DISABLE_GCC_WARNING(gcc_option)
#define KIRI_MATH_ENABLE_GCC_WARNING(gcc_option)
#elif defined(_MSC_VER)
#define KIRI_MATH_DISABLE_CLANG_WARNING(gcc_option)
#define KIRI_MATH_ENABLE_CLANG_WARNING(gcc_option)
#define KIRI_MATH_DISABLE_MSVC_WARNING(msvc_errorcode) \
    KIRI_MATH_DIAG_PRAGMA(msvc, push)                  \
    KIRI_MATH_DIAG_DO_PRAGMA(warning(disable           \
                                     :##msvc_errorcode))
#define KIRI_MATH_ENABLE_MSVC_WARNING(msvc_errorcode) KIRI_MATH_DIAG_PRAGMA(msvc, pop)
#define KIRI_MATH_DISABLE_GCC_WARNING(gcc_option)
#define KIRI_MATH_ENABLE_GCC_WARNING(gcc_option)
#elif defined(__GNUC__)
#if ((__GNUC__ * 100) + __GNUC_MINOR__) >= 406
#define KIRI_MATH_DISABLE_CLANG_WARNING(gcc_option)
#define KIRI_MATH_ENABLE_CLANG_WARNING(gcc_option)
#define KIRI_MATH_DISABLE_MSVC_WARNING(gcc_option)
#define KIRI_MATH_ENABLE_MSVC_WARNING(gcc_option)
#define KIRI_MATH_DISABLE_GCC_WARNING(gcc_option) \
    KIRI_MATH_DIAG_PRAGMA(GCC, push)              \
    KIRI_MATH_DIAG_PRAGMA(GCC, ignored KIRI_DIAG_JOINSTR(-W, gcc_option))
#define KIRI_MATH_ENABLE_GCC_WARNING(gcc_option) KIRI_MATH_DIAG_PRAGMA(GCC, pop)
#else
#define KIRI_MATH_DISABLE_CLANG_WARNING(gcc_option)
#define KIRI_MATH_ENABLE_CLANG_WARNING(gcc_option)
#define KIRI_MATH_DISABLE_MSVC_WARNING(gcc_option)
#define KIRI_MATH_ENABLE_MSVC_WARNING(gcc_option)
#define KIRI_MATH_DISABLE_GCC_WARNING(gcc_option) \
    KIRI_MATH_DIAG_PRAGMA(GCC, ignored KIRI_DIAG_JOINSTR(-W, gcc_option))
#define KIRI_MATH_ENABLE_GCC_WARNING(gcc_option) \
    KIRI_MATH_DIAG_PRAGMA(GCC, warning KIRI_DIAG_JOINSTR(-W, gcc_option))
#endif
#endif

#endif // _KIRI_MATH_MACROS_H_
