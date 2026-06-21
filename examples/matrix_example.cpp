#include <iostream>
#include "NumLA/matrix.hpp"

int main() {

    // Generate an Identity Matrix
    auto I = NumLA::Matrix<double, 2, 2>::Identity();
    std::cout << "Identity Matrix I:\n" << I << "\n";

    // Initialize a 2x3 Matrix
    NumLA::Matrix<double, 2, 3> A = {{
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0}
    }};

    // Initialize a 3x2 Matrix
    NumLA::Matrix<double, 3, 2> B = {{
        {7.0, 8.0},
        {9.0, 10.0},
        {11.0, 12.0}
    }};

    std::cout << "Matrix A:\n" << A << "\n";
    std::cout << "Matrix B:\n" << B << "\n";

    // Multiply them (Result will be 2x2)
    auto C = A * B;
    std::cout << "Result C (A * B):\n" << C << "\n";

    // Demonstrate element access
    std::cout << "Element C(0, 1): " << C(0, 1) << "\n"; // Should output the element at first row, second column of C

    // Demonstrate modifying an element
    C(0, 1) = 42.0;
    std::cout << "Modified Result C (after changing C(0, 1) to 42.0):\n" << C << "\n";

    // Initialize a vector
    NumLA::Vector<double, 3> v = {{1.0}, {2.0}, {3.0}};
    std::cout << "Vector v:\n" << v << "\n";

    return 0;
}