/*
 * @Author: Doyub Kim 
 * @Date: 2020-04-01 16:23:59 
 * @Last Modified by:   Xu.Wang 
 * @Last Modified time: 2020-04-01 16:23:59 
 */
#ifndef _KIRI_MATH_DETAIL_RAY3_INL_H_
#define _KIRI_MATH_DETAIL_RAY3_INL_H_

namespace kiri_math_mini
{

    template <typename T>
    Ray<T, 3>::Ray() : Ray(Vector3<T>(), Vector3<T>(1, 0, 0))
    {
    }

    template <typename T>
    Ray<T, 3>::Ray(
        const Vector3<T> &newOrigin,
        const Vector3<T> &newDirection) : origin(newOrigin),
                                          direction(newDirection.normalized())
    {
    }

    template <typename T>
    Ray<T, 3>::Ray(const Ray &other) : origin(other.origin),
                                       direction(other.direction)
    {
    }

    template <typename T>
    Vector3<T> Ray<T, 3>::pointAt(T t) const
    {
        return origin + t * direction;
    }

} // namespace kiri_math_mini

#endif // _KIRI_MATH_DETAIL_RAY3_INL_H_
