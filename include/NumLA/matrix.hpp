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
    };

}