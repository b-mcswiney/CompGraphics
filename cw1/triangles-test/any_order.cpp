#include <catch2/catch_amalgamated.hpp>

#include "helpers.hpp"

#include "../draw2d/surface.hpp"
#include "../draw2d/draw.hpp"

TEST_CASE( "any order", "[any order][!mayfail]")
{
    Surface surface( 320, 240 );
    surface.clear();
 
    SECTION( "Barycentric test" )
    {
        draw_triangle_interp( surface,
            { 20.f, 20.f }, { 30.f, 30.f }, { 40.f, 20.f },
            { 100 ,0 ,0 }, { 0, 0, 0 }, { 0, 0, 0 } 
        );

        auto const triangleOne = find_most_red_pixel( surface );

        draw_triangle_interp( surface,
            {30.f, 30.f}, {20.f, 20.f}, {40.f, 20.f},
            { 100 ,0 ,0 }, { 0, 0, 0 }, { 0, 0, 0 } 
        );

        auto const triangleTwo = find_most_red_pixel( surface );

        draw_triangle_interp( surface,
            {30.f, 30.f}, {40.f, 20.f}, {20.f, 20.f},
            { 100 ,0 ,0 }, { 0, 0, 0 }, { 0, 0, 0 } 
        );

        auto const triangleThree = find_most_red_pixel( surface );

        REQUIRE( int(triangleOne.r) == int(triangleTwo.r) );
        REQUIRE( int(triangleTwo.r) == int(triangleThree.r) );
        REQUIRE( int(triangleOne.r) == int(triangleThree.r) );
    }
    SECTION( "Solid test" )
    {
        draw_triangle_solid( surface,
            {20.f, 20.f}, {30.f, 30.f}, {40.f, 20.f},
            { 100 ,100 ,100 }
        );

        auto const triangleOne = find_most_red_pixel( surface );

        draw_triangle_solid( surface,
            {30.f, 30.f}, {20.f, 20.f}, {40.f, 20.f},
            { 100 ,100 ,100 }
        );

        auto const triangleTwo = find_most_red_pixel( surface );

        draw_triangle_solid( surface,
            {30.f, 30.f}, {40.f, 20.f}, {20.f, 20.f},
            { 100 ,100 ,100 }
        );

        auto const triangleThree = find_most_red_pixel( surface );

        REQUIRE( int(triangleOne.r) == int(triangleTwo.r) );
        REQUIRE( int(triangleTwo.r) == int(triangleThree.r) );
        REQUIRE( int(triangleOne.r) == int(triangleThree.r) );
    }
}