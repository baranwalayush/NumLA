#pragma once
#include <array>
#include <iostream>
#include <type_traits>
#include <initializer_list>
#include <cassert>

namespace NumLA {

    template <typename T, std::size_t Rows, std::size_t Cols>
    class Matrix {
        // Ensure they only pass arithmetic types (int, float, double)
        static_assert(std::is_arithmetic_v<T>, "Matrix type must be numeric.");
        static_assert(Rows > 0 && Cols > 0, "Matrix dimensions must be greater than zero.");

        private:
            // Flat 1D storage for cache locality
            std::array<T, Rows * Cols> m_data{};

        public:
            // Default constructor (initializes to zeros)
            Matrix() = default;

            // // Constructor with initialization list
            // Matrix(const std::array<T, Rows * Cols>& data) : m_data(data) {}

            // Initializer List Constructor: Allows nested brace initialization {{1, 2}, {3, 4}}
            Matrix(std::initializer_list<std::initializer_list<T>> list) {
                assert(list.size() == Rows && "Initializer list row count mismatch.");
                
                std::size_t row = 0;
                for (const auto& row_list : list) {
                    assert(row_list.size() == Cols && "Initializer list column count mismatch.");
                    std::size_t col = 0;
                    for (const auto& val : row_list) {
                        (*this)(row, col) = val;
                        ++col;
                    }
                    ++row;
                }
            }

            // Element access (Row-major indexing: row * Cols + col)
            T& operator()(std::size_t row, std::size_t col) {
                assert(row < Rows && col < Cols && "Matrix index out of bounds.");
                return m_data[row * Cols + col];
            }

            const T& operator()(std::size_t row, std::size_t col) const {
                assert(row < Rows && col < Cols && "Matrix index out of bounds.");
                return m_data[row * Cols + col];
            }

            constexpr std::size_t rows() const { return Rows; }
            constexpr std::size_t cols() const { return Cols; }

            static constexpr Matrix Identity() {
                static_assert(Rows == Cols, "Identity matrix must be square (Rows must equal Cols).");
                
                Matrix result;
                for (std::size_t i = 0; i < Rows; ++i) {
                    result(i, i) = static_cast<T>(1);
                }
                return result;
            }
    };

    // Vector Type Aliases
    // Column vector: Dim rows, 1 column (dim*1)
    template <typename T, std::size_t Dim>
    using ColVector = Matrix<T, Dim, 1>;

    // Row vector: 1 row, Dim columns (1*dim)
    template <typename T, std::size_t Dim>
    using RowVector = Matrix<T, 1, Dim>;

    // Matrix Multiplication
    template <typename T, std::size_t R1, std::size_t C1, std::size_t C2>
    Matrix<T, R1, C2> operator*(const Matrix<T, R1, C1>& lhs, const Matrix<T, C1, C2>& rhs) {
        Matrix<T, R1, C2> result; // Zero-initialized by default

        for (std::size_t i = 0; i < R1; ++i) {
            for (std::size_t k = 0; k < C1; ++k) {
                T factor = lhs(i, k);
                for (std::size_t j = 0; j < C2; ++j) {
                    result(i, j) += factor * rhs(k, j);
                }
            }
        }
            return result;
    }

    // Stream Output Operator
    template <typename T, std::size_t Rows, std::size_t Cols>
    std::ostream& operator<<(std::ostream& os, const Matrix<T, Rows, Cols>& matrix) {
        for (std::size_t i = 0; i < Rows; ++i) {
            os << "[ ";
            for (std::size_t j = 0; j < Cols; ++j) {
                os << matrix(i, j) << (j + 1 < Cols ? ", " : " ");
            }
            os << "]\n";
        }
        return os;
    }

    // Matrix Addition
    template <typename T, std::size_t Rows, std::size_t Cols>
    Matrix<T, Rows, Cols> operator+(const Matrix<T, Rows, Cols>& lhs, const Matrix<T, Rows, Cols>& rhs) {
        Matrix<T, Rows, Cols> result;
        for (std::size_t i = 0; i < Rows; ++i) {
            for (std::size_t j = 0; j < Cols; ++j) {
                result(i, j) = lhs(i, j) + rhs(i, j);
            }
        }
        return result;
    }

    // Matrix Subtraction
    template <typename T, std::size_t Rows, std::size_t Cols>
    Matrix<T, Rows, Cols> operator-(const Matrix<T, Rows, Cols>& lhs, const Matrix<T, Rows, Cols>& rhs) {
        Matrix<T, Rows, Cols> result;
        for (std::size_t i = 0; i < Rows; ++i) {
            for (std::size_t j = 0; j < Cols; ++j) {
                result(i, j) = lhs(i, j) - rhs(i, j);
            }
        }
        return result;
    }

    // Scalar Multiplication (Scalar * Matrix)
    template<typename T, std::size_t Rows, std::size_t Cols>
    Matrix<T, Rows, Cols> operator*(const T& scalar, const Matrix<T, Rows, Cols>& matrix) {
        Matrix<T, Rows, Cols> result;
        for (std::size_t i = 0; i < Rows; ++i) {
            for (std::size_t j = 0; j < Cols; ++j) {
                result(i, j) = matrix(i, j) * scalar;
            }
        }
        return result;
    }

    // Scalar Multiplication (Matrix * Scalar)
    template<typename T, std::size_t Rows, std::size_t Cols>
    Matrix<T, Rows, Cols> operator*(const Matrix<T, Rows, Cols>& matrix, const T& scalar) {
        return scalar * matrix;
    }

    // Transpose of a Matrix
    template <typename T, std::size_t Rows, std::size_t Cols>
    Matrix<T, Cols, Rows> transpose(const Matrix<T, Rows, Cols>& matrix) {
        Matrix<T, Cols, Rows> result;
        for (std::size_t i = 0; i < Rows; ++i) {
            for (std::size_t j = 0; j < Cols; ++j) {
                result(j, i) = matrix(i, j);
            }
        }
        return result;
    }

}