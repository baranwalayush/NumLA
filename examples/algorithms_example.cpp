#include <iostream>
#include "NumLA/matrix.hpp"
#include "NumLA/algorithms.hpp"

int main() {

    NumLA::Matrix<double, 3, 3> A1 = {{
        {0.0, 2.0, 1.0},
        {1.0, 1.0, 1.0},
        {2.0, 1.0, 0.0}
    }};

    NumLA::ColVector<double, 3> b1 = {
        {4.0},
        {6.0},
        {5.0}
    };

    std::cout << "Performing Gaussian Elimination on...\n";
    std::cout << "Matrix A:\n" << A1 << "\n";
    std::cout << "Vector b:\n" << b1 << "\n";

    try {
        // Run the solver
        auto [U, modified_b] = NumLA::perform_gaussian_elimination(A1, b1);
        
        std::cout << "Upper Triangular Matrix U of the system A:\n" << U << "\n";
        std::cout << "Modified Vector b after elimination:\n" << modified_b << "\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    std::cout << "----------------------------------------\n\n";

    // Define system matrix A
    NumLA::Matrix<double, 3, 3> A2 = {{
        { 2.0,  1.0, -1.0},
        {-3.0, -1.0,  2.0},
        {-2.0,  1.0,  2.0}
    }};

    // Define right-hand side vector b
    NumLA::ColVector<double, 3> b2 = {
        {8.0},
        {-11.0},
        {-3.0}
    };

    std::cout << "Solving Ax = b...\n";
    std::cout << "Matrix A:\n" << A2 << "\n";
    std::cout << "Vector b:\n" << b2 << "\n";

    try {
        // Run the solver
        auto x = NumLA::solve_gaussian(A2, b2);
        
        std::cout << "Solution Vector x:\n" << x << "\n";
        
        // Verification: Check if A * x matches original vector b!
        auto verification = A2 * x;
        std::cout << "Verification (A * x):\n" << verification << "\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}