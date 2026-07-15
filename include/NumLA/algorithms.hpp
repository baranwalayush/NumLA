#pragma once

#include "matrix.hpp"
#include <cmath>
#include <cstddef>
#include <stdexcept>
#include <utility>

namespace NumLA {

    namespace detail {

        template <typename T, std::size_t Dim, std::size_t Cols>
        void forward_eliminate(Matrix<T, Dim, Dim>& A, Matrix<T, Dim, Cols>& B) {
            for (std::size_t i = 0; i < Dim; ++i) {
                std::size_t max_row = i;
                for (std::size_t r = i + 1; r < Dim; ++r) {
                    if (std::abs(A(r, i)) > std::abs(A(max_row, i))) {
                        max_row = r;
                    }
                }

                if (max_row != i) {
                    for (std::size_t c = 0; c < Dim; ++c) {
                        std::swap(A(i, c), A(max_row, c));
                    }
                    for (std::size_t c = 0; c < Cols; ++c) {
                        std::swap(B(i, c), B(max_row, c));
                    }
                }

                if (std::abs(A(i, i)) < 1e-12) {
                    throw std::runtime_error("Matrix is singular or near-singular. Cannot solve.");
                }

                for (std::size_t r = i + 1; r < Dim; ++r) {
                    const T factor = A(r, i) / A(i, i);
                    for (std::size_t c = i; c < Dim; ++c) {
                        A(r, c) -= factor * A(i, c);
                    }
                    for (std::size_t c = 0; c < Cols; ++c) {
                        B(r, c) -= factor * B(i, c);
                    }
                }
            }
        }

        template <typename T, std::size_t Dim>
        ColVector<T, Dim> back_substitute(const Matrix<T, Dim, Dim>& A, const ColVector<T, Dim>& b) {
            ColVector<T, Dim> x;

            for (int i = static_cast<int>(Dim) - 1; i >= 0; --i) {
                T sum = 0;
                for (std::size_t j = static_cast<std::size_t>(i) + 1; j < Dim; ++j) {
                    sum += A(static_cast<std::size_t>(i), j) * x(j, 0);
                }
                x(static_cast<std::size_t>(i), 0) = (b(static_cast<std::size_t>(i), 0) - sum) / A(static_cast<std::size_t>(i), i);
            }

            return x;
        }

        template <typename T, std::size_t Dim, std::size_t Cols>
        void gauss_jordan_reduce(Matrix<T, Dim, Dim>& A, Matrix<T, Dim, Cols>& B) {
            for (int i = static_cast<int>(Dim) - 1; i >= 0; --i) {
                const T pivot = A(i, i);
                for (std::size_t j = 0; j < Dim; ++j) {
                    A(i, j) /= pivot;
                }
                for (std::size_t j = 0; j < Cols; ++j) {
                    B(i, j) /= pivot;
                }

                for (int r = i-1; r >= 0; --r) {
                    const T factor = A(r, i);
                    for (std::size_t c = i; c < Dim; ++c) {
                        A(r, c) -= factor * A(i, c);
                    }
                    for (std::size_t c = 0; c < Cols; ++c) {
                        B(r, c) -= factor * B(i, c);
                    }
                }
            }
        }

    }

    /**
     * Performs Gaussian elimination with partial pivoting on the system Ax = b.
     * Partial pivoting is used to enhance numerical stability by swapping rows to ensure the pivot element is the largest in its column.
     * @param A Coefficient matrix (Dim x Dim)
     * @param b Right-hand side vector (Dim x 1)
     * @return A pair containing the row echelon form of A (or the upper triangular matrix) and the modified right-hand side vector b after elimination
     * @throws std::runtime_error if the matrix is singular or near-singular
     */
    template<typename T, std::size_t Dim>
    std::pair<Matrix<T, Dim, Dim>, ColVector<T, Dim>> perform_gaussian_elimination(Matrix<T, Dim, Dim> A, ColVector<T, Dim> b) {
        detail::forward_eliminate(A, b);

        return std::make_pair(A, b);
    }

