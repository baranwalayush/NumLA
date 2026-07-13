#include <iostream>
#include "NumLA/matrix.hpp"
#include "NumLA/algorithms.hpp"

int main() {

    // Example 1: Perform Gaussian elimination on a simple 3*3 system

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

    // Example 2: Solve a linear system Ax = b using Gaussian elimination

    NumLA::Matrix<double, 3, 3> A2 = {{
        { 2.0,  1.0, -1.0},
        { 3.0, -1.0,  2.0},
        {-2.0,  1.0,  2.0}
    }};

    NumLA::ColVector<double, 3> b2 = {
        {8.0},
        {-11.0},
        {-3.0}
    };

    std::cout << "Solving Ax = b... using Gaussian Elimination\n";
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

    std::cout << "----------------------------------------\n\n";
    
    // Example 3: Solve a linear system Ax = b using Gauss-Jordan elimination

    std::cout << "Solving Ax = b... using Gauss-Jordan Elimination\n";
    std::cout << "Matrix A:\n" << A2 << "\n";
    std::cout << "Vector b:\n" << b2 << "\n";

    try {
        // Run the solver
        auto x = NumLA::solve_gauss_jordan(A2, b2);
        
        std::cout << "Solution Vector x:\n" << x << "\n";
        
        // Verification: Check if A * x matches original vector b!
        auto verification = A2 * x;
        std::cout << "Verification (A * x):\n" << verification << "\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    std::cout << "----------------------------------------\n\n";

    // Example 4: Find inverse of a matrix using Gauss-Jordan elimination

    NumLA::Matrix<double, 2, 2> A3 = {{
        {4.0, 7.0},
        {2.0, 6.0}
    }};

    std::cout << "Finding inverse of matrix A using Gauss-Jordan elimination...\n";
    std::cout << "Matrix A:\n" << A3 << "\n";

    try {
        auto A_inv = NumLA::gauss_jordan_inverse(A3);
        std::cout << "Inverse of Matrix A:\n" << A_inv << "\n";

        // Verification: Check if A * x matches original vector b!
        auto verification = A3 * A_inv;
        std::cout << "Verification (A * A_inv):\n" << verification << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }


    return 0;
}