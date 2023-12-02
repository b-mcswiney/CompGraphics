#include <catch2/catch_amalgamated.hpp>

#include "../vmlib/mat44.hpp"

// See mat44-rotation.cpp first!

TEST_CASE("4x4 matrix by matrix multiplication", "[mat44]")
{
	static constexpr float kEps_ = 1e-6f;

    using namespace Catch::Matchers;
	
    SECTION("Standard: matrix * matrix")
    {
        Mat44f mat1 = { {
        1.0f, 2.0f, 3.0f, 4.0f,
        5.0f, 6.0f, 7.0f, 8.0f,
        9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
        } };

        Mat44f mat2 = { {
            17.0f, 18.0f, 19.0f, 20.0f,
            21.0f, 22.0f, 23.0f, 24.0f,
            25.0f, 26.0f, 27.0f, 28.0f,
            29.0f, 30.0f, 31.0f, 32.0f
        } };

        Mat44f result = mat1 * mat2;

        REQUIRE_THAT(result(0, 0), WithinAbs(250.0f, kEps_));
        REQUIRE_THAT(result(0, 1), WithinAbs(260.0f, kEps_));
        REQUIRE_THAT(result(0, 2), WithinAbs(270.0f, kEps_));
        REQUIRE_THAT(result(0, 3), WithinAbs(280.0f, kEps_));

        REQUIRE_THAT(result(1, 0), WithinAbs(618.0f, kEps_));
        REQUIRE_THAT(result(1, 1), WithinAbs(644.0f, kEps_));
        REQUIRE_THAT(result(1, 2), WithinAbs(670.0f, kEps_));
        REQUIRE_THAT(result(1, 3), WithinAbs(696.0f, kEps_));

        REQUIRE_THAT(result(2, 0), WithinAbs(986.0f, kEps_));
        REQUIRE_THAT(result(2, 1), WithinAbs(1028.0f, kEps_));
        REQUIRE_THAT(result(2, 2), WithinAbs(1070.0f, kEps_));
        REQUIRE_THAT(result(2, 3), WithinAbs(1112.0f, kEps_));

        REQUIRE_THAT(result(3, 0), WithinAbs(1354.0f, kEps_));
        REQUIRE_THAT(result(3, 1), WithinAbs(1412.0f, kEps_));
        REQUIRE_THAT(result(3, 2), WithinAbs(1470.0f, kEps_));
        REQUIRE_THAT(result(3, 3), WithinAbs(1528.0f, kEps_));
    }
}

TEST_CASE("4x4 matrix by vector multiplication", "[mat44][vec4]")
{
	static constexpr float kEps_ = 1e-6f;
	
    using namespace Catch::Matchers;

    SECTION("Standard: matrix * vector")
    {
        Mat44f mat = { {
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            9.0f, 10.0f, 11.0f, 12.0f,
            13.0f, 14.0f, 15.0f, 16.0f
        } };

        Vec4f vec = { 1.0f, 2.0f, 3.0f, 4.0f };
        Vec4f result = mat * vec;

        REQUIRE_THAT(result[0], WithinAbs(30.0f, kEps_));
        REQUIRE_THAT(result[1], WithinAbs(70.0f, kEps_));
        REQUIRE_THAT(result[2], WithinAbs(110.0f, kEps_));
        REQUIRE_THAT(result[3], WithinAbs(150.0f, kEps_));
    }
}
