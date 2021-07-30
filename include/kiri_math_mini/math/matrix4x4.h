/*
 * @Author: Doyub Kim 
 * @Date: 2020-03-17 16:10:33 
 * @Last Modified by: Xu.Wang
 * @Last Modified time: 2020-03-20 19:18:56
 */
#ifndef _KIRI_MATH_MATRIX4X4_H_
#define _KIRI_MATH_MATRIX4X4_H_

#include <kiri_math_mini/math/matrix3x3.h>
#include <kiri_math_mini/math/vector4.h>

#include <array>
#include <limits>

namespace kiri_math_mini
{

    //!
    //! \brief 4-D matrix class.
    //!
    //! This class is a row-major 4-D matrix class, which means each element of
    //! the matrix is stored in order of (0,0), ... , (0,3), (1,0), ... , (3,3).
    //! Also, this 4-D matrix is speciallized for geometric transformations.
    //! \tparam T - Type of the element.
    //!
    template <typename T>
    class Matrix<T, 4, 4>
    {
    public:
        static_assert(std::is_floating_point<T>::value,
                      "Matrix only can be instantiated with floating point types");

        // MARK: Constructors

        //! Constructs identity matrix.
        Matrix();

        //! Constructs constant value matrix.
        explicit Matrix(T s);

        //! Constructs a matrix with input elements.
        //! This constructor initialize 3x3 part, and other parts are set to 0
        //! except (3,3) which will be set to 1.
        //! \warning Ordering of the input elements is row-major.
        Matrix(T m00, T m01, T m02, T m10, T m11, T m12, T m20, T m21, T m22);

        //! Constructs a matrix with input elements.
        //! \warning Ordering of the input elements is row-major.
        Matrix(T m00, T m01, T m02, T m03, T m10, T m11, T m12, T m13, T m20, T m21,
               T m22, T m23, T m30, T m31, T m32, T m33);

        //!
        //! \brief Constructs a matrix with given initializer list \p lst.
        //!
        //! This constructor will build a matrix with given initializer list \p lst
        //! such as
        //!
        //! \code{.cpp}
        //! Matrix<float, 4, 4> arr = {
        //!     {1.f, 2.f, 4.f, 3.f},
        //!     {9.f, 3.f, 5.f, 1.f},
        //!     {4.f, 8.f, 1.f, 5.f},
        //!     {3.f, 7.f, 2.f, 6.f}
        //! };
        //! \endcode
        //!
        //! Note the initializer also has 4x4 structure.
        //!
        //! \param lst Initializer list that should be copy to the new matrix.
        //!
        template <typename U>
        Matrix(const std::initializer_list<std::initializer_list<U>> &lst);

        //! Constructs a matrix with 3x3 matrix.
        //! This constructor initialize 3x3 part, and other parts are set to 0
        //! except (3,3) which is set to 1.
        explicit Matrix(const Matrix3x3<T> &m33);

        //! Constructs a matrix with input matrix.
        Matrix(const Matrix &m);

        //! Constructs a matrix with input array.
        //! \warning Ordering of the input elements is row-major.
        explicit Matrix(const T *arr);

        // MARK: Basic setters

        //! Sets whole matrix with input scalar.
        void set(T s);

        //! Sets this matrix with input elements.
        //! This method copies 3x3 part only, and other parts are set to 0
        //! except (3,3) which is set to 1.
        //! \warning Ordering of the input elements is row-major.
        void set(T m00, T m01, T m02, T m10, T m11, T m12, T m20, T m21, T m22);

        //! Sets this matrix with input elements.
        //! \warning Ordering of the input elements is row-major.
        void set(T m00, T m01, T m02, T m03, T m10, T m11, T m12, T m13, T m20,
                 T m21, T m22, T m23, T m30, T m31, T m32, T m33);

        //!
        //! \brief Sets a matrix with given initializer list \p lst.
        //!
        //! This function will fill the matrix with given initializer list \p lst
        //! such as
        //!
        //! \code{.cpp}
        //! Matrix<float, 4, 4> arr;
        //! arr.set({
        //!     {1.f, 2.f, 4.f, 3.f},
        //!     {9.f, 3.f, 5.f, 1.f},
        //!     {4.f, 8.f, 1.f, 5.f},
        //!     {3.f, 7.f, 2.f, 6.f}
        //! });
        //! \endcode
        //!
        //! Note the initializer also has 3x3 structure.
        //!
        //! \param lst Initializer list that should be copy to the new matrix.
        //!
        template <typename U>
        void set(const std::initializer_list<std::initializer_list<U>> &lst);

        //! Sets this matrix with input 3x3 matrix.
        //! This method copies 3x3 part only, and other parts are set to 0
        //! except (3,3) which will be set to 1.
        void set(const Matrix3x3<T> &m33);

        //! Copies from input matrix.
        void set(const Matrix &m);

        //! Copies from input array.
        //! \warning Ordering of the input elements is row-major.
        void set(const T *arr);

        //! Sets diagonal elements with input scalar.
        void setDiagonal(T s);

        //! Sets off-diagonal elements with input scalar.
        void setOffDiagonal(T s);

