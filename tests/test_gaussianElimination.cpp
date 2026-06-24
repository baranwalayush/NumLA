#include "catch.hpp"
#include "NumLA/matrix.hpp"
#include "NumLA/algorithms.hpp"

TEST_CASE("Matrix Gaussian Elimination", "[Matrix][Algorithms]") {

    SECTION("Identity matrix as the coefficient matrix with a simple right-hand side vector") {
        auto A = NumLA::Matrix<double, 3, 3>::Identity();
        NumLA::ColVector<double, 3> b = {{3},
                                           {5},
                                           {2}};

        // Perform Gaussian elimination
        auto x = NumLA::solve_gaussian(A, b);

        auto A_dashed = A * x;

        REQUIRE(A_dashed(0, 0) == 3);
        REQUIRE(A_dashed(1, 0) == 5);
        REQUIRE(A_dashed(2, 0) == 2);
    }
}
