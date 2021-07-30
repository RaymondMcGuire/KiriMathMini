

#ifndef _KIRI_MATH_DETAIL_FUNCTORS_INL_H_
#define _KIRI_MATH_DETAIL_FUNCTORS_INL_H_

#include <kiri_math_mini/functors.h>

namespace kiri_math_mini
{

    template <typename T, typename U>
    constexpr U TypeCast<T, U>::operator()(const T &a) const
    {
        return static_cast<U>(a);
    }

    template <typename T>
    constexpr T RMinus<T>::operator()(const T &a, const T &b) const
    {
        return b - a;
    }

    template <typename T>
    constexpr T RDivides<T>::operator()(const T &a, const T &b) const
    {
        return b / a;
    }
} // namespace kiri_math_mini

#endif // _KIRI_MATH_DETAIL_FUNCTORS_INL_H_
