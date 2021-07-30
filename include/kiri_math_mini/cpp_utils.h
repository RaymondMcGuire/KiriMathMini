#ifndef _KIRI_MATH_CPP_UTILS_H_
#define _KIRI_MATH_CPP_UTILS_H_

#include <algorithm>

namespace kiri_math_mini
{

    template <class ForwardIt, class T, class Compare = std::less<T>>
    ForwardIt binaryFind(ForwardIt first, ForwardIt last, const T &value,
                         Compare comp = {});
} // namespace kiri_math_mini

#include "inl/cpp_utils-inl.h"

#endif // _KIRI_MATH_CPP_UTILS_H_
