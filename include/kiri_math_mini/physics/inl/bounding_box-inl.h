#ifndef _KIRI_MATH_DETAIL_BOUNDING_BOX_INL_H_
#define _KIRI_MATH_DETAIL_BOUNDING_BOX_INL_H_

#include <kiri_math_mini/math/math_utils.h>
#include <algorithm>
#include <limits>

namespace kiri_math_mini
{

    template <typename T, size_t N>
    BoundingBox<T, N>::BoundingBox()
    {
        reset();
    }

    template <typename T, size_t N>
    BoundingBox<T, N>::BoundingBox(
        const VectorType &point1, const VectorType &point2)
    {
        for (size_t i = 0; i < N; ++i)
        {
            LowestPoint[i] = std::min(point1[i], point2[i]);
            HighestPoint[i] = std::max(point1[i], point2[i]);
        }
    }

    template <typename T, size_t N>
    BoundingBox<T, N>::BoundingBox(const BoundingBox &other) : LowestPoint(other.LowestPoint),
                                                               HighestPoint(other.HighestPoint)
    {
    }

    template <typename T, size_t N>
    bool BoundingBox<T, N>::overlaps(const BoundingBox &other) const
    {
        for (size_t i = 0; i < N; ++i)
        {
            if (HighestPoint[i] < other.LowestPoint[i] || LowestPoint[i] > other.HighestPoint[i])
            {
                return false;
            }
        }

        return true;
    }

    template <typename T, size_t N>
    bool BoundingBox<T, N>::contains(const VectorType &point) const
    {
        for (size_t i = 0; i < N; ++i)
        {
            if (HighestPoint[i] < point[i] || LowestPoint[i] > point[i])
            {
                return false;
            }
        }

        return true;
    }

    template <typename T, size_t N>
    Vector<T, N> BoundingBox<T, N>::midPoint() const
    {
        Vector<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = (HighestPoint[i] + LowestPoint[i]) / 2;
        }
        return result;
    }

    template <typename T, size_t N>
    T BoundingBox<T, N>::diagonalLength() const
    {
        T result = 0;
        for (size_t i = 0; i < N; ++i)
        {
            result += square(HighestPoint[i] - LowestPoint[i]);
        }
        return std::sqrt(result);
    }

    template <typename T, size_t N>
    T BoundingBox<T, N>::diagonalLengthSquared() const
    {
        T result = 0;
        for (size_t i = 0; i < N; ++i)
        {
            result += square(HighestPoint[i] - LowestPoint[i]);
        }
        return result;
    }

    template <typename T, size_t N>
    void BoundingBox<T, N>::reset()
    {
        for (size_t i = 0; i < N; ++i)
        {
            LowestPoint[i] = std::numeric_limits<T>::max();
            HighestPoint[i] = -std::numeric_limits<T>::max();
        }
    }

    template <typename T, size_t N>
    void BoundingBox<T, N>::merge(const VectorType &point)
    {
        for (size_t i = 0; i < N; ++i)
        {
            LowestPoint[i] = std::min(LowestPoint[i], point[i]);
            HighestPoint[i] = std::max(HighestPoint[i], point[i]);
        }
    }

    template <typename T, size_t N>
    void BoundingBox<T, N>::merge(const BoundingBox &other)
    {
        for (size_t i = 0; i < N; ++i)
        {
            LowestPoint[i] = std::min(LowestPoint[i], other.LowestPoint[i]);
            HighestPoint[i] = std::max(HighestPoint[i], other.HighestPoint[i]);
        }
    }

    template <typename T, size_t N>
    void BoundingBox<T, N>::expand(T delta)
    {
        for (size_t i = 0; i < N; ++i)
        {
            LowestPoint[i] -= delta;
            HighestPoint[i] += delta;
        }
    }

} // namespace kiri_math_mini

#endif // _KIRI_MATH_DETAIL_BOUNDING_BOX_INL_H_
