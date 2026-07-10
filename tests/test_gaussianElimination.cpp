#include "catch.hpp"
#include "NumLA/matrix.hpp"
#include "NumLA/algorithms.hpp"

TEST_CASE("Linear Solvers", "[Algorithms][Gaussian]") {

    SECTION("Identity matrix as the coefficient matrix with a simple right-hand side vector") {
        auto A = NumLA::Matrix<double, 3, 3>::Identity();
        NumLA::ColVector<double, 3> b = {
            {3.0},
            {5.0},
            {2.0}
        };

        auto x = NumLA::solve_gaussian(A, b);

        auto A_dashed = A * x;

        REQUIRE(A_dashed(0, 0) == 3.0);
        REQUIRE(A_dashed(1, 0) == 5.0);
        REQUIRE(A_dashed(2, 0) == 2.0);
    }

    SECTION("Solve a standard 3x3 non-singular system") {
        NumLA::Matrix<double, 3, 3> A = {{
            { 2.0,  1.0, -1.0},
            {-3.0, -1.0,  2.0},
            {-2.0,  1.0,  2.0}
        }};

        NumLA::ColVector<double, 3> b = {
            {8.0},
            {-11.0},
            {-3.0}
        };

        // Analytical solution is x = 2, y = 3, z = -1
        auto x = NumLA::solve_gaussian(A, b);

        REQUIRE(x(0, 0) == Approx(2.0));
        REQUIRE(x(1, 0) == Approx(3.0));
        REQUIRE(x(2, 0) == Approx(-1.0));
    }

    SECTION("Check that a singular matrix throws an exception") {
        // A matrix where the third row is a linear combination of the first two
        NumLA::Matrix<double, 3, 3> singular_A = {{
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0},
            {5.0, 7.0, 9.0} // Row 1 + Row 2
        }};

        NumLA::ColVector<double, 3> b = {
            {1.0}, 
            {2.0}, 
            {3.0}
        };

        REQUIRE_THROWS_AS(NumLA::solve_gaussian(singular_A, b), std::runtime_error);
    }
}
