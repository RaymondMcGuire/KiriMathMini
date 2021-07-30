#ifndef _KIRI_MATH_DETAIL_BOUNDING_BOX2_INL_H_
#define _KIRI_MATH_DETAIL_BOUNDING_BOX2_INL_H_

#include <algorithm>
#include <limits>
#include <utility>

namespace kiri_math_mini
{

    template <typename T>
    BoundingBox<T, 2>::BoundingBox()
    {
        reset();
    }

    template <typename T>
    BoundingBox<T, 2>::BoundingBox(const Vector2<T> &point1,
                                   const Vector2<T> &point2)
    {
        LowestPoint.x = std::min(point1.x, point2.x);
        LowestPoint.y = std::min(point1.y, point2.y);
        HighestPoint.x = std::max(point1.x, point2.x);
        HighestPoint.y = std::max(point1.y, point2.y);
    }

    template <typename T>
    BoundingBox<T, 2>::BoundingBox(const BoundingBox &other)
        : LowestPoint(other.LowestPoint), HighestPoint(other.HighestPoint) {}

    template <typename T>
    T BoundingBox<T, 2>::width() const
    {
        return HighestPoint.x - LowestPoint.x;
    }

    template <typename T>
    T BoundingBox<T, 2>::height() const
    {
        return HighestPoint.y - LowestPoint.y;
    }

    template <typename T>
    T BoundingBox<T, 2>::length(size_t axis)
    {
        return HighestPoint[axis] - LowestPoint[axis];
    }

    template <typename T>
    bool BoundingBox<T, 2>::overlaps(const BoundingBox &other) const
    {
        if (HighestPoint.x < other.LowestPoint.x ||
            LowestPoint.x > other.HighestPoint.x)
        {
            return false;
        }

        if (HighestPoint.y < other.LowestPoint.y ||
            LowestPoint.y > other.HighestPoint.y)
        {
            return false;
        }

        return true;
    }

    template <typename T>
    bool BoundingBox<T, 2>::contains(const Vector2<T> &point) const
    {
        if (HighestPoint.x < point.x || LowestPoint.x > point.x)
        {
            return false;
        }

        if (HighestPoint.y < point.y || LowestPoint.y > point.y)
        {
            return false;
        }

        return true;
    }

    template <typename T>
    bool BoundingBox<T, 2>::contains(const BoundingBox &other) const
    {
        return !(other.LowestPoint.x > HighestPoint.x || other.HighestPoint.x < LowestPoint.x || other.HighestPoint.y > LowestPoint.y || other.LowestPoint.y < HighestPoint.y);
    }

    template <typename T>
    bool BoundingBox<T, 2>::intersects(const Ray2<T> &ray) const
    {
        T tMin = 0;
        T tMax = std::numeric_limits<T>::max();

        const Vector2<T> &rayInvDir = ray.direction.rdiv(1);

        for (int i = 0; i < 2; ++i)
        {
            T tNear = (LowestPoint[i] - ray.origin[i]) * rayInvDir[i];
            T tFar = (HighestPoint[i] - ray.origin[i]) * rayInvDir[i];

            if (tNear > tFar)
                std::swap(tNear, tFar);
            tMin = tNear > tMin ? tNear : tMin;
            tMax = tFar < tMax ? tFar : tMax;

            if (tMin > tMax)
                return false;
        }

        return true;
    }

    template <typename T>
    BoundingBoxRayIntersection2<T> BoundingBox<T, 2>::closestIntersection(
        const Ray2<T> &ray) const
    {
        BoundingBoxRayIntersection2<T> intersection;

        T tMin = 0;
        T tMax = std::numeric_limits<T>::max();

        const Vector2<T> &rayInvDir = ray.direction.rdiv(1);

        for (int i = 0; i < 2; ++i)
        {
            T tNear = (LowestPoint[i] - ray.origin[i]) * rayInvDir[i];
            T tFar = (HighestPoint[i] - ray.origin[i]) * rayInvDir[i];

            if (tNear > tFar)
            {
                std::swap(tNear, tFar);
            }

            tMin = std::max(tNear, tMin);
            tMax = std::min(tFar, tMax);

            if (tMin > tMax)
            {
                intersection.isIntersecting = false;
                return intersection;
            }
        }

        intersection.isIntersecting = true;

        if (contains(ray.origin))
        {
            intersection.tNear = tMax;
            intersection.tFar = std::numeric_limits<T>::max();
        }
        else
        {
            intersection.tNear = tMin;
            intersection.tFar = tMax;
        }

        return intersection;
    }

    template <typename T>
    Vector2<T> BoundingBox<T, 2>::midPoint() const
    {
        return (HighestPoint + LowestPoint) / static_cast<T>(2);
    }

    template <typename T>
    T BoundingBox<T, 2>::diagonalLength() const
    {
        return (HighestPoint - LowestPoint).length();
    }

    template <typename T>
    T BoundingBox<T, 2>::diagonalLengthSquared() const
    {
        return (HighestPoint - LowestPoint).lengthSquared();
    }

    template <typename T>
    void BoundingBox<T, 2>::reset()
    {
        LowestPoint.x = std::numeric_limits<T>::max();
        LowestPoint.y = std::numeric_limits<T>::max();
        HighestPoint.x = -std::numeric_limits<T>::max();
        HighestPoint.y = -std::numeric_limits<T>::max();
    }

    template <typename T>
    void BoundingBox<T, 2>::merge(const Vector2<T> &point)
    {
        LowestPoint.x = std::min(LowestPoint.x, point.x);
        LowestPoint.y = std::min(LowestPoint.y, point.y);
        HighestPoint.x = std::max(HighestPoint.x, point.x);
        HighestPoint.y = std::max(HighestPoint.y, point.y);
    }

    template <typename T>
    void BoundingBox<T, 2>::merge(const BoundingBox &other)
    {
        LowestPoint.x = std::min(LowestPoint.x, other.LowestPoint.x);
        LowestPoint.y = std::min(LowestPoint.y, other.LowestPoint.y);
        HighestPoint.x = std::max(HighestPoint.x, other.HighestPoint.x);
        HighestPoint.y = std::max(HighestPoint.y, other.HighestPoint.y);
    }

    template <typename T>
    void BoundingBox<T, 2>::expand(T delta)
    {
        LowestPoint -= delta;
        HighestPoint += delta;
    }

    template <typename T>
    Vector2<T> BoundingBox<T, 2>::corner(size_t idx) const
    {
        static const T h = static_cast<T>(1) / 2;
        static const Vector2<T> offset[4] = {
            {-h, -h}, {+h, -h}, {-h, +h}, {+h, +h}};

        return Vector2<T>(width(), height()) * offset[idx] + midPoint();
    }

    template <typename T>
    Vector2<T> BoundingBox<T, 2>::clamp(const Vector2<T> &pt) const
    {
        return ::kiri_math_mini::clamp(pt, LowestPoint, HighestPoint);
    }

    template <typename T>
    bool BoundingBox<T, 2>::isEmpty() const
    {
        return (LowestPoint.x >= HighestPoint.x || LowestPoint.y >= HighestPoint.y);
    }

} // namespace kiri_math_mini

#endif // _KIRI_MATH_DETAIL_BOUNDING_BOX2_INL_H_
