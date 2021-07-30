#ifndef _KIRI_MATH_PDE_H_
#define _KIRI_MATH_PDE_H_

#include <array>

namespace kiri_math_mini
{

    //!
    //! \brief 1-st order upwind differencing.
    //! D0[1] is the origin.
    //!
    //! \code
    //!   |------|------|
    //! D0[0]  D0[1]  D0[2]
    //! \endcode
    //!
    //! Returns two solutions for each side.
    //!
    template <typename T>
    std::array<T, 2> upwind1(T *D0, T dx);

    //!
    //! \brief 1-st order upwind differencing.
    //! D0[1] is the origin.
    //!
    //! \code
    //!   |------|------|
    //! D0[0]  D0[1]  D0[2]
    //! \endcode
    //!
    template <typename T>
    T upwind1(T *D0, T dx, bool isDirectionPositive);

    //!
    //! \brief 2nd-order central differencing.
    //! D0[1] is the origin.
    //!
    //! \code
    //!   |------|------|
    //! D0[0]  D0[1]  D0[2]
    //! \endcode
    //!
    template <typename T>
    T cd2(T *D0, T dx);

    //!
    //! \brief 3rd-order ENO.
    //! D0[3] is the origin.
    //!
    //! \code
    //!   |------|------|------|------|------|------|
    //! D0[0]  D0[1]  D0[2]  D0[3]  D0[4]  D0[5]  D0[6]
    //! \endcode
    //!
    //! Returns two solutions for each side.
    //!
    template <typename T>
    std::array<T, 2> eno3(T *D0, T dx);

    //!
    //! \brief 3rd-order ENO.
    //! D0[3] is the origin.
    //!
    //! \code
    //!   |------|------|------|------|------|------|
    //! D0[0]  D0[1]  D0[2]  D0[3]  D0[4]  D0[5]  D0[6]
    //! \endcode
    //!
    //!
    template <typename T>
    T eno3(T *D0, T dx, bool isDirectionPositive);

    //!
    //! \brief 5th-order Weno.
    //! D0[3] is the origin.
    //!
    //! \code
    //!   |------|------|------|------|------|------|
    //! D0[0]  D0[1]  D0[2]  D0[3]  D0[4]  D0[5]  D0[6]
    //! \endcode
    //!
    //! Returns two solutions for each side.
    //!
    //!
    template <typename T>
    std::array<T, 2> weno5(T *v, T h, T eps = 1.0e-8);

    //!
    //! \brief 5th-order Weno.
    //! D0[3] is the origin.
    //!
    //! \code
    //!   |------|------|------|------|------|------|
    //! D0[0]  D0[1]  D0[2]  D0[3]  D0[4]  D0[5]  D0[6]
    //! \endcode
    //!
    template <typename T>
    T weno5(T *v, T h, bool is_velocity_positive, T eps = 1.0e-8);

} // namespace kiri_math_mini

#include "inl/pde-inl.h"

#endif // _KIRI_MATH_PDE_H_
