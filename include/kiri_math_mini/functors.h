#ifndef _KIRI_MATH_FUNCTORS_H_
#define _KIRI_MATH_FUNCTORS_H_

#include <functional>

namespace kiri_math_mini
{

    //! Type casting operator.
    template <typename T, typename U>
    struct TypeCast
    {
        constexpr U operator()(const T &a) const;
    };

    //! Reverse minus operator.
    template <typename T>
    struct RMinus
    {
        constexpr T operator()(const T &a, const T &b) const;
    };

    //! Reverse divides operator.
    template <typename T>
    struct RDivides
    {
        constexpr T operator()(const T &a, const T &b) const;
    };
} // namespace kiri_math_mini

#include "inl/functors-inl.h"

#endif // _KIRI_MATH_FUNCTORS_H_
