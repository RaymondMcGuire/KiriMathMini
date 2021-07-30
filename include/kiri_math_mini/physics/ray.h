#ifndef _KIRI_MATH_RAY_H_
#define _KIRI_MATH_RAY_H_

#include <kiri_math_mini/math/vector.h>

namespace kiri_math_mini
{

    //!
    //! \brief      Class for ray.
    //!
    //! \tparam     T     The value type.
    //! \tparam     N     The dimension.
    //!
    template <typename T, size_t N>
    class Ray
    {
        static_assert(N != 2 && N != 3, "Not implemented.");
        static_assert(
            std::is_floating_point<T>::value,
            "Ray only can be instantiated with floating point types");
    };

} // namespace kiri_math_mini

#endif // _KIRI_MATH_RAY_H_