        //! Sets i-th row with input vector.
        void setRow(size_t i, const Vector4<T> &row);

        //! Sets i-th column with input vector.
        void setColumn(size_t i, const Vector4<T> &col);

        // MARK: Basic getters

        //! Returns true if this matrix is similar to the input matrix within the
        //! given tolerance.
        bool isSimilar(const Matrix &m,
                       double tol = std::numeric_limits<double>::epsilon()) const;

        //! Returns true if this matrix is a square matrix.
        bool isSquare() const;

        //! Returns number of rows of this matrix.
        size_t rows() const;

        //! Returns number of columns of this matrix.
        size_t cols() const;

        //! Returns data pointer of this matrix.
        T *data();

        //! Returns constant pointer of this matrix.
        const T *data() const;

        //! Returns 3x3 part of this matrix.
        Matrix<T, 3, 3> matrix3() const;

        // MARK: Binary operator methods - new instance = this instance (+) input
        //! Returns this matrix + input scalar.
        Matrix add(T s) const;

        //! Returns this matrix + input matrix (element-wise).
        Matrix add(const Matrix &m) const;

        //! Returns this matrix - input scalar.
        Matrix sub(T s) const;

        //! Returns this matrix - input matrix (element-wise).
        Matrix sub(const Matrix &m) const;

        //! Returns this matrix * input scalar.
        Matrix mul(T s) const;

        //! Returns this matrix * input vector.
        Vector4<T> mul(const Vector4<T> &v) const;

        //! Returns this matrix * input matrix.
        Matrix mul(const Matrix &m) const;

        //! Returns this matrix / input scalar.
        Matrix div(T s) const;

        // MARK: Binary operator methods - new instance = input (+) this instance
        //! Returns input scalar + this matrix.
        Matrix radd(T s) const;

        //! Returns input matrix + this matrix (element-wise).
        Matrix radd(const Matrix &m) const;

        //! Returns input scalar - this matrix.
        Matrix rsub(T s) const;

        //! Returns input matrix - this matrix (element-wise).
        Matrix rsub(const Matrix &m) const;

        //! Returns input scalar * this matrix.
        Matrix rmul(T s) const;

        //! Returns input matrix * this matrix.
        Matrix rmul(const Matrix &m) const;

        //! Returns input matrix / this scalar.
        Matrix rdiv(T s) const;

        // MARK: Augmented operator methods - this instance (+)= input
        //! Adds input scalar to this matrix.
        void iadd(T s);

        //! Adds input matrix to this matrix (element-wise).
        void iadd(const Matrix &m);

        //! Subtracts input scalar from this matrix.
        void isub(T s);

        //! Subtracts input matrix from this matrix (element-wise).
        void isub(const Matrix &m);

        //! Multiplies input scalar to this matrix.
        void imul(T s);

        //! Multiplies input 3x3 matrix to this matrix.
        //! This method assumes missing part of the input matrix has 0 for the
        //! off-diagonal and 1 for the diagonal part.
        void imul(const Matrix3x3<T> &m33);

        //! Multiplies input matrix to this matrix.
        void imul(const Matrix &m);

        //! Divides this matrix with input scalar.
        void idiv(T s);

        // MARK: Modifiers
        //! Transposes this matrix.
        void transpose();

        //! Inverts this matrix.
        void invert();

        // MARK: Complex getters
        //! Returns sum of all elements.
        T sum() const;

        //! Returns average of all elements.
        T avg() const;

        //! Returns minimum among all elements.
        T min() const;

        //! Returns maximum among all elements.
        T max() const;

        //! Returns absolute minimum among all elements.
        T absmin() const;

        //! Returns absolute maximum among all elements.
        T absmax() const;

        //! Returns sum of all diagonal elements.
        T trace() const;

        //! Returns determinant of this matrix.
        T determinant() const;

        //! Returns diagonal part of this matrix.
        Matrix diagonal() const;

        //! Returns off-diagonal part of this matrix.
        Matrix offDiagonal() const;

        //! Returns strictly lower triangle part of this matrix.
        Matrix strictLowerTri() const;

        //! Returns strictly upper triangle part of this matrix.
        Matrix strictUpperTri() const;

        //! Returns lower triangle part of this matrix (including the diagonal).
        Matrix lowerTri() const;

        //! Returns upper triangle part of this matrix (including the diagonal).
        Matrix upperTri() const;

        //! Returns transposed matrix.
        Matrix transposed() const;

        //! Returns inverse matrix.
        Matrix inverse() const;

        template <typename U>
        Matrix<U, 4, 4> castTo() const;

        // MARK: Setter operators
        //! Assigns input matrix.
        Matrix &operator=(const Matrix &m);

        //! Addition assignment with input scalar.
        Matrix &operator+=(T s);

        //! Addition assignment with input matrix (element-wise).
        Matrix &operator+=(const Matrix &m);

        //! Subtraction assignment with input scalar.
        Matrix &operator-=(T s);

        //! Subtraction assignment with input matrix (element-wise).
        Matrix &operator-=(const Matrix &m);

        //! Multiplication assignment with input scalar.
        Matrix &operator*=(T s);

