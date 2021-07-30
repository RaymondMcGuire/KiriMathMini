/*
 * @Author: Doyub Kim 
 * @Last Modified by:   Xu.Wang 
 * @Last Modified time: 2019-12-14 02:27:36 
 */
#ifndef _KIRI_MATH_ARRAY_H_
#define _KIRI_MATH_ARRAY_H_

#include <kiri_math_mini/math/size.h>

namespace kiri_math_mini
{

    //!
    //! \brief Generic N-dimensional array class interface.
    //!
    //! This class provides generic template class for N-dimensional array where N
    //! must be either 1, 2 or 3. This particular class exists to provide generic
    //! interface for 1, 2 or 3 dimensional arrays using template specialization
    //! only, but it cannot create any instance by itself.
    //!
    //! \tparam T - Real number type.
    //! \tparam N - Dimension.
    //!
    template <typename T, size_t N>
    class Array final
    {
    public:
        static_assert(
            N < 1 || N > 3, "Not implemented - N should be either 1, 2 or 3.");
    };

} // namespace kiri_math_mini

#endif // _KIRI_MATH_ARRAY_H_
