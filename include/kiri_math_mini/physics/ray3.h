/*
 * @Author: Doyub Kim 
 * @Date: 2020-04-01 16:20:59 
 * @Last Modified by: Xu.Wang
 * @Last Modified time: 2020-04-01 16:23:51
 */
#ifndef _KIRI_MATH_RAY3_H_
#define _KIRI_MATH_RAY3_H_

#include <kiri_math_mini/math/vector3.h>
#include <kiri_math_mini/physics/ray.h>

namespace kiri_math_mini
{

    //!
    //! \brief      Class for 3-D ray.
    //!
    //! \tparam     T     The value type.
    //!
    template <typename T>
    class Ray<T, 3> final
    {
    public:
        static_assert(
            std::is_floating_point<T>::value,
            "Ray only can be instantiated with floating point types");

        //! The origin of the ray.
        Vector3<T> origin;

        //! The direction of the ray.
        Vector3<T> direction;

        //! Constructs an empty ray that points (1, 0, 0) from (0, 0, 0).
        Ray();

        //! Constructs a ray with given origin and riection.
        Ray(const Vector3<T> &newOrigin, const Vector3<T> &newDirection);

        //! Copy constructor.
        Ray(const Ray &other);

        //! Returns a point on the ray at distance \p t.
        Vector3<T> pointAt(T t) const;
    };

    //! Type alias for 3-D ray.
    template <typename T>
    using Ray3 = Ray<T, 3>;

    //! Float-type 3-D ray.
    typedef Ray3<float> Ray3F;

    //! Double-type 3-D ray.
    typedef Ray3<double> Ray3D;

} // namespace kiri_math_mini

#include "inl/ray3-inl.h"

#endif // _KIRI_MATH_RAY3_H_
