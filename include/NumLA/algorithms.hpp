#pragma once

#include "matrix.hpp"
#include <cmath>
#include <stdexcept>
#include <utility>

namespace NumLA {

    /**
     * Performs Gaussian elimination with partial pivoting on the system Ax = b.
     * Partial pivoting is used to enhance numerical stability by swapping rows to ensure the pivot element is the largest in its column.
     * @param A Coefficient matrix (Dim x Dim)
     * @param b Right-hand side vector (Dim x 1)
     * @return A pair containing the modified upper triangular matrix A and the modified vector b
     * @throws std::runtime_error if the matrix is singular or near-singular
     */
    template<typename T, std::size_t Dim>
    std::pair<Matrix<T, Dim, Dim>, ColVector<T, Dim>> perform_gaussian_elimination(Matrix<T, Dim, Dim> A, ColVector<T, Dim> b) {

        // Forward Elimination 
        for (std::size_t i = 0; i < Dim; ++i) {
            
            // PARTIAL PIVOTING 
            // Find the row with the largest absolute value in the current column
            std::size_t max_row = i;
            for (std::size_t r = i + 1; r < Dim; ++r) {
                if (std::abs(A(r, i)) > std::abs(A(max_row, i))) {
                    max_row = r;
                }
            }
            
            // If the rows are different, swap them in both Matrix A and Vector b
            if (max_row != i) {
                for (std::size_t c = 0; c < Dim; ++c) {
                    std::swap(A(i, c), A(max_row, c));
                }
                std::swap(b(i, 0), b(max_row, 0));
            }
            
            // Check if the matrix is singular (or close to it)
            if (std::abs(A(i, i)) < 1e-12) {
                throw std::runtime_error("Matrix is singular or near-singular. Cannot solve.");
            }
            
            // Eliminate the entries below the pivot
            for (std::size_t r = i + 1; r < Dim; ++r) {
                T factor = A(r, i) / A(i, i);
                for (std::size_t c = i; c < Dim; ++c) {
                    A(r, c) -= factor * A(i, c);
                }
                b(r, 0) -= factor * b(i, 0);
            }
        }

        return std::make_pair(A, b);
    }

    /**
     * Performs Gaussian elimination with partial pivoting on a square matrix A and returns the upper triangular form.
     * Partial pivoting is used to enhance numerical stability by swapping rows to ensure the pivot element is the largest in its column.
     * @param A Coefficient matrix (Dim x Dim)
     * @return Upper triangular matrix after Gaussian elimination
     * @throws std::runtime_error if the matrix is singular or near-singular
     */
    template <typename T, std::size_t Dim>
    Matrix<T, Dim, Dim> perform_gaussian_elimination(Matrix<T, Dim, Dim> A) {

        ColVector<T, Dim> b; // Placeholder for the right-hand side vector

        std::tie(A, b) = perform_gaussian_elimination(A, b);

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
        
        std::tie(A, b) = perform_gaussian_elimination(A, b);

        // Back Substitution 
        ColVector<T, Dim> x; // Result vector initialized to 0
        
        // Loop backwards from the last row to the first
        for (int i = static_cast<int>(Dim) - 1; i >= 0; --i) {
            T sum = 0;
            for (std::size_t j = i + 1; j < Dim; ++j) {
                sum += A(i, j) * x(j, 0);
            }
            x(i, 0) = (b(i, 0) - sum) / A(i, i);
        }

        return x;
    }

}