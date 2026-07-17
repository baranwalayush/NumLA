#include "catch.hpp"
#include "NumLA/matrix.hpp"
#include "NumLA/algorithms.hpp"

TEST_CASE("Gaussian elimination: forward elimination transforms A and b correctly", "[algorithms][gaussian_elimination][unit][integration]")
{

    SECTION("Perform Gaussian elimination on a simple 2x2 system")
    {
        NumLA::Matrix<double, 2, 2> A = {{{2.0, 1.0},
                                          {1.0, 3.0}}};

        NumLA::ColVector<double, 2> b = {
            {8.0},
            {13.0}};

        auto [U, modified_b] = NumLA::perform_gaussian_elimination(A, b);

        // Check that U is upper triangular
        REQUIRE(U(1, 0) == Approx(0.0));

        // Check that the modified b is correct
        REQUIRE(modified_b(0, 0) == Approx(8.0));
        REQUIRE(modified_b(1, 0) == Approx(9.0));
    }

    SECTION("Perform Gaussian elimination on a 3x3 system")
    {
        NumLA::Matrix<double, 3, 3> A = {{{0.0, 2.0, 1.0},
                                          {1.0, 1.0, 1.0},
                                          {2.0, 1.0, 0.0}}};

        NumLA::ColVector<double, 3> b = {
            {4.0},
            {6.0},
            {5.0}};

        auto [U, modified_b] = NumLA::perform_gaussian_elimination(A, b);

        // Check that U is upper triangular
        REQUIRE(U(1, 0) == Approx(0));
        REQUIRE(U(2, 0) == Approx(0));
        REQUIRE(U(2, 1) == Approx(0));

        // Check that the modified b is correct
        REQUIRE(modified_b(0, 0) == Approx(5.0));
        REQUIRE(modified_b(1, 0) == Approx(4.0));
        REQUIRE(modified_b(2, 0) == Approx(2.5));
    }

    SECTION("Perform Gaussian elimination on a 3x3 system")
    {
        NumLA::Matrix<double, 3, 3> A = {{{0.0, 2.0, 1.0},
                                          {1.0, 1.0, 1.0},
                                          {2.0, 1.0, 0.0}}};

        auto U = NumLA::perform_gaussian_elimination(A);

        // Check that U is upper triangular
        REQUIRE(U(1, 0) == Approx(0));
        REQUIRE(U(2, 0) == Approx(0));
        REQUIRE(U(2, 1) == Approx(0));
    }

    SECTION("Check that a singular matrix throws an exception")
    {
        // A matrix where the third row is a linear combination of the first two
        NumLA::Matrix<double, 3, 3> singular_A = {{
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0},
            {5.0, 7.0, 9.0} // Row 1 + Row 2
        }};

        NumLA::ColVector<double, 3> b = {
            {1.0},
            {2.0},
            {3.0}};

        REQUIRE_THROWS_AS(NumLA::perform_gaussian_elimination(singular_A, b), std::runtime_error);
    }
}

TEST_CASE("Gaussian elimination solver: solves Ax = b using forward/back substitution", "[algorithms][gaussian_elimination][solver][unit][integration]")
{

    SECTION("Identity matrix as the coefficient matrix with a simple right-hand side vector")
    {
        auto A = NumLA::Matrix<double, 3, 3>::Identity();
        NumLA::ColVector<double, 3> b = {
            {3.0},
            {5.0},
            {2.0}};

        auto x = NumLA::solve_gaussian(A, b);

        auto A_dashed = A * x;

        REQUIRE(A_dashed(0, 0) == 3.0);
        REQUIRE(A_dashed(1, 0) == 5.0);
        REQUIRE(A_dashed(2, 0) == 2.0);
    }

    SECTION("Solve a standard 3x3 non-singular system")
    {
        NumLA::Matrix<double, 3, 3> A = {{{2.0, 1.0, -1.0},
                                          {-3.0, -1.0, 2.0},
                                          {-2.0, 1.0, 2.0}}};

        NumLA::ColVector<double, 3> b = {
            {8.0},
            {-11.0},
            {-3.0}};

        // Analytical solution is x = 2, y = 3, z = -1
        auto x = NumLA::solve_gaussian(A, b);

        REQUIRE(x(0, 0) == Approx(2.0));
        REQUIRE(x(1, 0) == Approx(3.0));
        REQUIRE(x(2, 0) == Approx(-1.0));
    }

    SECTION("Check that a singular matrix throws an exception")
    {
        // A matrix where the third row is a linear combination of the first two
        NumLA::Matrix<double, 3, 3> singular_A = {{
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0},
            {5.0, 7.0, 9.0} // Row 1 + Row 2
        }};

        NumLA::ColVector<double, 3> b = {
            {1.0},
            {2.0},
            {3.0}};

        REQUIRE_THROWS_AS(NumLA::solve_gaussian(singular_A, b), std::runtime_error);
    }
}

