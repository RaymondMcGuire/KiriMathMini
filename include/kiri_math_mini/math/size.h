

#ifndef _KIRI_MATH_SIZE_H_
#define _KIRI_MATH_SIZE_H_

#include <kiri_math_mini/math/point.h>

namespace kiri_math_mini
{

    //! \brief N-D size type.
    template <size_t N>
    using Size = Point<size_t, N>;

} // namespace kiri_math_mini

// #include "inl/size-inl.h"

#endif // _KIRI_MATH_SIZE_H_
