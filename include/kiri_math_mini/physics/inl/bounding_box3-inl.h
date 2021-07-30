/*
 * @Author: Doyub Kim 
 * @Date: 2020-04-01 16:55:36 
 * @Last Modified by:   Xu.Wang 
 * @Last Modified time: 2020-04-01 16:55:36 
 */
#ifndef _KIRI_MATH_DETAIL_BOUNDING_BOX3_INL_H_
#define _KIRI_MATH_DETAIL_BOUNDING_BOX3_INL_H_

#include <algorithm>
#include <limits>
#include <utility>

namespace kiri_math_mini
{

    template <typename T>
    BoundingBox<T, 3>::BoundingBox()
    {
        reset();
    }

    template <typename T>
    BoundingBox<T, 3>::BoundingBox(const Vector3<T> &point1,
                                   const Vector3<T> &point2)
    {
        LowestPoint.x = std::min(point1.x, point2.x);
        LowestPoint.y = std::min(point1.y, point2.y);
        LowestPoint.z = std::min(point1.z, point2.z);
        HighestPoint.x = std::max(point1.x, point2.x);
        HighestPoint.y = std::max(point1.y, point2.y);
        HighestPoint.z = std::max(point1.z, point2.z);
    }

    template <typename T>
    BoundingBox<T, 3>::BoundingBox(const BoundingBox &other)
        : LowestPoint(other.LowestPoint), HighestPoint(other.HighestPoint) {}

    template <typename T>
    T BoundingBox<T, 3>::width() const
    {
        return HighestPoint.x - LowestPoint.x;
    }

    template <typename T>
    T BoundingBox<T, 3>::height() const
    {
        return HighestPoint.y - LowestPoint.y;
    }

    template <typename T>
    T BoundingBox<T, 3>::depth() const
    {
        return HighestPoint.z - LowestPoint.z;
    }

    template <typename T>
    T BoundingBox<T, 3>::length(size_t axis)
    {
        return HighestPoint[axis] - LowestPoint[axis];
    }

    template <typename T>
    void BoundingBox<T, 3>::setBboxWithCenter(Vector3<T> center, T radius)
    {
        Vector3<T> point1(center.add(radius));
        Vector3<T> point2(center.sub(radius));
        LowestPoint.x = std::min(point1.x, point2.x);
        LowestPoint.y = std::min(point1.y, point2.y);
        LowestPoint.z = std::min(point1.z, point2.z);
        HighestPoint.x = std::max(point1.x, point2.x);
        HighestPoint.y = std::max(point1.y, point2.y);
        HighestPoint.z = std::max(point1.z, point2.z);
    }

    template <typename T>
    void BoundingBox<T, 3>::setBboxWithCenter(Vector3<T> center, T longSide, T shortSide)
    {
        Vector3<T> point1(center.add(Vector3<T>(longSide / 2, shortSide / 2, shortSide / 2)));
        Vector3<T> point2(center.sub(Vector3<T>(longSide / 2, shortSide / 2, shortSide / 2)));
        LowestPoint.x = std::min(point1.x, point2.x);
        LowestPoint.y = std::min(point1.y, point2.y);
        LowestPoint.z = std::min(point1.z, point2.z);
        HighestPoint.x = std::max(point1.x, point2.x);
        HighestPoint.y = std::max(point1.y, point2.y);
        HighestPoint.z = std::max(point1.z, point2.z);
    }

    template <typename T>
    void BoundingBox<T, 3>::setBboxWithCenter(Vector3<T> center, T xSide, T ySide, T zSide)
    {
        Vector3<T> point1(center.add(Vector3<T>(xSide / 2, ySide / 2, zSide / 2)));
        Vector3<T> point2(center.sub(Vector3<T>(xSide / 2, ySide / 2, zSide / 2)));
        LowestPoint.x = std::min(point1.x, point2.x);
        LowestPoint.y = std::min(point1.y, point2.y);
        LowestPoint.z = std::min(point1.z, point2.z);
        HighestPoint.x = std::max(point1.x, point2.x);
        HighestPoint.y = std::max(point1.y, point2.y);
        HighestPoint.z = std::max(point1.z, point2.z);
    }

    template <typename T>
    bool BoundingBox<T, 3>::overlaps(const BoundingBox &other) const
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

        if (HighestPoint.z < other.LowestPoint.z ||
            LowestPoint.z > other.HighestPoint.z)
        {
            return false;
        }

