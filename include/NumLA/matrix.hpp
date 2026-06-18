#pragma once
#include <array>
#include <iostream>
#include <type_traits>

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

            // Constructor with initialization list
            Matrix(const std::array<T, Rows * Cols>& data) : m_data(data) {}

            // Element access (Row-major indexing: row * Cols + col)
            T& operator()(std::size_t row, std::size_t col) {
                return m_data[row * Cols + col];
            }

            const T& operator()(std::size_t row, std::size_t col) const {
                return m_data[row * Cols + col];
            }

            constexpr std::size_t rows() const { return Rows; }
            constexpr std::size_t cols() const { return Cols; }
    };

}