        //! Multiplication assignment with input matrix.
        Matrix &operator*=(const Matrix &m);

        //! Multiplication assignment with input 3x3 matrix.
        //! This method assumes missing part of the input matrix has 0 for the
        //! off-diagonal and 1 for the diagonal part.
        Matrix &operator*=(const Matrix3x3<T> &m);

        //! Division assignment with input scalar.
        Matrix &operator/=(T s);

        // MARK: Getter operators
        //! Returns reference of i-th element.
        T &operator[](size_t i);

        //! Returns constant reference of i-th element.
        const T &operator[](size_t i) const;

        //! Returns reference of (i,j) element.
        T &operator()(size_t i, size_t j);

        //! Returns constant reference of (i,j) element.
        const T &operator()(size_t i, size_t j) const;

        //! Returns true if is equal to m.
        bool operator==(const Matrix &m) const;

        //! Returns true if is not equal to m.
        bool operator!=(const Matrix &m) const;

        // OpenGL Operation
        //! Sets all matrix entries to zero.
        static Matrix zero();

        //! Set all diagonal elements to 1, and other elements to 0.
        static Matrix identity();

        //! Create scale matrix.
        static Matrix scaleMatrix(T sx, T sy, T sz);

        //! Create scale matrix.
        static Matrix scaleMatrix(const Vector<T, 3> &s);

        //! Create rotation matrix.
        //! \warning Input angle should be radian.
        static Matrix rotationMatrix(const Vector<T, 3> &axis, T rad);

        //! Create translation matrix.
        static Matrix translationMatrix(const Vector<T, 3> &t);

        //! Create view matrix for camera function "lookAt".
        static Matrix viewMatrix(const Vector<T, 3> &cam, const Vector<T, 3> &target, const Vector<T, 3> &up);

        //! Create perspective matrix for 3d camera
        static Matrix perspectiveMatrix(T _fovy, T _aspect, T _near, T _far);

        //! Create orthographic matrix for 3d camera
        static Matrix orthoMatrix(T _left, T _right, T _top, T _bottom, T _near, T _far);

    private:
        std::array<T, 16> _elements;
    };

    //! Type alias for 4x4 matrix.
    template <typename T>
    using Matrix4x4 = Matrix<T, 4, 4>;

    // Operator overloadings
    //! Returns a matrix with opposite sign.
    template <typename T>
    Matrix4x4<T> operator-(const Matrix4x4<T> &a);

    //! Returns a + b (element-size).
    template <typename T>
    Matrix4x4<T> operator+(const Matrix4x4<T> &a, const Matrix4x4<T> &b);

    //! Returns a + b', where every element of matrix b' is b.
    template <typename T>
    Matrix4x4<T> operator+(const Matrix4x4<T> &a, T b);

    //! Returns a' + b, where every element of matrix a' is a.
    template <typename T>
    Matrix4x4<T> operator+(T a, const Matrix4x4<T> &b);

    //! Returns a - b (element-size).
    template <typename T>
    Matrix4x4<T> operator-(const Matrix4x4<T> &a, const Matrix4x4<T> &b);

    //! Returns a - b', where every element of matrix b' is b.
    template <typename T>
    Matrix4x4<T> operator-(const Matrix4x4<T> &a, T b);

    //! Returns a' - b, where every element of matrix a' is a.
    template <typename T>
    Matrix4x4<T> operator-(T a, const Matrix4x4<T> &b);

    //! Returns a * b', where every element of matrix b' is b.
    template <typename T>
    Matrix4x4<T> operator*(const Matrix4x4<T> &a, T b);

    //! Returns a' * b, where every element of matrix a' is a.
    template <typename T>
    Matrix4x4<T> operator*(T a, const Matrix4x4<T> &b);

    //! Returns a * b.
    template <typename T>
    Vector<T, 3> operator*(const Matrix4x4<T> &a, const Vector<T, 3> &b);

    //! Returns a * b.
    template <typename T>
    Vector4<T> operator*(const Matrix4x4<T> &a, const Vector4<T> &b);

    //! Returns a * b.
    template <typename T>
    Matrix4x4<T> operator*(const Matrix4x4<T> &a, const Matrix3x3<T> &b);

    //! Returns a * b.
    template <typename T>
    Matrix4x4<T> operator*(const Matrix3x3<T> &a, const Matrix4x4<T> &b);

    //! Returns a * b.
    template <typename T>
    Matrix4x4<T> operator*(const Matrix4x4<T> &a, const Matrix4x4<T> &b);

    //! Returns a' / b, where every element of matrix a' is a.
    template <typename T>
    Matrix4x4<T> operator/(const Matrix4x4<T> &a, T b);

    //! Returns a / b', where every element of matrix b' is b.
    template <typename T>
    Matrix4x4<T> operator/(const T &a, const Matrix4x4<T> &b);

    //! Float-type 4x4 matrix.
    typedef Matrix4x4<float> Matrix4x4F;

    //! Double-type 4x4 matrix.
    typedef Matrix4x4<double> Matrix4x4D;

} // namespace kiri_math_mini

#include "inl/matrix4x4-inl.h"

#endif // _KIRI_MATH_MATRIX4X4_H_