    /**
     * Performs Gaussian elimination with partial pivoting on a square matrix A and returns the upper triangular form.
     * Partial pivoting is used to enhance numerical stability by swapping rows to ensure the pivot element is the largest in its column.
     * @param A Coefficient matrix (Dim x Dim)
     * @return Row echelon form of A (or the upper triangular matrix) after Gaussian elimination
     * @throws std::runtime_error if the matrix is singular or near-singular
     */
    template <typename T, std::size_t Dim>
    Matrix<T, Dim, Dim> perform_gaussian_elimination(Matrix<T, Dim, Dim> A) {

        ColVector<T, Dim> b; // Placeholder for the right-hand side vector

        detail::forward_eliminate(A, b);

        return A;
    }

    /**
     * Solves the linear system Ax = b using Gaussian Elimination with Partial Pivoting.
     * Partial pivoting is used to enhance numerical stability by swapping rows to ensure the pivot element is the largest in its column.
     * Takes A and b by value to keep original data intact.
     * @param A Coefficient matrix (Dim x Dim)
     * @param b Right-hand side vector (Dim x 1)
     * @return Solution vector x (Dim x 1)
     * @throws std::runtime_error if the matrix is singular or near-singular
     */
    template <typename T, std::size_t Dim>
    ColVector<T, Dim> solve_gaussian(Matrix<T, Dim, Dim> A, ColVector<T, Dim> b) {
        detail::forward_eliminate(A, b);
        return detail::back_substitute(A, b);
    }

    /**
     * Solves the linear system Ax = b using Gauss-Jordan Elimination.
     * This method reduces the augmented matrix [A|b] to reduced row echelon form, allowing direct extraction of the solution vector x.
     * @param A Coefficient matrix (Dim x Dim)
     * @param b Right-hand side vector (Dim x 1)
     * @return Solution vector x (Dim x 1)
     * @throws std::runtime_error if the matrix is singular or near-singular
     */
    template <typename T, std::size_t Dim>
    ColVector<T, Dim> solve_gauss_jordan(Matrix<T, Dim, Dim> A, ColVector<T, Dim> b) {

        detail::forward_eliminate(A, b);
        detail::gauss_jordan_reduce(A, b);
        return b;
    }

    /**
     * Computes the inverse of a square matrix A using Gauss-Jordan elimination.
     * The method augments A with the identity matrix and reduces it to reduced row echelon form, resulting in the inverse of A.
     * @param A Square matrix (Dim x Dim)
     * @return Inverse of matrix A (Dim x Dim)
     * @throws std::runtime_error if the matrix is singular or near-singular
     */
    template <typename T, std::size_t Dim>
    Matrix<T, Dim, Dim> gauss_jordan_inverse(Matrix<T, Dim, Dim> A) {

        Matrix<T, Dim, Dim> I = Matrix<T, Dim, Dim>::Identity();

        detail::forward_eliminate(A, I);
        detail::gauss_jordan_reduce(A, I);

        return I;
    }

    /**
     * Performs LU decomposition of a square matrix A into lower triangular matrix L and upper triangular matrix U.
     * The decomposition is done using Doolittle's method, where L is a lower triangular matrix with unit diagonal elements and U is an upper triangular matrix.
     * This function does not perform pivoting
     * @param A Square matrix (Dim x Dim) to be decomposed
     * @return A pair containing the lower triangular matrix L and the upper triangular matrix U
     * @throws std::runtime_error if the matrix is singular or near-singular
     */
    template <typename T, std::size_t Dim>
    std::pair<Matrix<T, Dim, Dim>, Matrix<T, Dim, Dim>> lu_decomposition(Matrix<T, Dim, Dim> A) {
        Matrix<T, Dim, Dim> L; // Lower triangular matrix
        Matrix<T, Dim, Dim> U; // Upper triangular matrix

        for (std::size_t i = 0; i < Dim; ++i) {
            for (std::size_t j = i; j < Dim; ++j) {
                T sum = 0;
                for (std::size_t k = 0; k < i; ++k) {
                    sum += L(i, k) * U(k, j);
                }
                U(i, j) = A(i, j) - sum;
            }

            for (std::size_t j = i + 1; j < Dim; ++j) {
                T sum = 0;
                for (std::size_t k = 0; k < i; ++k) {
                    sum += L(j, k) * U(k, i);
                }
                L(j, i) = (A(j, i) - sum) / U(i, i);
            }
            L(i, i) = 1; // Diagonal elements of L are 1
        }

        return std::make_pair(L, U);
    }
}