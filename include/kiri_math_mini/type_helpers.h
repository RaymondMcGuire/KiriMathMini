#ifndef _KIRI_MATH_TYPE_HELPERS_H_
#define _KIRI_MATH_TYPE_HELPERS_H_

namespace kiri_math_mini
{

    //! Returns the type of the value itself.
    template <typename T>
    struct ScalarType
    {
        typedef T value;
    };

} // namespace kiri_math_mini

#endif // _KIRI_MATH_TYPE_HELPERS_H_
