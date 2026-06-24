#include <iostream>
#include "NumLA/matrix.hpp"
#include "NumLA/algorithms.hpp"

int main() {
    // Define system matrix A
    NumLA::Matrix<double, 3, 3> A = {{
        { 2.0,  1.0, -1.0},
        {-3.0, -1.0,  2.0},
        {-2.0,  1.0,  2.0}
    }};

    // Define right-hand side vector b
    NumLA::ColVector<double, 3> b = {
        {8.0},
        {-11.0},
        {-3.0}
    };

    std::cout << "Solving Ax = b...\n";
    std::cout << "Matrix A:\n" << A << "\n";
    std::cout << "Vector b:\n" << b << "\n";

    try {
        // Run the solver
        auto x = NumLA::solve_gaussian(A, b);
        
        std::cout << "Solution Vector x:\n" << x << "\n";
        
        // Verification: Check if A * x matches original vector b!
        auto verification = A * x;
        std::cout << "Verification (A * x):\n" << verification << "\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}