        return true;
    }

    template <typename T>
    bool BoundingBox<T, 3>::contains(const Vector3<T> &point) const
    {
        if (HighestPoint.x < point.x || LowestPoint.x > point.x)
        {
            return false;
        }

        if (HighestPoint.y < point.y || LowestPoint.y > point.y)
        {
            return false;
        }

        if (HighestPoint.z < point.z || LowestPoint.z > point.z)
        {
            return false;
        }

        return true;
    }

    template <typename T>
    bool BoundingBox<T, 3>::intersects(const Ray3<T> &ray) const
    {
        T tMin = 0;
        T tMax = std::numeric_limits<T>::max();
        const Vector3<T> &rayInvDir = ray.direction.rdiv(1);

        for (int i = 0; i < 3; ++i)
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
    BoundingBoxRayIntersection3<T> BoundingBox<T, 3>::closestIntersection(
        const Ray3<T> &ray) const
    {
        BoundingBoxRayIntersection3<T> intersection;

        T tMin = 0;
        T tMax = std::numeric_limits<T>::max();
        const Vector3<T> &rayInvDir = ray.direction.rdiv(1);

        for (int i = 0; i < 3; ++i)
        {
            T tNear = (LowestPoint[i] - ray.origin[i]) * rayInvDir[i];
            T tFar = (HighestPoint[i] - ray.origin[i]) * rayInvDir[i];

            if (tNear > tFar)
                std::swap(tNear, tFar);
            tMin = tNear > tMin ? tNear : tMin;
            tMax = tFar < tMax ? tFar : tMax;

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
    Vector3<T> BoundingBox<T, 3>::midPoint() const
    {
        return (HighestPoint + LowestPoint) / static_cast<T>(2);
    }

    template <typename T>
    T BoundingBox<T, 3>::diagonalLength() const
    {
        return (HighestPoint - LowestPoint).length();
    }

    template <typename T>
    T BoundingBox<T, 3>::diagonalLengthSquared() const
    {
        return (HighestPoint - LowestPoint).lengthSquared();
    }

    template <typename T>
    void BoundingBox<T, 3>::reset()
    {
        LowestPoint.x = std::numeric_limits<T>::max();
        LowestPoint.y = std::numeric_limits<T>::max();
        LowestPoint.z = std::numeric_limits<T>::max();
        HighestPoint.x = -std::numeric_limits<T>::max();
        HighestPoint.y = -std::numeric_limits<T>::max();
        HighestPoint.z = -std::numeric_limits<T>::max();
    }

    template <typename T>
    void BoundingBox<T, 3>::merge(const Vector3<T> &point)
    {
        LowestPoint.x = std::min(LowestPoint.x, point.x);
        LowestPoint.y = std::min(LowestPoint.y, point.y);
        LowestPoint.z = std::min(LowestPoint.z, point.z);
        HighestPoint.x = std::max(HighestPoint.x, point.x);
        HighestPoint.y = std::max(HighestPoint.y, point.y);
        HighestPoint.z = std::max(HighestPoint.z, point.z);
    }

    template <typename T>
    void BoundingBox<T, 3>::merge(const BoundingBox &other)
    {
        LowestPoint.x = std::min(LowestPoint.x, other.LowestPoint.x);
        LowestPoint.y = std::min(LowestPoint.y, other.LowestPoint.y);
        LowestPoint.z = std::min(LowestPoint.z, other.LowestPoint.z);
        HighestPoint.x = std::max(HighestPoint.x, other.HighestPoint.x);
        HighestPoint.y = std::max(HighestPoint.y, other.HighestPoint.y);
        HighestPoint.z = std::max(HighestPoint.z, other.HighestPoint.z);
    }

    template <typename T>
    void BoundingBox<T, 3>::expand(T delta)
    {
        LowestPoint -= delta;
        HighestPoint += delta;
    }

    template <typename T>
    Vector3<T> BoundingBox<T, 3>::corner(size_t idx) const
    {
        static const T h = static_cast<T>(1) / 2;
        static const Vector3<T> offset[8] = {
            {-h, -h, -h}, {+h, -h, -h}, {-h, +h, -h}, {+h, +h, -h}, {-h, -h, +h}, {+h, -h, +h}, {-h, +h, +h}, {+h, +h, +h}};

        return Vector3<T>(width(), height(), depth()) * offset[idx] + midPoint();
    }

    template <typename T>
    Vector3<T> BoundingBox<T, 3>::clamp(const Vector3<T> &pt) const
    {
        return ::kiri_math_mini::clamp(pt, LowestPoint, HighestPoint);
    }

    template <typename T>
    bool BoundingBox<T, 3>::isEmpty() const
    {
        return (LowestPoint.x >= HighestPoint.x || LowestPoint.y >= HighestPoint.y ||
                LowestPoint.z >= HighestPoint.z);
    }

} // namespace kiri_math_mini

#endif // _KIRI_MATH_DETAIL_BOUNDING_BOX3_INL_H_
