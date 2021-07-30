/*** 
 * @Author: Xu.WANG
 * @Date: 2021-07-30 12:22:51
 * @LastEditTime: 2021-07-30 12:47:36
 * @LastEditors: Xu.WANG
 * @Description: 
 * @FilePath: \KiriMathMini\include\kiri_math_mini\private_helpers.h
 */
/*
 * @Author: Doyub Kim  
 * @Date: 2020-03-20 16:02:26 
 * @Last Modified by:   Xu.Wang 
 * @Last Modified time: 2020-03-20 16:02:26 
 */
#ifndef _KIRI_MATH_PRIVATE_HELPERS_H_
#define _KIRI_MATH_PRIVATE_HELPERS_H_

#include <kiri_math_mini/platform.h>

#ifndef UNUSED_VARIABLE
#define UNUSED_VARIABLE(x) ((void)x)
#endif

#ifndef CLONE_W_CUSTOM_DELETER
#define CLONE_W_CUSTOM_DELETER(ClassName) \
    std::shared_ptr<ClassName>(           \
        new ClassName(*this),             \
        [](ClassName *obj) {              \
            delete obj;                   \
        });
#endif

#ifdef KIRI_MATH_WINDOWS
#include <Windows.h>
#include <exception>
#include <string>

inline void throwIfFailed(HRESULT hr)
{
    if (FAILED(hr))
    {
        throw std::exception(std::to_string(hr).c_str());
    }
}

#ifndef IF_FAILED_CLEANUP
#define IF_FAILED_CLEANUP(_hr) \
    if (FAILED(_hr))           \
    {                          \
        hr = _hr;              \
        goto Cleanup;          \
    }
#endif

#ifndef FAIL_AND_CLEANUP
#define FAIL_AND_CLEANUP(_hr) \
    {                         \
        hr = _hr;             \
        goto Cleanup;         \
    }
#endif

#endif // KIRI_MATH_WINDOWS

#endif // _KIRI_MATH_PRIVATE_HELPERS_H_
