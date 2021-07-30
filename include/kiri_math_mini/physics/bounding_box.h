#ifndef _KIRI_MATH_BOUNDING_BOX_H_
#define _KIRI_MATH_BOUNDING_BOX_H_

#include <kiri_math_mini/math/vector.h>

namespace kiri_math_mini
{

    //!
    //! \brief Generic N-D axis-aligned bounding box class.
    //!
    //! \tparam T - Real number type.
    //! \tparam N - Dimension.
    //!
    template <typename T, size_t N>
    class BoundingBox
    {
    public:
        static_assert(
            N > 0, "Size of static-sized box should be greater than zero.");

        typedef Vector<T, N> VectorType;

        //! Lower corner of the bounding box.
        VectorType LowestPoint;

        //! Upper corner of the bounding box.
        VectorType HighestPoint;

        //! Default constructor.
        BoundingBox();

        //! Constructs a box that tightly covers two points.
        BoundingBox(const VectorType &point1, const VectorType &point2);

        //! Constructs a box with other box instance.
        BoundingBox(const BoundingBox &other);

        //! Returns true of this box and other box overlaps.
        bool overlaps(const BoundingBox &other) const;

        //! Returns true if the input point is inside of this box.
        bool contains(const VectorType &point) const;

        //! Returns the mid-point of this box.
        VectorType midPoint() const;

        //! Returns diagonal length of this box.
        T diagonalLength() const;

        //! Returns squared diagonal length of this box.
        T diagonalLengthSquared() const;

        //! Resets this box to initial state (min=infinite, max=-infinite).
        void reset();

        //! Merges this and other point.
        void merge(const VectorType &point);

        //! Merges this and other boxes.
        void merge(const BoundingBox &other);

        //! Expands this box by given delta to all direction.
        //! If the width of the box was x, expand(y) will result a box with
        //! x+y+y width.
        void expand(T delta);
    };

} // namespace kiri_math_mini

#include "inl/bounding_box-inl.h"

#endif // _KIRI_MATH_BOUNDING_BOX_H_
