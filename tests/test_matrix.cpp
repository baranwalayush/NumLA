#include "catch.hpp"
#include "NumLA/matrix.hpp"

TEST_CASE("Matrix Core Functionality", "[matrix][core][unit]") {
    
    SECTION("Default constructor initializes elements to zero") {
        NumLA::Matrix<double, 2, 2> mat;
        REQUIRE(mat(0, 0) == 0.0);
        REQUIRE(mat(0, 1) == 0.0);
        REQUIRE(mat(1, 0) == 0.0);
        REQUIRE(mat(1, 1) == 0.0);
    }

    SECTION("Initializer list constructor populates data correctly") {
        NumLA::Matrix<double, 2, 3> mat = {{
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0}
        }};
        
        REQUIRE(mat.rows() == 2);
        REQUIRE(mat.cols() == 3);
        REQUIRE(mat(0, 0) == 1.0);
        REQUIRE(mat(0, 2) == 3.0);
        REQUIRE(mat(1, 1) == 5.0);
    }

    SECTION("Identity Factory creates a correct square identity matrix") {
        auto I = NumLA::Matrix<double, 3, 3>::Identity();
        
        REQUIRE(I(0, 0) == 1.0);
        REQUIRE(I(1, 1) == 1.0);
        REQUIRE(I(2, 2) == 1.0);
        REQUIRE(I(0, 1) == 0.0);
        REQUIRE(I(2, 0) == 0.0);
    }
}

TEST_CASE("Matrix Mathematical Operators", "[matrix][math][unit]") {

    SECTION("Matrix multiplication produces correct analytical results") {
        NumLA::Matrix<double, 2, 3> A = {{
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0}
        }};

        NumLA::Matrix<double, 3, 2> B = {{
            {7.0, 8.0},
            {9.0, 10.0},
            {11.0, 12.0}
        }};

        // Expected analytical result:
        // C(0,0) = 1*7 + 2*9 + 3*11 = 7 + 18 + 33 = 58
        // C(0,1) = 1*8 + 2*10 + 3*12 = 8 + 20 + 36 = 64
        // C(1,0) = 4*7 + 5*9 + 6*11 = 28 + 45 + 66 = 139
        // C(1,1) = 4*8 + 5*10 + 6*12 = 32 + 50 + 72 = 154
        auto C = A * B;

        REQUIRE(C(0, 0) == 58.0);
        REQUIRE(C(0, 1) == 64.0);
        REQUIRE(C(1, 0) == 139.0);
        REQUIRE(C(1, 1) == 154.0);
    }

    SECTION("Multiplication by Identity leaves matrix unchanged") {
        NumLA::Matrix<double, 2, 2> A = {{
            {3.5, -1.2},
            {0.0, 4.8}
        }};
        auto I = NumLA::Matrix<double, 2, 2>::Identity();
        
        auto result = A * I;
        
        REQUIRE(result(0, 0) == 3.5);
        REQUIRE(result(0, 1) == -1.2);
        REQUIRE(result(1, 0) == 0.0);
        REQUIRE(result(1, 1) == 4.8);
    }
}