TEST_CASE("Gauss-Jordan solver: computes solution via row-reduction to reduced echelon form", "[algorithms][gauss_jordan][solver][unit][integration]")
{

    SECTION("Identity matrix as the coefficient matrix with a simple right-hand side vector")
    {
        auto A = NumLA::Matrix<double, 3, 3>::Identity();
        NumLA::ColVector<double, 3> b = {
            {3.0},
            {5.0},
            {2.0}};

        auto x = NumLA::solve_gauss_jordan(A, b);

        auto A_dashed = A * x;

        REQUIRE(A_dashed(0, 0) == 3.0);
        REQUIRE(A_dashed(1, 0) == 5.0);
        REQUIRE(A_dashed(2, 0) == 2.0);
    }

    SECTION("Solve a standard 3x3 non-singular system")
    {
        NumLA::Matrix<double, 3, 3> A = {{{2.0, 1.0, -1.0},
                                          {-3.0, -1.0, 2.0},
                                          {-2.0, 1.0, 2.0}}};

        NumLA::ColVector<double, 3> b = {
            {8.0},
            {-11.0},
            {-3.0}};

        // Analytical solution is x = 2, y = 3, z = -1
        auto x = NumLA::solve_gauss_jordan(A, b);

        REQUIRE(x(0, 0) == Approx(2.0));
        REQUIRE(x(1, 0) == Approx(3.0));
        REQUIRE(x(2, 0) == Approx(-1.0));
    }

    SECTION("Check that a singular matrix throws an exception")
    {
        // A matrix where the third row is a linear combination of the first two
        NumLA::Matrix<double, 3, 3> singular_A = {{
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0},
            {5.0, 7.0, 9.0} // Row 1 + Row 2
        }};

        NumLA::ColVector<double, 3> b = {
            {1.0},
            {2.0},
            {3.0}};

        REQUIRE_THROWS_AS(NumLA::solve_gauss_jordan(singular_A, b), std::runtime_error);
    }

    SECTION("Compute the inverse of a non-singular matrix")
    {
        NumLA::Matrix<double, 2, 2> A = {{{4.0, 7.0},
                                          {2.0, 6.0}}};

        auto A_inv = NumLA::gauss_jordan_inverse(A);

        // The expected inverse is:
        // [ 0.6, -0.7 ]
        // [-0.2,  0.4 ]
        REQUIRE(A_inv(0, 0) == Approx(0.6));
        REQUIRE(A_inv(0, 1) == Approx(-0.7));
        REQUIRE(A_inv(1, 0) == Approx(-0.2));
        REQUIRE(A_inv(1, 1) == Approx(0.4));

        // Verify that A * A_inv is the identity matrix
        auto I = A * A_inv;
        REQUIRE(I(0, 0) == Approx(1.0));
        REQUIRE(I(0, 1) == Approx(0.0));
        REQUIRE(I(1, 0) == Approx(0.0));
        REQUIRE(I(1, 1) == Approx(1.0));
    }
}

TEST_CASE("LU Decomposition: Doolittle Algorithm", "[algorithms][lu_decomposition][doolittle][unit][integration]") 
{
    SECTION("Perform LU decomposition on a 3x3 non-singular matrix")
    {
        NumLA::Matrix<double, 3, 3> A = {{{4.0, 3.0, 2.0},
                                          {2.0, 1.0, 1.0},
                                          {6.0, 5.0, 4.0}}};

        auto [L, U] = NumLA::lu_decomposition(A);

        // Verify that L is lower triangular and U is upper triangular
        REQUIRE(L(1, 0) != Approx(0.0));
        REQUIRE(L(2, 0) != Approx(0.0));
        REQUIRE(L(2, 1) != Approx(0.0));

        REQUIRE(U(1, 0) == Approx(0.0));
        REQUIRE(U(2, 0) == Approx(0.0));
        REQUIRE(U(2, 1) == Approx(0.0));

        // Verify that L * U equals the original matrix A
        auto A_reconstructed = L * U;
        for (std::size_t i = 0; i < 3; ++i) {
            for (std::size_t j = 0; j < 3; ++j) {
                REQUIRE(A_reconstructed(i, j) == Approx(A(i, j)));
            }
        }
    }
}
